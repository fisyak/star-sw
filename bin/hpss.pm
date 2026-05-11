#  Program Name            : HPPS.PM
#    Original Author       : JLAURET
#    Date                  :  7-DEC-1998
#    Program Description   : Perl Module for HPPS perl scripts
#                          :
#  Duplicate copy needs to be on carousel
#


use Carp;
use Date::Manip;
use DBI;
use Digest::MD5;




# ----------------------------- Misc setup
$HPSS::DEBUG = (1==0);
$HPSS::FAKE  = (1==0);
$HPSS::FAILED= (1==0);
#$HPSS::CHECKS= (1==0);
$HPSS::DELENT= (1==0);
$HPSS::FILIN = "";
$HPSS::FILOUT= "";
$HPSS::LOGFIL= "";
$HPSS::DATE = &DateCalc(&Today(),"+30 days");
$HPSS::MDATE= &DateCalc(&Today(),"-8 days"); # yesterday - 7 days
$HPSS::DIFFT= 0;
$HPSS::PROTO= "pftp";
$HPSS::OMODE= 0;
#$HPSS::PMODE= 0;
@HPSS::LASTMSG=(""); # go 2 messages deep


# ----------------------------- Group/Disk partitions setup
# --- Used for file-restore only.

$HPSS::PPATH   ="//treat-as-rr.rcf.bnl.gov/dev/null";
$HPSS::GROUP   = "Star";
$HPSS::BASEPATH="/home/starreco";

# ----------------------------- Database setup
$HPSS::DDBNAME  ="DataCarousel";
$HPSS::DDBUSER  ="star_c_user";
$HPSS::DDBPASSWD="VoyonsVoir";

$HPSS::DDBSERVER="duvall.star.bnl.gov";
$HPSS::DDBPORT=undef;


# -- DDB access privs and Possibilities
$HPSS::UPDATE=(0==1);
$HPSS::APPEND=(0==1);
#$HPSS::UPDATE_PRIV=(0==1);

# First table is the main one, second variable is the list of table names
# with DDBTBLINFO[idx] returning the table name for DDBTBLNAM field idx.
# First index (0) will be the main table itself.
$HPSS::DDBTBLNAM=undef;
@HPSS::DDBTBLINFO=("Entries","Sources","Destinations","NodeInfo","GrpInfo");

# Will use a global variable so no class new() would be called
$HPSS::MD5=undef;


# ----------------------------- Server per basic Rules
$HPSS::NUMFILES=50;



# --- Nothing to change below this line ---------------------------------

$HPSS::VERSION="V01.337";


# Those variables MUST be global but hidden from configuration. They are
# intermediate variables or Information agregates.
$HPSS::CDATE=&Today();
$HPSS::USER=undef;
$HPSS::DDBREF=undef;
@HPSS::DDBINFO=undef;
@HPSS::DDBINFO_REF=(undef,undef);


# The next variables are for our checking purposes only. To modify if
# set_ddb_parameters has other arguments.
$HPSS::MAXPARAMETERS=11;

# Auto-detect NFS server mechanism
#%HPSS::NODES;

# parameter table
#%HPSS::PARAM


# Records will go as follow
# (will be updated, see aaa_readme.format for the moment.)




require 5.000;
require Exporter;
@ISA = qw(Exporter);

@EXPORT=qw(
	   hpss_get_args hpss_user_help hpss_check_all
	   hpss_set_ddb_parameters hpss_toggle_debug
	   hpss_get_value hpss_set_value
	   hpss_get_clean_method hpss_get_parameter hpss_set_parameter
	   hpss_set_server_mode
	   hpss_get_files hpss_set_files hpss_flush_files
	   hpss_get_record_locids hpss_set_record_locids hpss_update_record_locids
	   hpss_open_database hpss_close_database
	   hpss_add_record hpss_remove_record
	   hpss_infoidx hpss_date
	   hpss_parse_log
	   hpss_set_message hpss_get_message hpss_flush_message hpss_clean_state
	   hpss_set_logfile hpss_get_version

           Today
);




# Note --> NONE of the variables are exported.






# ----------------------------------------------------------------------
#             Args related routine. Uses global variables.
# ----------------------------------------------------------------------
sub	hpss_get_args
{
    my($i,$err,$test);
    my($first,$Life);
    my($cnt);

    $first = (1==1);
    $Life  = 0;
    $cnt   = 0;

    # Initialize a bunch of global variables. The following usage will
    # set the database variables to the default values.
    &hpss_set_ddb_parameters();


    # Scan args
    for($i=0 ; $i <= $#ARGV ; $i++){
	if ( $ARGV[$i] eq "-f" ){
	 # read inputs from file.
	 if ( ! defined($ARGV[$i+1]) ){    die "-f is missing an input filename\n";}

	 open(FI,$ARGV[++$i]) || die "Could not open $ARGV[$i]\n";
	 while ( defined($line = <FI>) ){
	     #
	     # Allow extra info on the same line and comment
	     # character = "#" or "!"
	     #
	     $cnt++;
	     $line  =~ s/^\s*(.*?)\s*$/$1/;
	     chomp($line);
	     if( ($line ne "") && (index("!#",substr($line,0,1)) == -1)){
		 @items = split(" ",$line);
		 # next instruction is not mandatory but added to prevent
		 # warning in -w mode.
		 if(! defined($items[1]) ){ $items[1] = ""; }
		 if( $items[1] eq "" ){
		    if($first){
		     $first = (1 == 0);
		     &info_message("get_args","Second argument (OutputFile) or column ".
				   " not found. Using $HPSS::PPATH for the restore path\n");
		    }
		    $items[1] = $HPSS::PPATH;
		 }
		 # will do source only
		 if ( $items[0] !~ m/\./){
		     &info_message("get_args",
				   "[$line]\n".
				   "Source $items[0] ...\n".
				   "... does not seem to have an extension at line $cnt. This may indicate a typo\n");
		 }
		 $HPSS::FILIN .= "$items[0],";
		 $HPSS::FILOUT.= "$items[1],";
	     }
	 }
	 close(FI);
	 # Note that the last character is a "," but we cannot use
	 # substr() which expects a string of length() < whatever. The
	 # rest of this script will take care of that
     } elsif ( substr($ARGV[$i],0,1) eq "-"){
	 # Option
	 $test	= 0;


	 # Those arguments may be placed anywhere and are not followed
	 # by other arg\s+value so they will also set the test=1 flag
	 # to skip further arg\s+value parsing
	 if (  &arg_present($ARGV[$i],"upd")  ){
	     $test	= 1;	$HPSS::UPDATE	= (1 == 1);
	 }
	 if (  &arg_present($ARGV[$i],"z")  ){
	     # same than -upd but this is a change in scheme
	     $test	= 1;	$HPSS::UPDATE	= (1 == 1);
	 }
	 if (  &arg_present($ARGV[$i],"a")  ){
	     $test	= 1;	$HPSS::APPEND	= (1 == 1);
	 }
	 if (  &arg_present($ARGV[$i],"e")  ){
	     $test	= 1;	$HPSS::DELENT	= (1 == 1);
	 }
	 if (  &arg_present($ARGV[$i],"d")  ){
	     $test	= 1;	$HPSS::DEBUG	= (1 == 1);
	 }

#       -qQ           same in addition of files not seen  on disk from where
#                     you  make  the  request. BEWARE  of  this  option with
#                     local disk. In general, -Q will indicate the files not
#                     seen (extraneous messaging even without -q)

	 if (  &arg_present($ARGV[$i],"q")  ){
	     $test	= 1;	$HPSS::FAILED	= (1 == 1);
	 }
#	 if (  &arg_present($ARGV[$i],"Q")  ){
#	     $test	= 1;    #$HPSS::FAILED   = (1 == 1);
#	                        $HPSS::CHECKS   = (1 == 1);
#	     print "DEBUG:: Enabling source checking\n";
#	 }

	 if (  &arg_present($ARGV[$i],"v")  ){
	     $test      = 1;
	     &info_message("Version","DataCarousel $HPSS::VERSION\n");
	 }
	 if (  &arg_present($ARGV[$i],"h")  ){
	     $test	= 1;	&hpss_user_help();
	 }

         if (  &arg_present($ARGV[$i],"coffee")  ){
	     $test  = 1;    $HPSS::DEBUG	= (1 == 1);
	     print "The coffee will be ready in 5 mnts ...\n";
	     print "Just kidding. Debugging turned ON.\n";
	 } elsif (  &arg_present($ARGV[$i],"c") ){   # need elsif here because of ^c
	     $test	= 0;	&hpss_copyright();
	 }


         if (  &arg_present($ARGV[$i],"s")  ){
	     my($min,$sec);
	     my($dt,$mess);

	     $test	=  1;

	     foreach $tmp ( split(";",&hpss_get_message(undef,20)) ){
		 ($dt,$mess) = split("::",$tmp);

		 # Dates are in GMT, new format and exact delta
		 $delta = &DateCalc($dt." GMT","now",,1);
		 ($tmp,$tmp,$tmp, $day,$hour,$min,$sec) = split(":",$delta);
		 &info_message("Status",sprintf("%2.2d %02.2d:%02.2d:%02.2d %s\n",
						$day,$hour,$min,$sec,$mess));
	     }
	 }

        if ( &arg_present($ARGV[$i],"p") ||
	     &arg_present($ARGV[$i],"w")    ){
	    my($Obj,@info,@res);
	    my($pfirst)=(1==1);

	    &hpss_check_database();

	    $Obj =&hpss_open_database();
	    @res =&hpss_show_queue_activity($Obj,$HPSS::MDATE,$HPSS::DATE);
	    $test=1;
	    foreach (@res){
		#print "DEBUG [$_]\n";
		if ( $_ eq "--"){
		    print " ---------------------------------------------------------------------------\n";
		} else {
		    @info = split(";",$_);

		    if ( $info[0] == -1 ){
			# this is a string or a list of string
			if ( $#info == 1){
			    if ( $pfirst ){
				$pfirst = 1==0;
				print "\n$info[1]\n\n";
			    } else {
				print "$info[1]\n";
			    }
			} else {
			    shift(@info);
			    print sprintf "%25.25s %10.10s %7.7s  %s\n",@info;
			}
		    } else {
			shift(@info);
			print sprintf "%25.25s %10.10s %7d  %s\n",@info;
		    }
		}
	    }
        }


	 # Now treat the rest
	 if(!$test ){
	     # Exclusive arguments (t or g or ...). Quick and dirty parsing
	     if( &arg_present($ARGV[$i],"T") || &arg_present($ARGV[$i],"t") ){
		 my($date);
		 $test	= 1;

		 # Note that we will also allow the "+" syntax
		 if ( ! defined($ARGV[$i+1]) ){   die "{-t|-T} is missing a a time specification\n";}

		 $date = $ARGV[++$i];

		 if( substr($date,0,1) eq "+" ){
		     $date 	= &DateCalc(&Today(),$date,\$err);
		 }
		 # Any valid date from Date::Manip (quite a few) will pass
		 # this test. Note also
		 $date	= &Today(); #&ParseDate($date);
		 if(! $date ){
		     &hpss_user_help();
		     &die_message("get_args","Invalid Date Format. Try again\n");
		 }

		 # if
		 if ( $ARGV[$i-1] =~ /T/){
		     $HPSS::DATE = $date;
		 } else {
		     $HPSS::MDATE= $date;
		 }


	     } elsif ( &arg_present($ARGV[$i],"g") ){
		 $test  = 1;
		 if ( ! defined($ARGV[$i+1]) ){   die "-g is missing a group name\n";}
		 $HPSS::GROUP = $ARGV[++$i];

	     } elsif ( &arg_present($ARGV[$i],"r") ){
		 if ( ! defined($ARGV[$i+1]) ){   die "-r is missing a path\n";}

		 $test	= 1;	$HPSS::PPATH	= $ARGV[++$i];
		 if(substr($HPSS::PPATH,length($HPSS::PPATH)-1,1) ne "/"){
		     &info_message("get_args","Potential error. Assuming trailing".
				   " / in path $HPSS::PPATH\n");
		     $HPSS::PPATH = "$HPSS::PPATH/";
		 }

	     } elsif ( &arg_present($ARGV[$i],"b") ){
		 if ( ! defined($ARGV[$i+1]) ){   die "-b is missing a path\n";}
		 $test	= 1;	$HPSS::BASEPATH	= $ARGV[++$i];

	     } elsif (  &arg_present($ARGV[$i],"n")  ){
		 if ( ! defined($ARGV[$i+1]) ){   die "-n is missing a DB reference\n";}
		 $test	= 1;
		 $HPSS::DDBREF =  $ARGV[++$i];
		 if( index($HPSS::DDBREF,"DBI:mysql") == -1){
		     # Forgot or quick syntax used
		     $HPSS::DDBREF = "DBI:mysql:$HPSS::DDBREF";
		 }

	     } elsif (  &arg_present($ARGV[$i],"l")  ){
		 if ( ! defined($ARGV[$i+1]) ){   die "-l is missing a lifetime information\n";}
		 $test	= 1;	$Life		= $ARGV[++$i];

	     } elsif (  &arg_present($ARGV[$i],"i")  ){ # impersonate
		 if ( ! defined($ARGV[$i+1]) ){   die "-i is missing a user name\n";}
		 $test	= 1;	$HPSS::USER	= $ARGV[++$i];
		 #my(@info)=getpwnam($HPSS::USER);
		 #if ( ! $info[0] ){ &die_message("get_args","Invalid user $HPSS::USER\n");}

	     } elsif (  &arg_present($ARGV[$i],"U")  ){
		 if ( ! defined($ARGV[$i+1]) ){   die "-U is missing a user name\n";}
		 $test	= 1;	$HPSS::DDBUSER	= $ARGV[++$i];
	     } elsif (  &arg_present($ARGV[$i],"P")  ){
		 if ( ! defined($ARGV[$i+1]) ){   die "-P is missing a password\n";}
		 $test	= 1;	$HPSS::DDBPASSWD= $ARGV[++$i];
	     }
	 }


	 # Did we get any valid arguments ?
	 if( ! $test ){
	     if( $ARGV[$i] ne "-c" ){
		 print "Invalid option or file name /$ARGV[$i]/ ignored\n";
	     }
	 }
     } else {
	 # Something else eventually unexpected or a filename. Note
	 # that the implementation of 2 scheme will not allow us to use
	 # variable overwrite as before but rather assign the first list
	 # as inputFiles, second list as outputFiles.
	 if( $HPSS::FILIN eq ""){
	     $HPSS::FILIN	= $ARGV[$i];
	 } else {
	     $HPSS::FILOUT	= $ARGV[$i];
	 }

     }
    }

    # Check date validity. Manipulate
    &debug_message("get_args","Debug mode is --ON--\n\n",
		   "Current Date/Time   ".localtime()."\n");

    &debug_message("get_args","Converted in        $HPSS::CDATE\n",
		   "Chosen expiration   $HPSS::DATE\n");

    if( $HPSS::DATE le $HPSS::CDATE){
	# Hum !! Trying to trick me or what ???
	&die_message("get_args",
		     "Cannot set expiration date <= current date/time\n");
    } else {
	$HPSS::DATE =~ s/://g;
    }

    # This extra editing was added on Apr 2001
    # It's actually being nice on users who forgets to specify an
    # output file.
    if($HPSS::FILOUT eq ""){
	$HPSS::FILOUT = $HPSS::FILIN;
	$HPSS::FILOUT =~ s/.*\///g;
	$HPSS::FILOUT = $HPSS::PPATH."/".$HPSS::FILOUT;
	#print "DEBUG :: $HPSS::FILOUT\n";
    }

    &debug_message("get_args",
		   "DataBaseRef         $HPSS::DDBREF\n",
		   "DDBUser             $HPSS::DDBUSER\n",
		   "DDBPasswd           $HPSS::DDBPASSWD\n",
		   length($HPSS::FILIN) <255?"HPSS File(s)        $HPSS::FILIN\n" :"HPSS File(s)        (many)\n",
		   length($HPSS::FILOUT)<255?"Restore File(s)     $HPSS::FILOUT\n":"Restore File(s)     (many)\n",
		   "Raw date            $HPSS::DATE\n",
		   &UnixDate($HPSS::DATE,
			     "Expiration          %b %e %Y at %T\n"),
		   "Group               $HPSS::GROUP\n",
		   "Update              $HPSS::UPDATE\n");


    # Return an array of values
    ($HPSS::FILIN,$HPSS::FILOUT,$HPSS::GROUP,$HPSS::DATE,$Life);
}


sub	arg_present
{
 my($string,$subst) = @_;

 # Make the option case-insensitive
 #(index(lc($string),lc($subst)) != -1);
 (index($string,$subst) != -1);

}

sub     hpss_copyright
{
  print "\n";
  print " Copyright\n ----------\n  This tool suite is free software; ";
  print "you can redistribute it and/or modify\n  it under the terms o";
  print "f the GNU General Public License as published by\n  the Free ";
  print "Software Foundation; either version 2 of the License, or\n  (";
  print "at your option) any later version.\n\n  This program is distr";
  print "ibuted in the hope that it will be useful,\n  but WITHOUT ANY";
  print " WARRANTY; without even the implied warranty of\n  MERCHANTAB";
  print "ILITY or FITNESS FOR A PARTICULAR PURPOSE.  \n  See the GNU G";
  print "eneral Public License for more details.\n\n  You should have ";
  print "received a copy of the GNU General Public License\n  along wi";
  print "th this program; if not, write to the Free Software\n  Founda";
  print "tion, Inc., 59 Temple Place, Suite 330, \n  Boston, MA  02111";
  print "-1307  USA\n\n ----------------------------------------------";
  print "-----------------------------\n Copyright 1998-2000 (c) Jerom";
  print "e Lauret <jlauret at mail.chem.sunysb.edu>\n Department of Ch";
  print "emistry, State Uiversity of New York \@ Stony Brook\n\n Copyrig";
  print "ht 2000-2020 (c) Jerome Lauret <jlauret at bnl.gov>\n STAR Co";
  print "llaboration, Brookhaven National Laboratory\n ---------------";
  print "------------------------------------------------------------\n";
  print "";

  print "\n";
  print "\nDisclaimer\n----------\n   IN NO EVENT SHALL THE AUTHORS OR";
  print " DISTRIBUTORS BE LIABLE TO ANY PARTY\n   FOR DIRECT, INDIRECT";
  print ", SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES\n   ARISING O";
  print "UT OF THE USE OF THIS SOFTWARE, ITS DOCUMENTATION, OR ANY\n  ";
  print " DERIVATIVES THEREOF, EVEN IF THE AUTHORS HAVE BEEN ADVISED O";
  print "F THE\n   POSSIBILITY OF SUCH DAMAGE.\n\n   THE AUTHORS AND D";
  print "ISTRIBUTORS SPECIFICALLY DISCLAIM ANY WARRANTIES,\n   INCLUDI";
  print "NG, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABI";
  print "LITY,\n   FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEM";
  print "ENT.  THIS SOFTWARE\n   IS PROVIDED ON AN \"AS IS\" BASIS, AN";
  print "D THE AUTHORS AND DISTRIBUTORS HAVE\n   ** NO OBLIGATION ** T";
  print "O PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, \n   O";
  print "R MODIFICATIONS.\n\n";

}

sub	hpss_user_help
{
    # Will have more later
    print " "; for ($i=0 ; $i < 75 ; $i++){ print "-";} ; print "\n";
    print "<DataCarousel HPSS module version $HPSS::VERSION>\n";
    # ----
  print "\nUsage is %% hpps_user.pl [option] args...\n\n where args st";
  print "ands for one of the following syntaxes\n     HPSSFile1[,...] ";
  print "TargetFile1[,...]\n     -f InputDescriptionList\n     -r Rest";
  print "orePath Filename1[,...]\n     -r RestorePath -f InputDescript";
  print "ionList\n\n i.e.   you  can  easer  use  a  list of path full";
  print "y specified 'HPSSFile' and\n 'TargetFile' file names on the c";
  print "ommand line or having this  combination  of\n input/output  w";
  print "ritten  to a text file 'InputDescriptionList'.  In this last\n";
  print " case, the InputDescriptionList will contain, on each line, a";
  print " combination of\n 'HPSSFile 'TargetFile'.\n\n The second argu";
  print "ment (that is 'TargetFile') or the second column (in case of\n";
  print " a description list) is not mandatory ; you can use the -r op";
  print "tion flag which\n will  tell  the  script to use the specifie";
  print "d restore path for all requested\n 'HPSSFilename' files i.e. ";
  print " you will store them  all  in  the  final  target\n directory";
  print ".\n\nOptions are\n       -t date       specify a default entr";
  print "y time for reporting\n       -T date       specify a default ";
  print "expiration time \n\n       -l time       specify a request li";
  print "fetime in HPSS (in seconds)\n       -g Grp        request res";
  print "toration under group name 'Grp'\n\n       -k            perfo";
  print "rms a fake submission (usefull for checking first)\n       -a";
  print "            append record (even  if  already in under  anothe";
  print "r uid)\n       -q            requeue Failed entries only\n   ";
  print "    -z            zeroes  record's  status (i.e.  forces  ent";
  print "ry status to\n                     new)\n\n       -d         ";
  print "   turns on debugging\n\n       -c            Shows copyright";
  print " and disclaimer information\n       -w            Shows queue";
  print "  status i.e. what is  in  progress  in the \n               ";
  print "      system\n       -s            Shows server side messages";
  print " (DataCarousel status)\n       \n       -h            Shows t";
  print "his help and continue\n\n\nOption you need to \"think\" about";
  print " before using\n       -e            Erase i.e. mark record(s)";
  print " as deleted if they are new or\n                     requeued";
  print ". Deleted records CANNOT be recovered using  -q\n            ";
  print "         but only by using -z \n       -q            Enters o";
  print "nly records which have failed before\n\nThose options should ";
  print "already be automatically setup\n       -r Path       to speci";
  print "fy an alternate restore path\n       -b Path       to specify";
  print " an HPSS relative path\n       -n DDref      DDB reference na";
  print "me name.\n       -U UserName   UserName to use for mysql acce";
  print "ss.\n       -P PassWord   PassWord to use for mysql access.\n\n";
  print "Date format. All the following are valid :\n  today\n  1st th";
  print "ursday in June 1992\n  05/10/98\n  12:30 Dec 12th 1880\n  8:0";
  print "0pm december tenth\n  +3 days\n  +3hours 12minutes 6 seconds\n";
  print "\n Dates  are expected to be specified as one string i.e.  yo";
  print "u must use quotes\n when the date contains several words ...\n";
  print "";

    # ----
    print " "; for ($i=0 ; $i < 75 ; $i++){ print "-";} ; print "\n";
}



# ----------------------------------------------------------------------
# Declare/Get/Set the variables for this package.
# ----------------------------------------------------------------------
sub	hpss_toggle_debug
{
    my($s)=@_;

    if ( defined($s) ){
	$HPSS::DEBUG = $s;
    } else {
	if($HPSS::DEBUG){
	    # Turn it OFF
	    $HPSS::DEBUG = (1==0);
	} else {
	    # Turn it ON
	    $HPSS::DEBUG = (1==1);
	}
    }
    return $HPSS::DEBUG;
}

# get variable value externally.
sub	hpss_get_value
{
    my($name) = @_;
    my($val);

    $name = &hpss_name_to_var($name);

    eval("\$val = \$HPSS::$name");
    if(!defined($val)){
	&info_message("get_ddb_parameter","Parameter $name does not exists\n");
	"";
    } else {
	$val;
    }
}
sub	hpss_set_value
{
 my($name,$val) = @_;

 $name = &hpss_name_to_var($name);
 &debug_message("set_value","$name -- is --> $val\n");
 if( int($val) eq $val || !defined($val)){
     eval("\$HPSS::$name = $val");
 } else {
     eval("\$HPSS::$name = \"$val\"");
 }
}

# Macro hidding private variables but making them available.
sub hpss_get_clean_method {            $HPSS::PARAM{"CLEAN"};}

# Returns any paramaters defined by name from the Parameter
# table. List is kept in AAAREADME.
sub hpss_get_parameter {
    my($param)=@_;

    # if it was defined
    if ( defined($HPSS::PARAM{$param}) ){
	return $HPSS::PARAM{$param};
    } else {
	# Well, we may have called this too early on
	if ( ! defined($HPSS::PARAM{"RETRY"}) ){
	    # if a default parameter is not even defined, open_db was
	    # unlikely called so try a recursive call.
	    if ( &hpss_load_params() ){
		return &hpss_get_parameter($param);
	    } else {
		return undef;
	    }
	}
	return undef;
    }
}

sub hpss_set_parameter
{
    my($Obj,$param,$val)=@_;
    my($cmd,$sth0,$sth1,$pval);

    if ( $Obj == 0){
	&info_message("set_parameter","No db Object handler\n");
	return 0;
    }
    #&info_message("set_parameter","Passing test\n");
    $cmd    = "SELECT Value FROM Parameters WHERE Name=\"$param\"";
    $sth0   = $Obj->prepare($cmd);

    if($sth0){
	#&info_message("set_parameter","Executing\n");
	$sth0->execute();
	$pval = $sth0->fetchrow();

	#&debug_message("set_parameters","OK, got pval=$pval\n");

	if ( ! defined($pval) ){
	    # the there are no parameters named $param
	    #&info_message("set_parameters","pval is undefined, inserting ($param,\"$val\")\n");
	    $cmd  = "INSERT INTO Parameters VALUES(0,\"$param\",\"$val\")";
	    $sth1 = $Obj->prepare($cmd);
	    if ( ! $sth1->execute() ){
		&info_message("set_parameters","Error occured on insert ".$sth1->errstr()."\n");
	    }
	    $sth0->finish();
	    $sth1->finish();

	} else {
	    $cmd  = "UPDATE Parameters SET Value=\"$val\" WHERE Name=\"$param\"";
	    $sth1 = $Obj->prepare($cmd);
	    if ( ! $sth1->execute() ){
		&info_message("set_parameters","Error occured on update ".$sth1->errstr()."\n");
	    }
	    $sth0->finish();
	    $sth1->finish();
	    return $pval;

	}
    } else {
	&info_message("set_parameter","Could not prepare statement [$cmd]\n");
    }
    return undef;
}


sub hpss_name_to_var
{
    my($name) = @_;

    $name = uc($name);
    $name =~ s/^\s*(.*?)\s*$/$1/;
    $name =~ s/\s+/ /g;
    $name =~ s/ /_/g;
    $name;
}


# Shortcut for server
sub	hpss_set_server_mode
{
 my($ref,$user,$passwd) = @_;
 return hpss_set_ddb_parameters(
 	undef,undef,undef,undef,# Filin/Filout/Date/Group
 	undef,1,0,		# Path/CreatePath/AppendMode
	$ref,$user,$passwd,	# DDBref/User/Passwd
	undef,1			# Debug/Update
	);
}


# Set DDBParameters externally.
sub	hpss_set_ddb_parameters
{
 my(@Vars) = @_;
 my($symb);

 # See value on top. MUST be modified.
 if($#Vars != $HPSS::MAXPARAMETERS && $#Vars != -1){
   $symb = ($#Vars < $HPSS::MAXPARAMETERS)?"<":">";
   &info_message("set_ddb_parameters",
   	"Suspicious Number of arguments $#Vars $symb $HPSS::MAXPARAMETERS\n");
 }

 # Get variables passed (but only if defined and non-null)
 $HPSS::FILIN   =       $Vars[0] unless( !defined($Vars[0]) );
 $HPSS::FILOUT  =       $Vars[1] unless( !defined($Vars[1]) );
 $HPSS::DATE    =       $Vars[2] unless( !defined($Vars[2]) );
 $HPSS::GROUP   =       $Vars[3] unless( !defined($Vars[3]) );

 $HPSS::PPATH   =       $Vars[4] unless( !defined($Vars[4]) );

 $HPSS::APPEND  =       $Vars[6] unless( !defined($Vars[6]) );
 $HPSS::DDBREF	=	$Vars[7] unless( !defined($Vars[7]) );
 $HPSS::DDBUSER =	$Vars[8] unless( !defined($Vars[8]) );
 $HPSS::DDBPASSWD =	$Vars[9] unless( !defined($Vars[9]) );

 $HPSS::DEBUG   =       $Vars[10] unless( !defined($Vars[10]) );
 $HPSS::UPDATE  =       $Vars[11] unless( !defined($Vars[11]) );


 # -- Default values setup if user did not pass anything
 # This extra editing breaks a bit the purpose of having
 # global variables and will be changed later on by using
 # temporary variables, then only putting them in the global
 # variables.
 $HPSS::FILIN	= "" unless( defined($HPSS::FILIN) );
 $HPSS::FILOUT	= "" unless( defined($HPSS::FILOUT) );
 $HPSS::GROUP	= "Star" unless( defined($HPSS::GROUP) );

 $HPSS::PPATH	= "//treat-as-rr.rcf.bnl.gov/dev/null"
			  unless ( defined($HPSS::PPATH) );

 $HPSS::DEBUG	= (1==0) unless( defined($HPSS::DEBUG) );
 $HPSS::UPDATE	= (1==0) unless( defined($HPSS::UPDATE) );

 # -- HardCoded (redundant?) DDB information.
 $HPSS::DDBREF  = "" unless( defined($HPSS::DDBREF));
 $HPSS::DDBUSER = "star_c_user" unless( defined($HPSS::DDBUSER) );
 $HPSS::DDBPASSWD= "VoyonsVoir" unless( defined($HPSS::DDBPASSWD) );

 if ( ! defined($HPSS::DATE) ){
     $HPSS::DATE = &DateCalc(&Today(),"+30 days");
     $HPSS::DATE =~ s/://g;
 }

 &debug_message("set_ddb_parameters",
		"FILIN        $HPSS::FILIN\n",
		"FILOUT       $HPSS::FILOUT\n",
		"DATE         $HPSS::DATE\n",
		"PPATH        $HPSS::PPATH\n",
		"DDBREF       $HPSS::DDBREF\n",
		"DDBUSER      $HPSS::DDBUSER\n",
		"DDBPASSWD    $HPSS::DDBPASSWD\n",
		"DEBUG        $HPSS::DEBUG\n",
		"UPDATE       $HPSS::UPDATE\n",
		"APPEND       $HPSS::APPEND\n");

}






# ----------------------------------------------------------------------
#        Checking path and file and database existence/validity
# ----------------------------------------------------------------------

sub	hpss_check_all
{
 my($mode) = @_;
 my(@sts);

 @sts	= (&hpss_check_file,&hpss_check_paths,&hpss_check_database);

 &debug_message("check_all",join(" ",@sts)."\n");
 &debug_message("check_all","Filename [$HPSS::FILIN][$HPSS::FILOUT]".
		" will not be accepted\n")                      if (!$sts[0]);
 &debug_message("check_all","Invalid/Non-Existing Path\n")	if (!$sts[1]);
 &debug_message("check_all","Database Fields undefined\n")	if (!$sts[2]);

 if ( ($mode != 1) || undef($mode) ){
  $status	= ($sts[0] && $sts[1] && $sts[2]);
  if($mode==2)	{	die "\n"					;}
  else 		{	return $status					;}
 } else {
  return ($sts[1] && $sts[2]);
 }
}


# This routine checks that the variable FILIN is defined.
sub	hpss_check_file
{
 if ($HPSS::FILIN  eq "" || ! defined($HPSS::FILIN) ||
     $HPSS::FILOUT eq "" || ! defined($HPSS::FILOUT)){
	0;
 } else {
 	1;
 }
}


# This routine doesnt do much. It's initial intent was to check if a given
# user/group was able to restore files. i.e. we had a group associated with
# a restoration path (like disk partition). We will not remove this routine
# in case this feature is restored.
sub	hpss_check_paths
{
    my($subdir);
    my($i,$path,$mask);
    my(@items,$j,$tmp);

    1;
}


# Checks that this script main variables are defined for DataBase access.
# Also, fixes global variables (i.e. in case hpss_set_value() has been called
# we need to reset some variables).
sub	hpss_check_database
{
 my($status,@items);

 $status = 1;

 # DDBSERVER as undef() is fine for connect()
 # DDBSPORT  as undef() is fine for connect()
 #print "--> $HPSS::DDBREF\n";
 if( $HPSS::DDBREF eq ""){
 	$HPSS::DDBREF = "DBI:mysql:$HPSS::DDBNAME";
 	if(defined($HPSS::DDBSERVER)){
		$HPSS::DDBREF  .= ":$HPSS::DDBSERVER";
  	}
	if(defined($HPSS::DDBPORT)){
		$HPSS::DDBREF  .= ":$HPSS::DDBPORT";
  	}
 } else {
	@items = split(":",$HPSS::DDBREF);
	if( index($HPSS::DDBREF,"DBI:mysql") == -1){
		$HPSS::DDBNAME = $items[0];
	} else {
		$HPSS::DDBNAME = $items[2];
	}
 }



 # Check user/password. Those will be a problem if !defined.
 if( !defined($HPSS::DDBUSER) ){
	&debug_message("check_database","mysql user is undefined\n");
	$status = (1==0);
 }
 if( !defined($HPSS::DDBPASSWD) ){
	&debug_message("check_database","mysql Password is undefined\n");
	$status = (1==0);
 }
 $status;
}





# ----------------------------------------------------------------------
#          Database Read/Write/Add/Delete/Modify record part
# ----------------------------------------------------------------------
# -----------------------
# Open/Close
# -----------------------
sub	hpss_open_database
{
    # HashArray left for compatibility reason (i.e. other ddb implementation
    # and old mysql version (just in case)). Also required for
    # other Hash-based DataBase modules.
    my(%DataBase) = @_;
    my($cmd1,$sth1);
    my($cmd2,$sth2);
    my($i);

    # Added mode=1 open and leave (no table check)
    if ( $HPSS::OMODE == 1){
	#print "Check called\n";
	&hpss_check_database();
    }


    # Information
    &debug_message("open_database",
		   "Opening $HPSS::DDBREF\n",
		   "User    $HPSS::DDBUSER\n",
		   "Passwd  $HPSS::DDBPASSWD\n");

    # Note that we still force AutoCommit in case the default changes ...
    $obj = DBI->connect($HPSS::DDBREF,$HPSS::DDBUSER,$HPSS::DDBPASSWD,
			{PrintError  => 0, AutoCommit => 1,
			 ChopBlanks  => 1, LongReadLen => 200});


    if(!$obj){
	# No object created. BAD ...
	&info_message("open_database",
		      "*** OpenFailure ***\n",
		      "DDBRef  $HPSS::DDBREF\n",
		      "User    $HPSS::DDBUSER\n",
		      "Reason ".$DBI::errstr);
	              #"Passwd  $HPSS::DDBPASSWD\n");
	return 0;
    }

    if ($HPSS::OMODE == 0){
	# Use prepare statments... We do a quick table opening
	# to check table existence and readability.
	# Table 0 will be done as well
	for($i = $#HPSS::DDBTBLINFO; $i >= 0 ; $i--){
	    $cmd1 = "SELECT id FROM $HPSS::DDBTBLINFO[$i] LIMIT 1";
	    &debug_message("open_database","$i will prepare/execute $cmd1\n");
	    $sth1 = $obj->prepare($cmd1);
	    if(!$sth1){
		&die_message("open_database",
			     "Cannot prepare select statment\n");
		return 0;
	    }
	    if($i != 0){ $sth1->finish();}
	}
	$HPSS::DDBTBLNAM = $HPSS::DDBTBLINFO[0];

	&debug_message("open_database","name of main table is [$HPSS::DDBTBLNAM]\n");


	# Grab Column Name
	&debug_message("open_database",
		       "Executing last sth $i [SELECT * FROM $HPSS::DDBTBLNAM LIMIT 1]\n");
	$sth1 = $obj->prepare("SELECT * FROM $HPSS::DDBTBLNAM LIMIT 1");
	$sth1->execute();
	if( $sth1->{NUM_OF_FIELDS} == 0 ){
	    print $obj->errstr;
	    &die_message("open_database","Table $HPSS::DDBTBLNAM has 0 column\n");
	    return 0;
	} else {
	    @HPSS::DDBINFO = @{ $sth1->{NAME} };
	    $sth1->finish();
	    # Build the reference to this i.e. an association between name and
	    # index number.
	    for ($i=0 ; $i <= $#HPSS::DDBINFO ; $i++){
		&debug_message("open_database","Field $i --> $HPSS::DDBINFO[$i]\n");
		$HPSS::DDBINFO_REF{uc($HPSS::DDBINFO[$i])} = $i;
	    }
	}

	if ( $HPSS::DIFFT == 0){
	    $cmd2 = "SELECT NOW()+0";
	    $sth2 = $obj->prepare($cmd2);
	    if($sth2){
		my($d1,$d2);
		$sth2->execute();
		$d1 = $sth2->fetchrow();
		$d2 = &Today();
		$d1 =~ s/\..*//g;
		$d2 =~ s/://g;
		$HPSS::DIFFT = &DateCalc($d1,$d2);
		#print "Diff is $HPSS::DIFFT \n";
	    }
	    $sth2->finish();
	}

	# Suck in some tables we need
	$cmd2 = "SELECT * FROM DiskLoc";
	$sth2 = $obj->prepare($cmd2);
	if($sth2){
	    $sth2->execute();
	    if($sth2){
		while( @res = $sth2->fetchrow_array() ){
		    $HPSS::NODES{$res[1]} = $res[2];
		}
		$sth2->finish();
	    }
	}

	# backward compat feature
	return undef if ( ! defined(&hpss_load_params($obj)));
    }

    # Everything was fine, return ddb object.
    return $obj;
}

sub hpss_load_params
{
    my($obj)=@_;
    my($close,$count);

    if ( ! defined($obj) ){
	$HPSS::OMODE = 1;
	$obj = &hpss_open_database();
	return undef if ( ! $obj);
	$close  = 1;
    } else {
	$close  = 0;
    }

    # default parameters - used to be a routine
    #
    # Default parameters. This will be the future way
    # of controlling the DataCarousel behavior without
    # resetting everything from scratch.
    #
    $HPSS::PARAM{"DEPTH"}   =   0;
    $HPSS::PARAM{"RETRY"}   =   5;
    # <--- end default parameters

    $count= 0;
    $cmd2 = "SELECT * FROM Parameters";
    $sth2 = $obj->prepare($cmd2);
    if($sth2){
	$sth2->execute();
	if($sth2){
	    while( @res = $sth2->fetchrow_array() ){
		# this may have happened on June 15th 2006
		if ( $res[2] !~ m/^\s*$/ ){
		    $HPSS::PARAM{$res[1]} = uc($res[2]);
		    $count++;
		} else {
		    $sth2->finish();
		    &info_message("open_database","Reading of $res[1] leaded to a null value\n");
		    $count = undef;
		}
	    }
	}
	$sth2->finish();
    }

    if ($close){
	&hpss_close_database($obj);
	$HPSS::OMODE = 0;
    }
    return $count;
}


# Close database i.e. write records and flush memory.
sub	hpss_close_database
{
 my($dbObj,%DataBase) = @_;

 # Reset this out
 $HPSS::OMODE = 0;

 # Close DataBase connection
 if ( $dbObj ){
     if( ! $dbObj->disconnect() ){
	 print $dbObj->errstr;
	 0;
     } else {
	 1;
     }
 } else {
     0;
 }
}



# -----------------------
# Modify Records
# -----------------------
# Warning : In this routine, DataBase is passed by reference.
# Obsolete usage for mysql but please, DO NOT REMOVE.
#
# This toutine returns the number of entries added BUT a number 0
# does not mean that things went wrong, it may mean that the entry
# was found in the db. To force
#
sub	hpss_add_record
{
    my($dbObj,$DataBase,$filin,$filout,$group,$date,$lifetime) = @_;
    #                                   ^^^^^^^^^^^^ can be undef

    my($entries,$i,$file,$ofile,$ppath,$hpathn);
    my($user,$lupdate);
    my($rgroup,$rdate,$ruser);
    my($grpnum,$err,@info,@all,$j);
    my($sth1,$sth2,$sth3,$cmd);

    my($RFile,$RPathn,$RNode,$status);
    my(@Files,@Ofile);
    my($val);

    if ( ! $dbObj ){
	&die_message("add_record","Method called without a DB handle\n");
    }

    # Init restored path.
    $user  = &GetLogin();
    $ruser = $user;
    if($user eq ""){
	&info_message("add_record","Bogus NULL string user received\n");
	return 0;
    }

    # Fix values if undefined
    if(!defined($group) ){
	$group = $HPSS::GROUP;
	&info_message("add_record","Using default group [$group]\n");
    }
    # Now revert to usable group string.
    $group = $HPSS::GROUP if ($group eq "*" || $group eq "");

    # same fix with date although this can happen at this stage only
    # if one (like a Pavel) is using the interface outside the wrapper
    if ( ! defined($date) ){
    	$date = &DateCalc(&Today(),"+30 days");
	$date =~ s/://g;
    }

    # Time 0 is unfinit life (until done)
    if ( ! defined($lifetime) ){  $lifetime = 0;}


    # Check content. Allow for file list
    $entries	= 0;

    # Prepare statment. Faster for multiple files. The above format implicitly
    # fixes the number of columns in DDBTBLNAM table.
    $cmd	= "INSERT INTO $HPSS::DDBTBLNAM values(NULL,?,?,?,?,0,?,NOW(),?,?,0,?,?)";
    $sth1	= $dbObj->prepare($cmd);
    $cmd        = "UPDATE LOW_PRIORITY $HPSS::DDBTBLNAM SET Status=? WHERE id=?";
    $sth3       = $dbObj->prepare($cmd);
    $cmd        = "SELECT * FROM $HPSS::DDBTBLNAM WHERE SourceID=? AND DestinationID=? AND NodeID=?";
    $sth2       = $dbObj->prepare($cmd);

    if( ! $sth1 || ! $sth2 || ! $sth3){
  	&info_message("add_record",
		      "DataBase manipulation Statements could not be prepared\n",
		      " [".$dbObj->errstr."]\n");
	return 0;
    }



    # The splitting of $filin does not ensure that the list is in a correct
    # format. User may send something like ",," or -f will append a leading
    # ",". We want to avoid empty string insertion ...
    # New scheme requires that the file list Input/Output matches each other
    # i.e. same number of elements.
    @Files = split(",",$filin);
    @Ofile = split(",",$filout);

    if($#Files != $#Ofile){
	&debug_message("add_record","Unmatched Input/Output file list\n");
	return 0;
    }


    for($i=0 ; $i <= $#Files ; $i++){
	# Sort out path (numerical) and file name.
	# Both above functions will render parsing much more flexible because
	# unlike URI module and all of that fancy stuff, it will parse and add
	# missing parts.
	$lupdate               = (1==0);
	($file,$hpathn)        = &hpss_split_hpath($Files[$i]);
	($RFile,$RPathn,$RNode)= &hpss_split_uri($Ofile[$i],$file);


	&debug_message("add_record",
		       "file  = $file\n",
		       "hpathn= $hpathn\n",
		       "RFile = $RFile\n",
		       "RPath = $RPathn\n",
		       "RNode = $RNode\n");


	if( ($file ne "") &&  ($hpathn ne "") &&
	    ($RFile ne "") && ($RPathn ne "") && ($RNode ne "") ){

	    # Simple first pass. We have to do the duplicates by hand. It will based on
	    # remote-restore duplication only (same node, same path).
	    # BTW : The above are repretitive commands and should be replaced by a routine.

	    # Enter Sources
	    $val = &from_record_and_fetch_in("add_record",
					     "Sources","$hpathn$file",$dbObj,1);
	    if( $val != 0){
		$info[&hpss_infoidx("SourceID")] = $val;
	    }

	    # Enter Destination ID
	    $val = &from_record_and_fetch_in("add_record",
					     "Destinations","$RPathn$RFile",$dbObj,1);
	    if( $val != 0){
		$info[&hpss_infoidx("DestinationID")] = $val;
	    }

	    # Enter Node ID
	    $val = &from_record_and_fetch_in("add_record",
					     "NodeInfo","$RNode",$dbObj,1);
	    if( $val != 0){
		$info[&hpss_infoidx("NodeID")] = $val;
	    }

	    #
	    # For group ID, we will fetch ONLY i.e. user will NOT have control
	    # over that table. Administrator will have now to enter groups
	    # in the GrpInfo table via the add_group.pl script provided.
	    #
	    $val = &from_record_and_fetch_in("add_record",
					     "GrpInfo","$group",$dbObj,0);
	    if($val == 0){
		&die_message("add_record","Group [$group] is undefined. If you would\n",
			     "like to have this group defined, please, contact the\n",
			     "Carousel software administrator\n");
	    } else {
		$info[&hpss_infoidx("GroupID")] = $val;
	    }



	    # Note that at this level, and because we used the IGNORE directive
	    # and sql table Auto-Increment no-duplicate, all the above items are now
	    # associated with IDs we need to recover.
	    # Complete the @info array .. not all necessary
	    $info[&hpss_infoidx("id")]        = 0;       # Auto-increment
	    $info[&hpss_infoidx("User")]      = $ruser;
	    $info[&hpss_infoidx("UpdUsr")]    = $user;
	    $info[&hpss_infoidx("EntryDate")] = 0;       # Updated by msql
	    $info[&hpss_infoidx("Expires")]   = $date;
	    $info[&hpss_infoidx("Status")]    = 0;
	    $info[&hpss_infoidx("Retries")]   = 0;
	    $info[&hpss_infoidx("DCLifeTime")]= $lifetime;


	    # -=-=-=-
	    # BEFORE entering this record, we WILL check if it is duplicated.
	    # -=-=-=-
	    if( ! $sth2->execute($info[&hpss_infoidx("SourceID")],
				 $info[&hpss_infoidx("DestinationID")],
				 $info[&hpss_infoidx("NodeID")]) ){
		&info_message("add_record","Cannot execute Duplicate Record statement\n");
	    } else {
		# We have sucessfully executed this statement ; get record now
		@all = $sth2->fetchrow();


		if( $#all != -1) {
		    # This record is already IN the Database.
		    &debug_message("add_record","--- Similar record in our database\n");


		    # This check is to be done ahead. It will be done
		    # regardless of FAILED flag.
#		    if ( $HPSS::CHECKS ){
#			$val =
#			    &from_record_and_fetch_in("add_record",
#						      "Destinations",
#						      $all[&hpss_infoidx("DestinationID")],
#						      $dbObj,
#						      -1);
#			if ( ! -e $val ){
#			    $lupdate = (1==1);
#			    &debug_message("add_record"," $val status=".$all[&hpss_infoidx("Status")]."\n");
#			}
#		    }


		    # Did the user used -upd, -a, -e, -q options ?
		    # Note that ALL modification to record are done ONLY IF the
		    # user ID is the same.
		    if (  ( $all[&hpss_infoidx("User")] eq $info[&hpss_infoidx("User")] &&
			    ($HPSS::UPDATE    ||
			     $HPSS::DELENT    ||
			     ($HPSS::FAILED && ($lupdate || $all[&hpss_infoidx("Status")] == 3))
			    )
			   )  ||
			  $HPSS::APPEND ) {

			# fake must be first
			if($HPSS::FAKE){
			    print "$hpathn$file $HPSS::PROTO://$ruser\@$RNode$RPathn$RFile\n";
			} else {
			    if( $HPSS::DELENT ){
				# print "Marking entry $all[0] with status=36\n";
				if ( $all[&hpss_infoidx("Status")] == 0 || $all[&hpss_infoidx("Status")] == 4){
				    $entries += &EnterRecord("DELENT",$sth3,36,@all);
				}
			    } elsif ( $HPSS::UPDATE ) {
				$info[&hpss_infoidx("id")] = $all[&hpss_infoidx("id")];
				$entries += &EnterRecord("UPDATE",$sth3,0,@info);
			    } else {
				# append
				$entries += &EnterRecord("APPEND",$sth1,-1,@info);
			    }
			}
		    } else {
			if($HPSS::FAKE){
			    print "# $hpathn$file $HPSS::PROTO://$ruser\@$RNode$RPathn$RFile\n";
			} else {
			    print "----- Already requested for restore ----\n\n";
			    printf "%15s %s\n","User",$all[&hpss_infoidx("User")];
			    printf "%15s %s\n","Source",$hpathn.$file;
			    $val =
				&from_record_and_fetch_in("add_record",
							  "Destinations",
							  $all[&hpss_infoidx("DestinationID")],
							  $dbObj,
							  -1);
			    printf("%15s %s\n","Destination",defined($val)?$val:"unknown");

			    $val =
				&from_record_and_fetch_in("add_record",
							  "NodeInfo",
							  $all[&hpss_infoidx("nodeID")],
							  $dbObj,
							  -1);
			    printf("%15s %s\n","Node",defined($val)?$val:"unknown");

			    # EntryData is in DB time (whatever timezone) - We need to
			    # subtract local now() and $HPSS:DBNOW .
			    #printf("%15s %s\n","EntryDate",
			    #	   &UnixDate($all[&hpss_infoidx("EntryDate")],"%b %e %Y at %T"));
			    #print "DEBUG ".&hpss_infoidx("EntryDate")."\n";
			    #print "DEBUG ".$all[&hpss_infoidx("EntryDate")]."\n";
			    if ( $all[&hpss_infoidx("EntryDate")] eq "0000-00-00 00:00:00"){
				printf("%15s %s\n","EntryDate","?");
			    } else {
				printf("%15s %s\n","EntryDate",
				       &UnixDate(&DateCalc($all[&hpss_infoidx("EntryDate")],$HPSS::DIFFT),
						 "%b %e %Y at %T"));
			    }

			    printf("%15s %s\n","Expires",
				   &UnixDate($all[&hpss_infoidx("Expires")],"%b %e %Y at %T"));
			    printf("%15s %s %s\n","Status",
				   &hpss_status_string($all[&hpss_infoidx("Status")]),
				   $lupdate?"(not visible)":"");

			    if( $all[&hpss_infoidx("User")] eq $info[&hpss_infoidx("User")] ){
				print("\n----- Use -z to requeue all, -q to requeue Failed entries\n\n");
			    } else {
				print("\n----- Use -a to append (user differs from original)\n\n");
			    }
			} # fake or real stuff
		    }     # same user name + update/erase/queue mode or not

		} else {
		    # This record is entirely new OR saved under a different
		    # user name. But we don't want to accidently add
		    # one in DELENT mode.
		    if( ! $HPSS::DELENT ){
			$entries += &EnterRecord("DELENT (new)",$sth1,-1,@info);
		    }
		}
	    }
	}             # Test on non-empty file name (restrict syntax)
    } # Loop over all files


    # Destroy handlers
    $sth1->finish();


    # Return the number of records successfully added
    &debug_message("add_record","Returning NumberOfEntry(ies) $entries\n");
    $entries;
}

# Enter record @info , sentence $sth is already prepared and tested
# for accessibility. Note the late update which changes the status.
#  Status -1 -> add an entry
#  Status x  -> set to status x
#
sub EnterRecord
{
    my($mode,$sth,$status,@info) = @_;
    my($lsts);

    if( $status == -1 ){
	$lsts =  $sth->execute($info[&hpss_infoidx("SourceID")],
			       $info[&hpss_infoidx("DestinationID")],
			       $info[&hpss_infoidx("GroupID")],
			       $info[&hpss_infoidx("NodeID")],
			       $info[&hpss_infoidx("User")],

			       $info[&hpss_infoidx("Expires")],
			       $info[&hpss_infoidx("DCLifeTime")],
			       $info[&hpss_infoidx("UpdUsr")],
			       $info[&hpss_infoidx("Retries")]);
    } else {
	$lsts = $sth->execute($status,
			      $info[&hpss_infoidx("id")]);
	#print " Statuses for ".$info[&hpss_infoidx("id")]." [".$sth->state."]\n";
    }

    if( ! $lsts){
	&info_message("EnterRecord","Failed to ".($status==0?"add":"update").
		      " record for $mode. Reason follows\n",
		      "[".$sth->errstr."]\n");
	return 0;
    } else {
	return 1;
    }
}


# -----------------------
# get/set/delete file(s)
# -----------------------
# get a list of files from database
sub	hpss_get_files
{
    my($dbObj,$DataBase,$status,$max,$cond) = @_;
    my($pstatus,$i,$cmd,$xcmd,$sth,$sthu,@res,@files);
    my($rv,$rt,$bys);
    my($lmt,$grp);
    my($user,@Users,%Ucount);
    my($group,@Groups,@GroupsW);
    my(%GUList,%UCount);
    my($method,$imethod,$dateC);
    my($tsort,$uinfo);
    my($prtmsg,$nrows);

    # maximum number of files per request
    $max    = $HPSS::NUMFILES unless defined($max);
    $prtmsg = $status==0;

    # be sure of undefining this
    undef(@files);

    # be sure we have a positive number always
    $pstatus = $status>0?$status:(-$status+1000);

    # Prepare a list of unique group. This will be the base of our later
    # fare-share. It makes sens only on status=0 cases.
    # NOTE : If the Database gets corrupted with illegal entries, the
    #  user-based fare share will return a lower number than expected
    #  because the selection on record is more strict than the selection
    #  on the number of users. This could be fixed in a garbagge-collection
    #  routine.
    $sth = $dbObj->prepare("SELECT * from CUsers");
    if ( $sth->execute() ){
	# previous operation did not finish ??
	$sth->finish();
	&info_message("get_files","Found CUsers (should have been deleted) - previous operation not done\n");
	$dbObj->do("DROP TABLE IF EXISTS CUsers");
	return @files;
    }

    $rt    = $HPSS::PARAM{"RETRY"};
    # however, if status = 4, we should not -- TODO
    # the reason is that we get_files() with status 4, then set_files will do retries+1
    # and set to 0. Then logic will do <= $rt and records will be left.
    # 
    $rt-- if ( $status == 4);

    $HPSS::CDATE =~ s/://g;
    $dateC = "$HPSS::DDBTBLNAM.Expires > $HPSS::CDATE ";
    &info_message("get_files","Will use only Expires > $HPSS::CDATE\n") if ( ! defined($cond) && $prtmsg );

    if($status == 0){
	# create CUsers / CGroups
	$dbObj->do("DROP TABLE IF EXISTS CUsers");
	$dbObj->do("DROP TABLE IF EXISTS CGroups");

	$rv = $dbObj->do("CREATE TABLE CGroups ( GroupID INT UNSIGNED NOT NULL, ".
			 "Name CHAR(64), Weight INT, COUNT INT UNSIGNED, PRIMARY KEY(GroupID))");
	if ( ! $rv ){  
	    &info_message("get_files","Creating CGroups failed [".$DBI::errstr."]\n"); 
	    return undef;
	}
	$rv = $dbObj->do("CREATE TABLE CUsers ( User char(15) NOT NULL, ".
			 "GroupID INT UNSIGNED NOT NULL, COUNT INT UNSIGNED, PRIMARY KEY(User, GroupID))");
	if ( ! $rv ){  
	    &info_message("get_files","Creating CUsers failed [".$DBI::errstr."]\n");  
	    return undef;
	}



	# fill CUsers
	$rv = $dbObj->do("INSERT INTO CUsers SELECT ".
			 "$HPSS::DDBTBLNAM.UpdUsr, $HPSS::DDBTBLNAM.GroupID, COUNT($HPSS::DDBTBLNAM.UpdUsr) ".
			 "FROM $HPSS::DDBTBLNAM WHERE $HPSS::DDBTBLNAM.Status=0 ".($dateC eq ""?"":"AND $dateC ").
			 "AND $HPSS::DDBTBLNAM.Retries <= $rt ".
			 "GROUP BY $HPSS::DDBTBLNAM.UpdUsr");
	if ( ! $rv ){  
	    &info_message("get_files","Insert in CUsers failed [".$DBI::errstr."]\n"); 
	    $dbObj->do("DROP TABLE IF EXISTS CUsers");
	    return undef;
	}


	# fill CGroups
	$rv = $dbObj->do("INSERT INTO CGroups SELECT ".
			 "$HPSS::DDBTBLNAM.GroupID, GrpInfo.Name, GrpInfo.Weight, COUNT($HPSS::DDBTBLNAM.GroupID) ".
			 "FROM $HPSS::DDBTBLNAM, GrpInfo  WHERE $HPSS::DDBTBLNAM.Status=0 ".($dateC eq ""?"":"AND $dateC ").
			 "AND GrpInfo.id=$HPSS::DDBTBLNAM.GroupID AND $HPSS::DDBTBLNAM.Retries <= $rt ".
			 "GROUP BY $HPSS::DDBTBLNAM.GroupID");
	if ( ! $rv ){  
	    &info_message("get_files","Insert in CGroups failed [".$DBI::errstr."]\n"); 
	    $dbObj->do("DROP TABLE IF EXISTS CGroups");
	    return undef;
	}


	$sth = $dbObj->prepare("SELECT * from CUsers");
	$sth->execute();
	if( $sth ){
	    while( @res = $sth->fetchrow_array() ){
		push(@Users,$res[0]);
		if ( ! defined($GUList{$res[1]}) ){   $GUList{$res[1]}  = $res[0]; }
		else {	                              $GUList{$res[1]} .= ",".$res[0];}
		if ( ! defined($UCount{$res[0]}) ){   $UCount{$res[0]}  = $res[2];}
		else {                                $UCount{$res[0]} += $res[2];}
	    }
	}
	&debug_message("get_files","Found $#Users users\n");

	$sth = $dbObj->prepare("SELECT * from CGroups");
	$sth->execute();
	if( $sth ){
	    while( @res = $sth->fetchrow_array() ){
		push(@Groups ,$res[0]);
		push(@GroupsW,$res[2]);
	    }
	}
	&debug_message("get_files","Found $#Groups groups\n");

	$sth->finish();
    }

    #
    # Prepare this table. Its format MUST match $HPSS::DDBTBLNAM format
    #
    $dbObj->do("DROP TABLE IF EXISTS Sorted_$pstatus");
    $cmd =
	"CREATE TABLE Sorted_$pstatus (id INT UNSIGNED NOT NULL AUTO_INCREMENT, ".
	" SourceID INT UNSIGNED NOT NULL, DestinationID INT UNSIGNED NOT NULL, ".
	" GroupID INT UNSIGNED NOT NULL, NodeID INT UNSIGNED NOT NULL, ".
	" LocID INT NOT NULL DEFAULT '0', ".
	" User CHAR(15), EntryDate TIMESTAMP, Expires TIMESTAMP, DCLifeTime SMALLINT, ".
	" Status SMALLINT, UpdUsr CHAR(15), Retries INT UNSIGNED DEFAULT '0', ".
	"PRIMARY KEY(id)) ENGINE=InnoDB";
    $rv  = $dbObj->do($cmd);
    if ( ! $rv ){  
	&info_message("get_files","Creation of Sorted_$pstatus failed [".$DBI::errstr."]\n");
	&info_message("get_files","$cmd\n");
	&hpss_clean_state($dbObj);
	&die_message("get_files","Fatal error $DBI::errstr\n");
	#return undef;
    }

    # The next table is really our own packing.
    $dbObj->do("DROP TABLE IF EXISTS Selected_$pstatus");
    #+
    #    0 id
    #    1 source
    #    2 detination
    #    3 user
    #    4 node
    #    5 lifetime
    #    6 locID for bookeeping [not used]
    #-
    $cmd =
	"CREATE TABLE Selected_$pstatus (id INT UNSIGNED NOT NULL,".
	" Sources TEXT NOT NULL, Destination TEXT NOT NULL,".
	" User CHAR(15) NOT NULL, Node TEXT NOT NULL, DCLifeTime SMALLINT, ".
	" LocID INT NOT NULL DEFAULT '0', ".
	"PRIMARY KEY(id)) ENGINE=InnoDB";
    $rv  = $dbObj->do($cmd);
    if ( ! $rv ){  
	&info_message("get_files","Creation of Selected_$pstatus failed [".$DBI::errstr."]\n");
	&info_message("get_files","$cmd\n");
	&hpss_clean_state($dbObj);
	&die_message("get_files","Fatal error\n");
	# return undef;
    }



    # We will execute several statements without checks. The final table selection
    # will tell us if it was built or not.

    # Note :
    # The initial intent was to sort by SourceID so we can restore a file
    # requested several times in multiple place at a time. Unfortunatly,
    # this has a critical side effect : files requested N-days ago and requested
    # again will suddenly have high priority over any other submission.
    # Of course, later improvements already fixed that up by warning the user
    # of multiple restore ... Also, the logic by which a user A would be able
    # to update an entry from user B was rendered impossible so, sorting by
    # SourceID does not make sens at all I would say ... The only time it would
    # matter is when one user request a file multiple times and under different
    # target names AND at different period. Well, cannot catch it all ...
    #
    # But this logic remained as-is until July 2001.
    $xcmd  = "";
    $uinfo = "";
    $tsort = 0;

    if($status >= 0){
	# default mode
	$cmd  = "INSERT INTO Sorted_$pstatus SELECT * FROM $HPSS::DDBTBLNAM WHERE Status=$status ";
	$cmd .= "AND Retries <= $rt ";
	$cmd .= "AND $dateC " if ($dateC ne "");

	# This is a "rough" mode as ordering will not be strict
	# enough
	if( $HPSS::PARAM{"ORDER"} eq "TAPEID"){
	    if( $HPSS::PARAM{"TSORT"} eq "SOFTID"){
		# SOFTID tries to compensate for the previous issue by sorting by
		# date ASC first but the date is truncated hence, the LocID within
		# an hour window is still possible.
		$tsort = 1;
		&info_message("get_files","ORDER=TAPEID (SOFTID) activated\n") if ($prtmsg);
		$xcmd = " ORDER BY DATE_FORMAT(EntryDate,'%Y-%m-%d %H'), LocID ASC";

	    } elsif( $HPSS::PARAM{"TSORT"} eq "TSLIDER"  ||
		     $HPSS::PARAM{"TSORT"} eq "TSLIDERX"    ){
		#  This is similar in spirit than the above but the granularity can
		# be made in seconds. In this case, the grouping is 2700 DESC (oldest
		# first) and within that window, the LocID are still sorted ...
		$tsort = 1;
		&info_message("get_files","ORDER=TAPEID (TSLIDER with slide=".(2700/60)." mnts) activated\n") if ($prtmsg);
		$xcmd = " ORDER BY ".
		        "  ((UNIX_TIMESTAMP( NOW() ) - UNIX_TIMESTAMP( Entries.EntryDate )) DIV 2700) DESC, ".
			"  LocID";

	    } else {
		# Initial sorting by LocID and EntryDate second will unfortunately
		# privilege the tapeID with smaller number and only then consider
		# the EntryDate. This is not fair but a possible algo.
		$tsort = 1;
		&info_message("get_files","ORDER=TAPEID activated\n") if ($prtmsg);
		$xcmd = " ORDER BY LocID, EntryDate ASC";
	    }

	} else {
	    $xcmd = " ORDER BY EntryDate ASC";

	}

    } elsif ( defined($cond) ) {
	# including negative status selection
	$cmd  = "INSERT INTO Sorted_$pstatus SELECT * FROM $HPSS::DDBTBLNAM WHERE $cond ";

    } else {
	# Hum. That sound like an illegal combo to me.
	&info_message("get_files","Unsuported Status=$status. Provide a condition\n");
	return undef;

    }
    &debug_message("get_files","Statement before method SHARE is $cmd\n");



    $imethod = $method = $HPSS::PARAM{"SHARE"};
    if( ! defined($method) ){ $method = "DEFAULT";}  # if not defined
    if( $method eq "")      { $method = "DEFAULT";}  # or defined as a null string
    if( $max <= 0)          { $method = "DEFAULT";}  # or if we asked for all records
    $uinfo .= "Sharing method=$method ".($tsort?"(+tapeID)":"")." -> ";

  SMETHODS:
    if ( $method eq "EQUAL" ){
	if( $#Users  <= 0){
	    &info_message("get_files","Method EQUAL but NUsers=".($#Users+1)." . Reverting to DEFAULT\n") if ($prtmsg);
	    $method = "DEFAULT";
	    goto SMETHODS;
	}

	&hpss_change_hpss_batch_policy($dbObj,0) if ($prtmsg);

	# Distributes entries. EQUAL share by users.
	$bys = int($max/($#Users+1)+0.5);
	if ($bys <= 0){ $bys = 1;}
	#if ($tsort){    $bys = $bys*5;}

	&info_message("get_files","Using method SHARE=EQUAL Tot=$max NUsers=".($#Users+1)." Each=$bys\n") if ($prtmsg);
	$uinfo .= "EQUAL share for users (";


	# EQUAL share will often lead to a higher number of
	# submitted jobs (int truncation) but it could also lead to
	# a lower number of many users have only one record or so. For
	# example, if a LIMIT 12 endsup with one record, there is no
	# bootstrap on count so, we end up with less than $max ...
	my(%Utmp,$l);

	$sth = $dbObj->prepare("$cmd AND User=? $xcmd LIMIT ?");
	foreach $user (@Users){
	    if ( ! defined($Utmp{$user}) ){
		#&info_message("get_files","$cmd AND User=? LIMIT $bys\n");
		$uinfo .= "$user,";
		$l      = &Share_4user($dbObj,$status,$user,$bys);
		if ( $l == 0){ $l = 1;}
		if ( $sth->execute($user,$l) ){
		    &info_message("get_files","SHARE=EQUAL user=$user ($l)\n") if ($prtmsg);
		} else {
		    &info_message("get_files","SHARE=EQUAL Failed [".$DBI::errstr."]\n");
		}
	    }
	    $Utmp{$user} = 1;
	}
	chop($uinfo); $uinfo .= ")";
	$sth->finish();

    } elsif ( $method eq "GROUP" ){
	# This rule is actually unfare. If a group with a higher
	# weight submits lots of requests + the first user of group 2
	# gets the rest and it never reverts to equal share amongst
	# remaining users.
	if( $#Groups  <= 0){
	    &info_message("get_files","Method GROUP but Groups=".($#Groups+1)." . Reverting to EQUAL\n") if ($prtmsg);
	    $method = "EQUAL";
	    goto SMETHODS;
	}

	&hpss_change_hpss_batch_policy($dbObj,0) if ($status==0);

	# Distributes entries. GROUP shares by .... Groups (well done)
	$bys = int($max/($#Groups+1)+0.5);
	if ($bys <= 0){ $bys = 1;}
	#if ($tsort){    $bys = $bys*5;}

	&info_message("get_files","Using method SHARE=GROUP $max $#Groups $bys\n") if ($prtmsg);
	$uinfo .= "GROUP sharing";

	$sth = $dbObj->prepare("$cmd AND GroupID=? $xcmd LIMIT $bys");
	foreach $group (@Groups){
	    if ( ! $sth->execute($group) ){
		&info_message("get_files","SHARE=GROUP Failed [".$DBI::errstr."]\n");
	    }
	}
	$sth->finish();


    } elsif ( $method eq "GRPW" ){
	#
	# This rule is taking into consideration group weight. A weight of 0
	# is the base line. If not null, the number is considered as a %tage.
	# For exach pass, remember that we have $max entries.
	#
	if( $#Groups  <= 0){
	    &info_message("get_files","Method GROUP but Groups=".($#Groups+1)." . Reverting to EQUAL\n") if ($prtmsg);
	    $method = "EQUAL";
	    goto SMETHODS;
	}

	# Otherwise, we need an array
	my($ii,$sum,$nullg,@Bys);

	# Distributes entries. GROUP shares by .... Groups (well done)
	#$bys = int($max/($#Groups+1));
	#if($bys <= 0){ $bys = 1;}


	# We need to pre-calculate the selection
	$nullg = $sum = 0;
	for ($ii=0 ; $ii <= $#GroupsW ; $ii++){
	    if ( $GroupsW[$ii] != 0){
		# The weights are direct i.e. 50 --> 50%
		$sum     += $GroupsW[$ii];
	    } else {
		$nullg++;
	    }
	}

	# After the first loop, the results of $sum is either
	# greater than 100 (over-subscribed) or below (more slots available)
	if ( $sum > 100){
	    # over subscribed, need to scale all down
	    &info_message("get_files","GRPW over subscribed for $max [$sum]\n");
	    my($off)= 100/$sum;
	    for ($ii=0 ; $ii <= $#GroupsW ; $ii++){
		if ($GroupsW[$ii] != 0){
		    $GroupsW[$ii] = $GroupsW[$ii]*$off;
		    $Bys[$ii]     = int($max*$GroupsW[$ii]/100)+1;
		    &info_message("get_files","\tadjusting grp index=$ii to $Bys[$ii]\n");
		} else {
		    # We should leave at least 1 in this mode otherwise,
		    # multiple direct %tage will prevent other users from
		    # ever getting a slot.
		    &info_message("get_files","\tSetting   grp index=$ii to 1\n");
		    $Bys[$ii]     = 1;
		}
	    }
	} else {
	    # We still have 100-$sum slots to share amongst $nullg
	    if ($nullg == 0 ){ $nullg = 1;}

	    &info_message("get_files","GRPW calculating weights\n") if ($prtmsg);
	    for ($ii=0 ; $ii <= $#GroupsW ; $ii++){
		my($off)=(100-$sum)/$nullg; #
		if ($GroupsW[$ii] == 0){
		    $Bys[$ii]     = int($max*$off/100)+1;
		} else {
		    $Bys[$ii]     = int($max*$GroupsW[$ii]/100)+1;
		}
	    }
	}

	# Note that in this policy, the end result will be to always
	# have at least one job per group in not over-subscribed since
	# we use int()+1
	# &info_message("get_files","$cmd AND GroupID=? $xcmd LIMIT ?");
	use DBI qw(:sql_types);
	$sth  = $dbObj->prepare("$cmd AND GroupID=? $xcmd LIMIT ?");
	$sthu = $dbObj->prepare("$cmd AND User=?    $xcmd LIMIT ?");

	$uinfo .= "GRPW sharing - this included ";
	&hpss_change_hpss_batch_policy($dbObj,0) if ($status==0);

	for ($ii=0 ; $ii <= $#Groups ; $ii++){
	    if ($Bys[$ii] != 0){
		# To be 100% fair, we need to see with the group that all users
		# get at equal slot ... This complicate the algo a bit
		my(@nu)=split(",",$GUList{$Groups[$ii]});

		if ( $#nu <= 0 ){
		    # this could happen if a user is in two groups, then it
		    # would appear only in one group and not two or more,
		    # therefore leading to -1. 0 is only one user in group.
		    $grp = $Groups[$ii]; $sth->bind_param(1,$grp,{TYPE => SQL_INTEGER});
		    $lmt = $Bys[$ii];    # if ($tsort){    $lmt = $lmt*5;}

		    $sth->bind_param(2,$lmt,{TYPE => SQL_INTEGER});

		    &info_message("get_files",
				  "Method GRPW - Selection grp index=$ii group=$grp is $lmt jobs \n");
		    $uinfo .= "group=$ii,";
		    if ( ! $sth->execute() ){
			&info_message("get_files","SHARE=GRPW Failed [".$DBI::errstr."]\n");
		    }
		} else {
		    # Otherwise, split by users (there are a few) and try to re-equilibrate
		    # Round off at 1
		    &info_message("get_files","\tgrp index=$ii has ".($#nu+1)." sub-users\n");

		    $bys = int($Bys[$ii]/($#nu+1));
		    if ($bys == 0){ $bys = 1;}
		    # if ($tsort){    $bys = $bys*5;}

		    foreach $user (@nu){
			&info_message("get_files",
				      "Method GRPW - Selection $Bys[$ii]/$bys jobs for $user\n");
			$sthu->bind_param(1,$user,{TYPE => SQL_VARCHAR});
			$sthu->bind_param(2,$bys, {TYPE => SQL_INTEGER});
			$uinfo .= "user=$user,";
			if ( ! $sthu->execute() ){
			    &info_message("get_files","SHARE=GRPW Failed [".$DBI::errstr."]\n");
			}
		    }
		}

	    } else {
		# this cannot be after correction from 20061031
		&info_message("get_files","Method GRPW - Bogus sel $Bys[$ii] jobs for $Groups[$ii]\n");
	    }
	}
	chop($uinfo);
	$sth->finish();
	$sthu->finish();


    } elsif ( $method eq "GRPU" ){
	# This is using other algorithm so no need to re-write
	# Oddly, this was broken until 2009/05
	if( $#Groups > 0){
	    &info_message("get_files","Method GRPU will select GROUP\n") if ($prtmsg);
	    $method = "GROUP";
	    goto SMETHODS;
	} else {
	    if( $#Users  > 0){
		&info_message("get_files","Method GRPU will select EQUAL\n") if ($prtmsg);
		$method = "EQUAL";
		goto SMETHODS;
	    } else {
		&info_message("get_files","Method GRPU but NUsers=".($#Users+1)." . Reverting to DEFAULT\n") if ($prtmsg);
		$method = "DEFAULT";
		goto SMETHODS;
	    }
	}
	&hpss_change_hpss_batch_policy($dbObj,0) if ($prtmsg);

    } else {
	# We can load a site-suplied module if exists.
	# The crontab moves us to the working directory.
	# Any implemented method is supposed to deal with
	# filling the 'Sorted' table.
	# Note that if a file named ShareDEFAULT.pl exists, it
	# will ALWAYS override the implemented default method.
	# When all records are requested, this is not disirable
	# but we don't stop you from screwing yourself up ...
	$file = "Share$method.pl";
	if( -e $file){
	    if( open(FI,$file) ){
		@all = <FI>;
		close(FI);
		$cmd = join("",@all);
		eval($cmd);
		if($@){
		    &info_message("get_files","Method SHARE=$method failed\n");
		}
	    } else {
		&info_message("get_files",
			      "File for method SHARE=$method found ".
			      "but cannot be opened (?)\n");
	    }
	} else {
	    # Unless a file ShareDEFAULT.pl exists, this WILL be the
	    # DEFAULT method.
	    #
	    $uinfo .= "DEFAULT used";

	    &hpss_change_hpss_batch_policy($dbObj,1) if ($status==0);

	    # default is to select exactely max
	    #$bys = $max;
	    if ( $imethod eq "DEFAULT"){
		# in this mode, we have no preference and no limits
		$bys = $max;
	    } else {
                # $Users[0] is the first and only user if we swapped
		$bys = &Share_4user($dbObj,$status,$Users[0],$max);
	    }
	    # if ($tsort){    $bys = $bys*5;}

	    #if( $bys == 0 && $status == 0){
	    if( $bys == 0 ){
		# Revert to a standard value
		$max = ($max>=0?$max:25);
		&info_message("get_files","SHARE=DEFAULT bys=0 and status=0, using max=$max\n");
		$cmd .= " $xcmd LIMIT $max";
	    } else {
		&info_message("get_files","SHARE=DEFAULT (provided method) $bys\n") if ($prtmsg);
		if ($max > 0) {  $cmd	.= " $xcmd LIMIT $bys";}
	    }
	    &info_message("get_files","Executing $cmd\n") if ($status == 0);
	    $nrows = $dbObj->do($cmd);
	    if ( ! defined($nrows) ){
		# an error has occured?
		&info_message("get_files","Possible error [".$DBI::errstr."]\n");
	    } else {
		&info_message("get_files","$nrows rows gathered\n") if ($status == 0);
	    }
	}

    }

    if ($status == 0){
	&info_message("get_files","Final algo information [$uinfo]\n");
	&hpss_set_message("Core","$uinfo",$dbObj);
    }

    # Post processing for TAPEID (could also use TSLIDERX)
    if ( $status == 0 && $HPSS::PARAM{"TSORT"} eq "TSLIDERX" ){
	# We should read back the LocID and add all records related to the available
	# tapes to minimize tape mounts - we only have the table "Sorted_$pstatus" so
	# far, not "Selected_$pstatus". If this pass is succesful, the number of
	# record needs to be changed.
	my $reccnt=0;
	my $sthcnt= $dbObj->prepare("SELECT COUNT(id) FROM Sorted_$pstatus ");
	my $sthff = $dbObj->prepare("SELECT COUNT(id),LocID FROM Sorted_$pstatus GROUP BY LocID");

	if ( $sthcnt->execute() ){
	    $reccnt = $sthcnt->fetchrow()||0;
	} else {
	    &info_message("get_files","\tError in SELECT [".$DBI::errstr."]\n");
	}
	$sthcnt->finish() if ($sthcnt);

	if ( $reccnt != 0){
	    if ( $sthff->execute() ){
		my(@resff,$xcmd);

		&info_message("get_files","TSLIDERX we begin with $reccnt records -->\n");

		while( @resff = $sthff->fetchrow_array() ){
		    #&info_message("get_files","** DEBUG Got Cnt=$resff[0] LocId=$resff[1]\n");
		    if ( $resff[1] != 0){
			# Now it is tricky because we should not repeat the inserts - but SourceID/DestinationID
			# are unique. So, we changed the scheme and use IGNORE and make the combo unique
			$xcmd = "INSERT IGNORE INTO Sorted_$pstatus SELECT * FROM $HPSS::DDBTBLNAM WHERE ".
			        "Status=0 AND LocID=$resff[1]";
			# brute force
			if ( $dbObj->do($xcmd) ){
			    &info_message("get_files","\tForce Fill of LocId=$resff[1] done ($max)\n");
			} else {
			    &info_message("get_files","\tForce Fill of LocId=$resff[1] failed [".$DBI::errstr."]\n");
			}
		    }
		}

		# So, we are done adding - we need to adjust max now - count again
		$sthcnt= $dbObj->prepare("SELECT COUNT(id) FROM Sorted_$pstatus ");
		if ( $sthcnt->execute() ){
		    $reccnt = $sthcnt->fetchrow();
		    &info_message("get_files","<-- TSLIDERX we end with $reccnt records\n");
		    if ( $max < $reccnt){
			# be bold
			$max = $reccnt;
		    }
		} else {
		    &info_message("get_files","\tError in SELECT [".$DBI::errstr."]\n");
		}
		$sthcnt->finish() if ($sthcnt);

	    } else {
		&info_message("get_files","TAPEID Forced fill statement failed to execute [".$DBI::errstr."]\n");
	    }
	    $sthff->finish() if ($sthff);
	}
    }


    # Verify selection (debugging)
    if ( $status >= 0){
	if ( $sth = $dbObj->prepare("SELECT COUNT(id) FROM Sorted_$pstatus") ){
	    if ( $sth->execute() ){
		my $res = $sth->fetchrow();
		if ( $res == 0){
		    if ( $status == 0){
			# this may be a bogus algorithm
			&info_message("get_files",
				      "Verification of algo found 0 entries - may indicate a problem or empty queue\n");

		    } else {
			&info_message("get_files",
				      "Verification of algo found 0 entries for status=$status\n");
		    }
		    $sth->finish();
		    goto SEL_EXIT;
		}

		# If not 0, we proceed i.e. no goto
		#
		# --->
                #
		$sth->finish();

	    } else {
		&info_message("get_files","Verification statement failed to execute [".$DBI::errstr."]\n");
		$sth->finish();
		goto SEL_EXIT;
	    }
	} else {
	    &info_message("get_files","Verification statement Did not prepare properly\n");
	    $sth->finish();
	    goto SEL_EXIT;
	}
     }



    # If you are tempted to replace DDBTBLNAM by Entries (which it currently is)
    # it would be a mistake. This logic allows us to set up test scripts on
    # the side manipulating different databases similar to Entries but without
    # interfering with the carousel. The name is hard-coded in generic server
    # but there, it does not matter ...
    &info_message("get_files","We will now build Selected_$pstatus records (Limit $max, TSort=$tsort)\n");
    $cmd = "INSERT INTO Selected_$pstatus SELECT ".
	   "$HPSS::DDBTBLNAM.id, Sources.Name, Destinations.Name, ".
	   "$HPSS::DDBTBLNAM.User, NodeInfo.Name, $HPSS::DDBTBLNAM.DCLifeTime, ".
	   "Sources.LocID ".
	   "FROM ".
	   "$HPSS::DDBTBLNAM, Sources, Destinations, NodeInfo, Sorted_$pstatus ".
	   "WHERE ".
	   "$HPSS::DDBTBLNAM.SourceID=Sources.id AND ".
	   "$HPSS::DDBTBLNAM.DestinationID=Destinations.id AND ".
	   "$HPSS::DDBTBLNAM.id=Sorted_$pstatus.id AND ".
	   "$HPSS::DDBTBLNAM.NodeID=NodeInfo.id ".($tsort?"ORDER BY Sources.LocID ":"").
	   ($max>0?"LIMIT $max":"");

    &debug_message("get_files","[$cmd]\n");
    $rv = $dbObj->do($cmd);

    if ( ! $rv){
	&info_message("get_files","Insert into Selected_$pstatus failed [".$DBI::errstr."]\n");
	&info_message("get_files",
		      "DEBUG INSERT INTO Selected_$pstatus SELECT ".
		      "$HPSS::DDBTBLNAM.id, Sources.Name, Destinations.Name, ".
		      "$HPSS::DDBTBLNAM.User, NodeInfo.Name, $HPSS::DDBTBLNAM.DCLifeTime, ".
		      "Sources.LocID ".
		      "FROM ".
		      "$HPSS::DDBTBLNAM, Sources, Destinations, NodeInfo, Sorted_$pstatus ".
		      "WHERE ".
		      "$HPSS::DDBTBLNAM.SourceID=Sources.id AND ".
		      "$HPSS::DDBTBLNAM.DestinationID=Destinations.id AND ".
		      "$HPSS::DDBTBLNAM.id=Sorted_$pstatus.id AND ".
		      "$HPSS::DDBTBLNAM.NodeID=NodeInfo.id ".($tsort?"ORDER BY Sources.LocID ":"").
		      ($max>0?"LIMIT $max":"")."\n");
	&hpss_clean_state($dbObj);	
	&die_message("get_files","Fatal error\n");
	# return undef;
    }


    &debug_message("get_files","Statement is $cmd\n");

    $cmd = "SELECT * FROM Selected_$pstatus";
    $sth = $dbObj->prepare($cmd);
    $sthu= $dbObj->prepare("UPDATE LOW_PRIORITY $HPSS::DDBTBLNAM SET Status=666 WHERE id=?");
    if ( ! $sth->execute() ){
	# More serious problem but will return empty list later on.
	&info_message("get_files","Rows Selection from Selected_$pstatus table failed [".$DBI::errstr."]\n");
    } else {
	$i = 0;
	while( @res = $sth->fetchrow_array() ){
	    #+
	    # We pack the info as user.FileId. In other scripts, the Id will allow
	    # us to do some accounting.
	    # This scheme implies a modification of the server script.
	    # June 2001. Prevention against bogus records.
	    #
	    # WARNING: 3rd item is expected by set_files() - do not change
	    #  order unless all code is changed.
	    #-
	    if($res[3] ne "" && $res[4] ne ""){
		$files[$i++]   = "$res[1] $HPSS::PROTO://$res[3].$res[0]\@$res[4]$res[2] $res[0] $res[5]";
	    } else {
		&info_message("get_files","Record considered BOGUS ".join(";",@res)."\n");
		$sthu->execute($res[0]);
	    }
	}
    }
    $sth->finish();
    $sthu->finish();

  SEL_EXIT:
    &hpss_clean_state();


    if($#files == -1){
	&debug_message("get_files","0 files selected\n");
    } else {
	&debug_message("get_files","$#files files selected\n");
    }
    return @files;
}


#
# Make sure the user does not have more than N jobs
# We call and ask for $shared because it is already pre-calculated
#
# A note that external logic will restore a returned value of 0
# to at least 1 and one place, will revert to the default value
# asked through the argument of get_file_list(). In short, this
# routine returns a hint that"may" be used, not a strict value.
#
sub Share_4user
{
    my($Obj,$status,$user,$share)=@_;

    my($rt,$sth,$lval,$mxval,$val);

    # don't bother for anything else than submit
    return $share if ( $status != 0 );

    # else check what to return ...
    $lval= 0;
    if ( ! defined( $HPSS::COUNTUSER{$user}) ){
	$lval= 0; 
	$rt  = &hpss_get_parameter("RETRY");
	$sth = $Obj->prepare("SELECT Count(User),User FROM $HPSS::DDBTBLNAM WHERE ".
			     "Status=1 AND Retries <= $rt GROUP BY User");

	#&info_message("CalcShare","Considering jobs in state 1,4 for $user\n");
	# IN (1,4) --> changed to 1 only for now (4 is to resubmit, they will
	# eventually be moved to status 1 and coiunt against the share then.

	if ( ! $sth){
	    &info_message("CalcShare","Error occured on prepare ".$sth->errstr()."\n");
	} else {
	    if ( $sth->execute() ){
		my(@items);

		while( @items = $sth->fetchrow_array() ){
		    $HPSS::COUNTUSER{$items[1]} = $items[0];
		    $lval = $items[0] if ( $items[1] =~ $user); # =~ will allow match to ""
		}
	    } else {
		&info_message("CalcShare","Error occured on execute ".$sth->errstr()."\n");
	    }
	}
	$HPSS::COUNTUSER{$user} = $lval if ($lval != 0);
    } else {
	$lval = $HPSS::COUNTUSER{$user};
    }

    # at this stage $lval is the number of jobs in status 1 (and 4 in previous coding)
    # Check the max total a given user can have.
    # This can be alterred by a carousel manager via DB or be %MAXRPERUSER% 
    if ( defined($mxval = &hpss_get_parameter("MAXPERU_$user")) ){	
	&info_message("CalcShare",
		      "Default value 1500 superseeded by MAXPERU_$user=$mxval\n");
	$val = $mxval;
    } else {
	# unlikely but need to check
	$mxval = $val = 1500;
    }

    # Now $val is the max number of restores that user may have in the system 
    #     $lval is the number of jobs in status 1 
    # We have all the information we need to return the share.
    #
    if ( $lval > $val ){
	# we way exceed the expected max for that user so return 0 share
	# To force a decrease and throttle, you may return 1 instead (0 
	# will trigger a logic reverting to default number of requests).
	$val = 1;
    } else {
	# how many more can we send? 
	# ( $val - $lval) is what's left but it should not exceed $share
	# Note that if a manager change the value MAXPERU_$user or MAXRPERUSER
	# between configurations and loops, the diff may become negative. Make
	# sure to protect against that too.
	if ( ( $val - $lval) < $share ){
	    if (  $val - $lval > 0 ){
		$val = $val - $lval;
	    } else {
		# we will still add 1 share and it will be enough
		# to do something while rebalancing and adjusting
		# to the new values.
		$val = 1;
	    }
	} else {
	    $val = $share;
	}

    }

    &info_message("CalcShare",
		  "From $share we found $lval at sts=1 (Max=$mxval) returning $val for user=[$user]\n");
    return $val;
}


#
# Handles restore policy change at HPSS Batch level
#
sub hpss_change_hpss_batch_policy
{
    #
    # Parameter are supposed to be
    #   0: default policy
    #   1: single user policy
    #
    # Be aware that those values may have nothing to do
    # with the values of PLCY1U and PLCYDFLT (for STAR, they
    # are equivalent but one may switch between any of two
    # available policies)
    #
    my($Obj,$pol)=@_;
    my($delay,$time,$stag);

    # protect against accidental loop (should not happen though)
    #return if ($HPSS::PMODE);

    $time = time();
    if ($pol == 0){
	$pol  = 0;
	$delay= 60*20;
	$stag = "PLCYDFLT=$pol (T=$delay)";
    } else {
	# one user policy could be done by checking first if
	# this is possible i.e. wwe are really the sole user
	my($sth,$rt,$ent,%Users,@items);
	my(@F);

	#$HPSS::PMODE = 1;
	#@F   = &hpss_get_files($Obj,undef,1,-1);
	#$HPSS::PMODE = 0;
	#
	##print "Got $#F entries\n";
	#
	#foreach $ent (@F){
	#    @items	= split(" ",$ent);
	#    $items[1] =~ s/\@.*//;   # strip node and file
	#    $items[1] =~ s/\..*//;   # strip request id
	#    $items[1] =~ s/.*\/\///; # strip proto
	#    $Users{$items[1]}=1;
	#}
	#@F = keys %Users;

	#print "We will prepare a select\n";
	$rt  = &hpss_get_parameter("RETRY");
	$pol = undef;

	$sth = $Obj->prepare("SELECT DISTINCT User FROM $HPSS::DDBTBLNAM WHERE ".
			     "Status=1 AND Retries <= $rt");

	#$sth = $Obj->prepare("SELECT DISTINCT User FROM $HPSS::DDBTBLNAM WHERE ".
	#		     "Status IN (1,4) AND Retries <= $rt");

	if ( ! $sth){
	    &info_message("Policy","Error occured on prepare ".$sth->errstr()."\n");
	} else {
	    if ( $sth->execute() ){
		#print "Execute was OK\n";
		while( @items = $sth->fetchrow_array() ){
		    #print "DEBUG pushing $items[0]\n";
		    push(@F,$items[0]);
		}

		# do not switch to one user if multiple are in status 1=submitted
		if ( $#F > 0){
		    &info_message("Policy","Found users=".join(";",@F).
				  " pending, not switching to PLCY1U\n");
		    return;
		} else {
		    if ( $#F == -1){
			#&info_message("Policy",
			#	      "Really?? No user, statement was a success and we reached here (??)\n");
			#&info_message("Policy","DDBTBLNAM=$HPSS::DDBTBLNAM\n");
			&info_message("Policy","No users requests with Status IN (1,4) and Retries <= $rt\n");
		    } else {
			&info_message("Policy","Found one user=".$F[0]." - policy can be switched to 1\n");
			$pol  = 1;
			$delay= 60*2;
			$stag = "PLCY1U=$pol (T=$delay)";
		    }
		}
	    } else {
		&info_message("Policy","Error occured on selecting record ".$sth->errstr()."\n");
	    }
	    $sth->finish();
	} # $sth
	return if ( ! defined($pol) );
    }

    # Be sure to change policy only if necessary
    if ( -e "/home/starrdat/Batch/bin/batch_Staging_Policy_upd.bash"){
        if ( &hpss_get_parameter("PolicyVal") != $pol ){
	    my($delta);

	    $delta =  $time - (&hpss_get_parameter("PolicyTm")||0);

	    if ( $delta > $delay ){
		&info_message("Policy","Switching HPSS Batch Policy to $pol\n");
		&hpss_set_message("Policy","Switching HPSS Batch Policy to $stag",$Obj);
		system("/home/starrdat/Batch/bin/batch_Staging_Policy_upd.bash $pol");
		if ( $? == -1){
		    &info_message("Policy","Failed to execute /home/starrdat/Batch/bin/batch_Staging_Policy_upd.bash\n");
		} else {
		    &hpss_set_parameter($Obj,"PolicyVal",$pol);
		    &hpss_set_parameter($Obj,"PolicyTm" ,$time);
		}
	    } else {
		&info_message("Policy",
			      "HPSS Batch Policy should be switched to $pol but delta $delta < $delay\n");
	    }
	} else {
	    # we use that same policy again, reset time last updated
	    my($expired)=time()-&hpss_get_parameter("PolicyTm");
	    if ( $expired > 600){
		# force reset in case externally changed
		if ( &hpss_get_parameter("PolicyFreeze") ){
		    &info_message("Policy","PolicyFreeze is set to TRUE - Not updating policy\n");
		} else {
		    &info_message("Policy","Force update for policy $pol and PolicyTm\n");
		    system("/home/starrdat/Batch/bin/batch_Staging_Policy_upd.bash $pol");
		    &hpss_set_parameter($Obj,"PolicyTm" ,$time);
		}
	    }
	}
    }

}


# Sets a bunch of files to a new status.
sub	hpss_set_files
{
    my($dbObj,$DataBase,$status,@files) = @_;

    # whether or not we want a low priority update is opened for debate - if we run into
    # concurent execution, best NOT to use low priority
    if ( $status == 1){
	# 2022/03 - everytime we move to sibmitted, we increase the retry count
	return &hpss_handle_task("UPDATE LOW_PRIORITY $HPSS::DDBTBLNAM SET Status=?, ".
				 " Retries=Retries+1 WHERE ".
				 " SourceID=? AND DestinationID=? AND NodeID=?",
				 $dbObj,$DataBase,$status,@files);
    } else {
	return &hpss_handle_task("UPDATE LOW_PRIORITY $HPSS::DDBTBLNAM SET Status=? WHERE ".
				 "SourceID=? AND DestinationID=? AND NodeID=?",
				 $dbObj,$DataBase,$status,@files);
    }
}

# Delete files
sub	hpss_flush_files
{
    my($dbObj,$DataBase,@files) = @_;
    return &hpss_handle_task("DELETE LOW_PRIORITY FROM $HPSS::DDBTBLNAM WHERE ".
			     "SourceID=? AND DestinationID=? AND NodeID=?",
			     $dbObj,$DataBase,-1,@files);
}

sub     hpss_clean_state
{
    my($dbObj,$DataBase) = @_;
    my($cmd,$close,$rt);

    if (! defined($dbObj) ){
	$HPSS::OMODE = 1;
	$dbObj  = &hpss_open_database();
	$close  = 1;
    } else {
	$close  = 0;
    }

    if ( $dbObj == 0){
	&info_message("clean_state","No db Object handler");
	return 0;
    } else {
	my(@CMDS)=("DROP TABLE IF EXISTS CGroups_old",
		   "RENAME TABLE CGroups TO CGroups_old",
		   "DROP TABLE IF EXISTS CUsers_old",
		   "RENAME TABLE CUsers  TO CUsers_old");

	$rt  = $HPSS::PARAM{"RETRY"};
	if ( $rt != 0){
	    # One could think that it is best to add the selection Retries<$rt to the
	    # groups and users in get_files() but it is not the case as those records
	    # are bogus and need to be marked.
	    #   TODO 2011 --> below seems drastic
	    #push(@CMDS,"UPDATE $HPSS::DDBTBLNAM SET Status=666 WHERE Retries=$rt AND Status=0");
	}
	foreach $cmd (@CMDS){
	    $dbObj->do($cmd);
	}

	&hpss_close_database($dbObj) if ($close);
	return 1;
    }
}

#
# Real routine which does things. Note that this routine
# will also take care of cleaning the DataBase.
#
# The list of values expected in a single pop @lines is
# determined by hpss_get_files()
#
sub	hpss_handle_task
{
    my($task,$dbObj,$DataBase,$status,@files) = @_;
    my(@items,$sth,$i,$error,$ok);
    my(@res);
    my($sthd,$sths,$sthu);
    my($taskr,$source,$file,$path);
    my($nodei,$node,$rc);


    # Don't waste time on that. Must be a mistake
    if($#files == -1){
	&debug_message("handle_task",
		       "Received File list is empty\n");
	return (0,0,0);
    }


    # In case NodeID is bogus, attempt to repair on the fly
    $sth   = "AND NodeID.*";
    $taskr = $task;
    $taskr =~ s/$sth//;

    # --- In its actual form, this routine NO LONGER supports
    # Flexible format. Only format returned by Get_files()
    # supported.
    # ---


    $error	= 0;
    $ok	        = 0;
    $sth	= $dbObj->prepare($task);


    &debug_message("handle_task","Scanning file list $#files\n");

    # it is better for speed issues to pre-prepare some sth
    # even if we do not use them. Please see comments on those
    # statements since this is a later speed improvement.
    $sthd = $dbObj->prepare("DELETE LOW_PRIORITY FROM $HPSS::DDBTBLNAM WHERE ".
	                    "SourceID=? AND ".
			    "DestinationID=? AND ".
			    "NodeID=? AND ".
			    "id != ?");
    $sths = $dbObj->prepare("SELECT * FROM AccntGlobal WHERE id=?");
    $sthu = $dbObj->prepare("UPDATE LOW_PRIORITY AccntGlobal SET Status=? WHERE id=?");
    $sthr = $dbObj->prepare($taskr);

    for ($i = 0 ; $i <= $#files ; $i++){
	@items = split(" ",$files[$i]);
	if( $#items < 1){
	    &debug_message("handle_task","Not enough elements in file list\n");
	    return (0,0);
	}
	($file,$path,$node) = &hpss_split_uri($items[1]);

	# Get it numerical now
	$source=&from_record_and_fetch_in( "handle_task",
					   "Sources",
					   $items[0],$dbObj,0);
	$file  = &from_record_and_fetch_in("handle_task",
					   "Destinations",
					   $path.$file,$dbObj,0);
	$nodei = &from_record_and_fetch_in("handle_task",
					   "NodeInfo",
					   $node,$dbObj,0);

	$id   = $items[2];

	if( $status == -1){
	    # run mode delete. This is the place where we
	    # on hpss_flush_files() call.
	    if ($i % 100 == 0 && $i != 0){
		&info_message("handle_task",
			      "$i records (".sprintf("%4.2f",
						     100*($i/($#files+1))).
			      "%) deleted on ".localtime()."\n");
	    }
	    $rc = $sth->execute($source,$file,$nodei);
	    if ( $sth->rows == 0){
		$sthr->execute($source,$file);
		if ( $sthr->rows != 0  && $nodei != 0){
		    &info_message("handle_task",
				  "Repaired BOGUS record src=$source file=$file NodeID=$nodei\n");
		} else {
		    &info_message("handle_task",
				  "ATTENTION BOGUS record detected src=$source file=$file ".
				  "node=$nodei\n");
		}
	    }
	} else {
	    # Update mode with a set_files() call.
	    $rc = $sth->execute($status,$source,$file,$nodei);

	    # if ( $rc && $status == 1){
	    #	&info_message("handle_task","Should be fine with $source $file $nodei\n");
	    # }
	    my($rcnt)=$sth->rows();

	    if ( $rcnt == 0){
		# we need up with 0 rows
		&debug_message("handle_task","Num rows = $rcnt\n");
	    	$sthr->execute($status,$source,$file);

		if ( $sthr->rows != 0 && $nodei != 0){
		    $dbObj->do("DELETE FROM NodeInfo WHERE id=$nodei");
		    my($nodeii) = &from_record_and_fetch_in("handle_task",
		                                       	    "NodeInfo",
					                    $node,$dbObj,0);
		    &info_message("handle_task",
				  "Reparing BOGUS detected status=$status src=$source file=$file ".
				  "node=$nodei -> $nodeii\n");
		    $dbObj->do("UPDATE Entries SET NodeID=$nodeii WHERE NodeID=$nodei");
		} else {
		    &info_message("handle_task",
				  "ATTENTION BOGUS record status=$status src=$source file=$file ".
				  "node=$nodei\n");
		}

	    # } else {
	    #	&info_message("handle_task","handle_task","$rcnt with $source $file $nodei\n");
	    }

	    # This will do the clean-up. Note the effect :
	    # it deletes from the database extraneous records
	    # wich reference the SAME HPSS File, to be restored
	    # on the SAME node and at the SAME location. This
	    # cannot be a user choice but a mistake ....
	    $sthd->execute($source,$file,$nodei,$id);

	    if($status == 0){
		# If what we are doing is to set file to Status 0
		# we may want to actually reset the AccntGlobal table
		# as well and strip out the REQUEUE word because this
		# case currently happens when we change 4 -> 0. Note
		# that if this is done, the get_files() command will
		# NOT select those files if Retries > RETRY Parameter.
		$sths->execute($id);
		@res = $sths->fetchrow_array();
		if($#res != -1){
		    $msg = $res[4];
		    $msg =~ m/(.*)(\**\s+REQUEUED.*)/;
		    $sthu->execute($1,$id);
		}
	    }
	}
	if( $rc ){
	    $ok++;
	} else {
	    &debug_message("handle_task",
			   "Task $task failed\n",
			   "[".$sth->errstr."]");
	    $error++;
	}


	&debug_message("handle_task",
		       "$task $source $file $nodei (id=$id)\n");
    }
    $sth->finish();
    $sthu->finish();
    $sthd->finish();
    $sths->finish();
    ($ok,$error);
}



# -----------------------
# Alias Table access
# -----------------------
# Return string from num
sub hpss_decode_2string
{
 my($i) = @_;
 my($res);


 $res = "Something";
 &info_message("decode_2string","OBSOLETE ROUTINE\n");

 return $res;

}


# Get Num from string
sub hpss_encode_string
{
 my($res,$table) = @_;
 my($cmd,$sth);

 if($res eq "" || $table eq ""){
     &die_message("encode_string","Suspicious Empty Path or Table received\n");
     return 0;
 }


 $i   = 0;
 &info_message("encode_string","OBSOLETE ROUTINE\n");


 if( !defined($i) ){
     # Since all indexes are sorted in order and non-repetitive due to
     # auto_increment, we can then ...
 }
 return $i;
}





# Finally, decode path from full file specification, return ($file,$hpath)
sub hpss_split_hpath
{
 my($file,$flag) = @_;
 my($path,$tmp);

 $tmp  =  $file;
 $file =~ s|.*/||;
 $path =  substr($tmp,0,length($tmp) - length($file));

 # Fix path if necessary. Check first character
 if(substr($path,0,1) ne "/"){
   if(! defined($flag)){
	$path = "$HPSS::BASEPATH/$path";
   } else {
	$path = "/$path";
   }
 }

 # Send info now.
 ($file,$path);
}



sub hpss_split_uri
{
    my($file,$missing) = @_;
    my(@items,$uri,$path,$tmp,$user);
    my(@all);

    # check argument validity
    if( ! defined($file) ){
	&debug_message("split_uri","UNDEF value sent to routine (??)\n");
	return ("","","");
    }
    &debug_message("split_uri","Received $file\n");


    # Pre-parse and fix it if users made a mistake.
    if( substr($file,length($file)-1,1) eq "/" ){
	# Only path was specified
	$file .= $missing;
    }


    # Treat this now
    @items = split("/",$file);
    #print "DEBUG :: [$items[0]] [$items[1]] [$items[2]]\n";

    # syntax starting with // . EXPECT NODE NAME after //
    # and have no mercy
    if( $items[0] eq "" && $items[1] eq ""){
	# missing proto name for sure
	shift(@items);
	unshift(@items,"$HPSS::PROTO".":");
    } elsif ($items[0] eq ""){
	# syntax starts with one / ;  assumes
	# the user has specified only a path and
	# no proto, user and node
	#&debug_message("split_uri","$#items [".getlogin()."]\n");
	# We can the implement the auto-path recognition
	$tmp = "";
	for($i=1 ; $i <= $HPSS::PARAM{"DEPTH"} ; $i++){
	    $tmp .= "/$items[$i]";
	}
	# we now have the path. Get NFS node name if any.
	if ( ($tmp = &GetNFSNode($tmp)) ne ""){
	    unshift(@items,&GetLogin()."\@$tmp");
	} else {
	    unshift(@items,&GetLogin()."\@treat-as-rr.rcf.bnl.gov");
	}
	unshift(@items,"");
	unshift(@items,$HPSS::PROTO.":");
    }


    # Now we are in business
    $rnode = $items[2];
    #print "$rnode\n";
    if( ($tmp = index($rnode,"\@") ) != -1 ){
	# The user name appears in the path. Strip it out
	#&debug_message("split_uri","Found \@ in $rnode\n");
	$user	= substr($rnode,0,$tmp);
	$rnode	= substr($rnode,$tmp+1,length($rnode));
    }


    shift(@items);  shift(@items);  shift(@items);
    $uri   = join("/",@items);
    ($tmp,$path) = &hpss_split_hpath($uri,1);

    #&debug_message("split_uri","Rnode $rnode Path $path File $tmp\n");
    ($tmp,$path,$rnode);
}


# This routine will allow us to be DataBase field ordering independant.
sub hpss_infoidx
{
    my($idx) = @_;
    my($tmp);

    $tmp = $HPSS::DDBINFO_REF{uc($idx)};
    if( ! defined($tmp) ){
	&die_message("infoidx","Script typo Error or DataBase changed. ".
		     "idx [$idx] unknown\n");
	0;
    } else {
	$tmp;
    }
}


#
# Called from $routine to record in $table the element $el
# and fetch it's value (returned value) using $dbObj handler.
# Returned value = 0 indicates a failure.
# Usage of $flag is :
#    1    Record and Fetch
#    0    Fetch only.
#   -1    Fetch only + what is fetched is the "Name" field not the id.
#
# This routine has never done any caching and therefore was VERY VERY
# slow. Modified J.L. October 6th 2001.
#
#
sub from_record_and_fetch_in
{
    my($routine,$table,$el,$dbObj,$flag) = @_;
    my($md5hex);
    my($sth,$cmd);
    my($value,@all);

    chomp($el);
    $el =~ s/^(.*?)\s*$/$1/g;

    # Use caching. %RNFI is automatically global.
    if( defined($RNFI{"$table-$el"}) && $flag != 1){  return $RNFI{"$table-$el"}; }


    # else record and/or fetch this element
    #$md5 = new MD5;
    #$md5->reset();

    if ( ! defined($HPSS::MD5) ){
	$HPSS::MD5 = Digest::MD5->new();
    } else {
	$HPSS::MD5->reset();
    }
    $HPSS::MD5->add($el);
    $md5hex = $HPSS::MD5->hexdigest();

    if($flag == 1){
	# Record this element. Use IGNORE to record this element without duplication.
	$cmd = 'INSERT IGNORE INTO '.$table.' VALUES(NULL,"'.
	    $md5hex.'","'.$el.'",0)';

	$sth = $dbObj->prepare($cmd);

	if( ! $sth){
	    &debug_message($routine,"Insert IGNORE statement could not be prepared\n");
	    return 0;
	}
	if (! $sth->execute() ){
	    &debug_message($routine,"Error occured on execute [".$sth->errstr."]\n",
		      "Command was $cmd\n");
	    return 0;
	}
	$sth->finish();
    }


    # Fetch value now.
    if( $flag == -1){
	$cmd = 'SELECT * FROM '.$table.' WHERE id = "'.$el.'"';
    } else {
	$cmd = 'SELECT * FROM '.$table.' WHERE MD5 = "'.$md5hex.'"';
    }
    $sth = $dbObj->prepare($cmd);
    if( ! $sth ){
	&debug_message($routine,
		      "Update Statement could not be prepared\n",
		      " [".$sth->errstr."]\n");
	return 0;
    }
    $sth->execute();
    @all = $sth->fetchrow_array();
    if($#all != -1){
	if( $flag == -1){
	    # Return the "name" field
	    $value = $all[2];
	} else {
	    # Return the id field
	    $value = $all[0];
	}
    } else {
	&debug_message($routine,"Failed to Fetch information for $el\n");
	$value = 0;
    }
    $sth->finish();
    $RNFI{"$table-$el"} = $value;
    $value;
}


#
# Select records from one of Sources, Destinations, NodeInfo
# i.e. from tables of the same shape. Only returns id in an
# array context.
#
# This will remain a low level routine ... but may be used
# in utility scripts
#
sub hpss_get_record_locids
{
    my($table,$limit,$locval,$dbObj)=@_;
    my($cmd,$sth,@id,@all);

    if ( ! $dbObj ){
	&debug_message("get_record_locids","No DB Object\n");
	return undef;
    } else {
	undef(@all);
	$cmd = 'SELECT id,Name FROM '.$table;
	if ( defined($locval) ){   $cmd .= " WHERE LocID=$locval"; }
	else                   {   $cmd .= " WHERE LocID=0";       }

	# Add this so most recent entries gets updated first (more likely
	# to be un-assigned a LocID) - This is an initial assumption which
	# should be changed when the whole table is updated once.
	#$cmd .= " ORDER BY id DESC";
	$cmd .= " ORDER BY id ASC";

	# Limit by bunch
	if ( defined($limit) ){    $cmd .= " LIMIT $limit";        }

	# Now prepare, ane execute
	$sth = $dbObj->prepare($cmd);
	if( ! $sth){
	    &debug_message("get_record_locids","Prepare statement failed [".$sth->errstr."]\n");
	    return undef;
	}
	if ( ! $sth->execute() ){
	    &debug_message("get_record_locids","Error occured on execute [".$sth->errstr."]\n");
	    return undef;
	}
	while ( @id = $sth->fetchrow_array() ){
	    #print "Returning [$id[0] $id[1]]\n";
	    push(@all,"$id[0] $id[1]");
	}
	$sth->finish();
	return @all;
    }
}


#
# Update accordinly multiple tables, one id at a time
#
sub hpss_set_record_locids
{
    my($table,$id,$locval,$dbObj)=@_;
    my($cmd,$sth);

    if ( ! $dbObj ){
	return 0;
    } else {
	$cmd = "UPDATE $table SET LocID=$locval WHERE id=?";

	#$idstr=  substr($table,0,length($table)-1);
	#$cmd2 = "UPDATE TABLE $HPSS::DDBTBLNAM SET ";

	$sth = $dbObj->prepare($cmd);
	if ( ! $sth->execute($id) ){
	    print "Error occured on primary execute [".$sth->errstr."]\n";
	    &debug_message("get_record_locids","Error occured on primary execute [".$sth->errstr."]\n");
	    return 0;
	#} else {
	    #print "Updated [$cmd] ?=$id\n";
	}
	$sth->finish();

	# if Sources, need to update Entries as well
	if ($table eq "Sources" && $locval != -1){
	    $cmd = "UPDATE IGNORE $HPSS::DDBTBLNAM SET LocID=$locval WHERE SourceID=?";
	    $sth = $dbObj->prepare($cmd);
	    if ( ! $sth->execute($id) ){
		&debug_message("get_record_locids","Error occured on secondary execute [".$sth->errstr."]\n");
	    }
	    $sth->finish();
 	}
	return 1;
    }
}


# update Entries LocID where LocID is NULL
sub hpss_update_record_locids
{
    my($dbObj)=@_;
    my($cmd);

    if ( $dbObj){
	$cmd  = "UPDATE $HPSS::DDBTBLNAM,Sources SET $HPSS::DDBTBLNAM.LocID=Sources.LocID";
	$cmd .= " WHERE $HPSS::DDBTBLNAM.SourceID=Sources.id AND $HPSS::DDBTBLNAM.LocID=0 AND Sources.LocID!=-1";

	$sth = $dbObj->prepare($cmd);
	if ( ! $sth ){
	    &info_message("update_record_locids","Prepare statement failed\n");
	} else {
	    if ( ! $sth->execute() ){
		&info_message("update_record_locids","Execute failed\n");
	    }
	    $sth->finish();
	}
    }
}


#
# Reporting of queue status
#
sub hpss_show_queue_activity
{
    my($dbObj,$Mval,$Xval,$extra)=@_;
    my($rt,$lasts,$cutd,$rcutd,$date);
    my($cmd1,$sth1,$cmd2,$sth2);
    my(@LIGNES,%StatS,%StatU);

    return () if ( !$dbObj);

    # this may change but for the moment, we keep it the same
    $rt    = &hpss_get_parameter("RETRY");
    $lasts = &hpss_get_parameter("LastSubmit");
    $cutd  = $rcutd = &Today();
    $cutd  =~ s/://g;
    $rcutd = &UnixDate($rcutd,"%b %e %Y");

    if ( !defined($Mval) ){
	$Mval = $date = &DateCalc(&Today(),"-20 days");
    } else {
	$Mval = $date = &ParseDate($Mval);
    }
    $date = &UnixDate($date,"%b %e %Y");
    $Mval =~ s/://g;

    if ( !defined($extra)){  $extra="";}


    &debug_message("show_queue_activity","Values rt=$rt min=$Mval expires=$cutd\n");

    $cmd1 = "SELECT COUNT(User),Retries,User,Status FROM Entries WHERE Retries <= $rt ".
            " AND EntryDate > $Mval  AND Expires > $cutd ".
	    #AND EntryDate < $Xval <-- not the saem format GMT < EDT comparison will chop records
	    " AND Status IN (5,6,36,666) $extra GROUP BY Status,User";   # <-- this one will not be grouped by Retries

    $cmd2 = "SELECT COUNT(User),Retries,User,Status FROM Entries WHERE Retries <= $rt ".
            " AND EntryDate > $Mval  AND Expires > $cutd ".
	    #AND EntryDate < $Xval <-- not the saem format GMT < EDT comparison will chop records
	    " AND Status IN (0,1,11,2,3,4) $extra GROUP BY Status,User,Retries";


    $sth1 = $dbObj->prepare($cmd1);
    $sth2 = $dbObj->prepare($cmd2);

    if ($sth1 && $sth2){
	if ( $sth1->execute() && $sth2->execute() ){
	    my($tmp,$sts,$psts)=("","","");
	    my($e,$rrt,$xif);

	    while( @res = $sth2->fetchrow_array() ){
                # since we increment retries by +1 at each submit, adjust
		$rrt = ($res[1]!=0?$res[1]-1:0); 
		#$xif = $res[1]==0?"":"(new mode)"; <<--- this was a transiiton logic
		$xif = "";
		$stinfo = "$res[1] $rrt $res[3]";     	$e = ($rrt > 1?"s":""); 
		$stinfo = "Previously failed $rrt time$e"   if ($res[1] > 1);

		if ( $res[3] == 0){
		$stinfo = "Requeued after $rrt failure$e";
		$stinfo = "Requeued"                        if ($res[1] == 1);
		$stinfo = "New and never submitted"         if ($res[1] == 0); 
		}
		$stinfo = "Waiting for HPSS response $xif" if ($rrt == 0 && $res[3] == 1);
		$stinfo = "Success on first try $xif"      if ($rrt == 0 && $res[3] == 2);
		$stinfo = "Non-recoverable error occured $xif" if ($rrt == 0 && $res[3] == 3);
		$stinfo = "Requeued known recoverable $xif"    if ($rrt == 0 && $res[3] == 4);
		$stinfo = "Behind after $rrt failure$e"     if ($res[3] ==11);


		if (  ($tmp = &hpss_status_string($res[3])) ne $psts ){
		    if ($#LIGNES == -1){  push(@LIGNES,"-1;Date > $date and Expiration > $rcutd");
					  push(@LIGNES,"-1;Status;User;Count;Sanity");}
		    push(@LIGNES,"--");
		    $sts = $psts = $tmp;
		} else {
		    $sts = "";
		}

		#$stinfo = "DEBUG 0=$res[0] 1=$res[1] $rtt 2=$res[2] 3=$res[3] $sts";

		push(@LIGNES,"$res[3];$sts;$res[2];$res[0];$stinfo");

		if ( defined($StatS{$res[3]}) ){ $StatS{$res[3]}             += $res[0];}
		else {                           $StatS{$res[3]}              = $res[0];}
		if ( defined($StatU{$res[3]}) ){ $StatU{$res[2]."_".$res[3]} += $res[0];}
		else {                           $StatU{$res[2]."_".$res[3]}  = $res[0];}
	    }

	    $stinfo = " ";
	    while( @res = $sth1->fetchrow_array() ){
		if (  ($tmp = &hpss_status_string($res[3])) ne $psts ){
		    if ($#LIGNES == -1){  push(@LIGNES,"-1;Date > $date and Expiration > $rcutd");
					  push(@LIGNES,"-1;Status;User;Count;Sanity");}
		    push(@LIGNES,"--");
		    $sts = $psts = $tmp;
		} else {
		    $sts = "";
		}
		$e = ($res[1] > 1?"s":"");
		$stinfo = "Previously submitted $res[1] time$e";
		push(@LIGNES,"$res[3];$sts;$res[2];$res[0];$stinfo");

		if ( defined($StatS{$res[3]}) ){ $StatS{$res[3]}             += $res[0];}
		else {                           $StatS{$res[3]}              = $res[0];}
		if ( defined($StatU{$res[3]}) ){ $StatU{$res[2]."_".$res[3]} += $res[0];}
		else {                           $StatU{$res[2]."_".$res[3]}  = $res[0];}
	    }


	    if ( $#LIGNES != -1){    # TODO: experimental
		my($TOT)=0;
		my($stsstr,$valu,$vali);
		push(@LIGNES,"-1;-");
		foreach $sts ( keys %StatS ){  $TOT += $StatS{$sts};}
		foreach $sts (sort {$a <=> $b} keys %StatS ){
		    $stsstr = &hpss_status_string($sts);
		    $valu   = int($StatS{$sts}/$TOT*100);
		    $vali   = ($StatS{$sts}/$TOT*100 - $valu)*100;
		    push(@LIGNES,sprintf("-1;%25.25s %%tage=%2.2d.%2.2d%%",$stsstr,$valu,$vali));
		}
	    }

	    #foreach $user (keys %StatU ){
	    #	print "DEBUG $user $StatU{$_}\n";
	    #}

	    $sth1->finish();
	    $sth2->finish();
	} else {
	    &debug_message("get_record_locids","Error occured on execute [".$sth2->errstr()."]\n");
	}
    } else {
	&debug_message("get_record_locids","Error occured on prepare [".$DBI::errstr."]\n");
    }
    return @LIGNES;
}

#
# More straight forward for only what is in progress
#
sub hpss_n_in_progress
{  
    my($dbObj)=@_;
    my($cmd,$sth,$res,$close);

    if (! defined($dbObj) ){
	$HPSS::OMODE = 1;
	$dbObj  = &hpss_open_database();
	$close = 1;
    } else {
	$close = 0;
    }

    $cmd = "SELECT COUNT(User) FROM Entries WHERE Status=1";
    $sth = $dbObj->prepare($cmd);
    $res = undef;
    if ($sth ){
	if ( $sth->execute() ){
	    $res =  $sth->fetchrow()||0;
	}
    }
    $sth->finish();
    &hpss_close_database($dbObj) if ($close);
    return $res;
}


# ----------------------------------------------------------------------
#                Routine to handle run Status
# ----------------------------------------------------------------------
# This routine uses the latest format using dbObj only
# They can open/close the database as needed.
sub hpss_get_message
{
    my($dbObj,$limit)=@_;
    my($close);
    my($sth,$res);
    $res = "";
    if ( ! defined($limit) ){
	$limit = 1;
    }

    if (! defined($dbObj) ){
	$HPSS::OMODE = 1;
	$dbObj  = &hpss_open_database();
	$close  = 1;
    } else {
	# Not a question of commit
	# $dbObj->commit();
	$close  = 0;
    }

    if ( $dbObj ){
	$sth    = $dbObj->prepare("SELECT EntryDate,Status FROM RunStatus ORDER BY id DESC LIMIT $limit");
	if ( $sth->execute() ){
	    while ( @res = $sth->fetchrow_array()){
		$res .= join("::",@res).";";
	    }
	    chop($res);
	}
	$sth->finish();
	&hpss_close_database($dbObj) if ( $close);
    }

    return $res;
}

sub hpss_set_message
{
    my($routine,$st,$dbObj,$force)=@_;
    my($close,$sth,$status);
    my($last,$new,@items,$curr);

    #&print_message("",$routine,"$st on ".localtime()."\n");

    $status = 0;
    $curr   = $st;

    if (! defined($dbObj) ){
	$HPSS::OMODE = 1;
	$dbObj  = &hpss_open_database();
	$close  = 1;
    } else {
	$close  = 0;
    }
    $force = 0 if ( ! defined($force) );

    # TODO --- instead, delete old and replace by new message

    if ( $dbObj ){
	# be aware that get_message() gets the ID too.
	if ( $HPSS::LASTMSG[0] eq "" ){
	    $last   = &hpss_get_message($dbObj,10);

	    &debug_message("set_message","last is [$last]\n");
	    @items  = split(";",$last);

	    for ($last=0 ; $last < 10 ; $last++){
		$items[$last] =~ s/[\d:]+//g;
		$HPSS::LASTMSG[$last] = $items[$last];
	    }
	}
	$curr   =~ s/[\s\d\.:-]+//g;

	# no repeat up to 10 levels
	$new =  (1==1);
	for ($last=0 ; $last < 10 ; $last++){
	    $HPSS::LASTMSG[$last] =~ s/[\s\d\.:-]+//g;
	    $new = $new && ($curr ne $HPSS::LASTMSG[$last]);
	}

	&debug_message("set_message","[".
		       join(" + ",@HPSS::LASTMSG)."] [$curr] new=$new force=$force\n");

	if ( $new || $force ){
	    &debug_message("set_message","Will insert\n");
	    $sth    = $dbObj->prepare("INSERT INTO RunStatus VALUES(0,NOW(),?)");
	    if ( ! $sth ){
		&debug_message("set_message","Failed to prepare statement [".$sth->errstr."]\n");
	    } else {
		if ( ! $sth->execute($st) ){
		    &debug_message("set_message","Failed to execute statement [".$sth->errstr."]\n");
		} else {
		    $status = 1;
		}
	    }
	    $sth->finish();

	    # shift all one down for all 10 entries
	    for ($last = 10-1 ; $last >= 0 ; $last--){
		if ($last == 0){  $HPSS::LASTMSG[0] = $curr;}
		else {            $HPSS::LASTMSG[$last] = $HPSS::LASTMSG[$last-1];}
	    }
	} else {
	    &debug_message("set_message","Will skip message\n");
	}
	&hpss_close_database($dbObj) if ($close);
    }

    return $status;

}


sub hpss_flush_message
{
    my($dbObj)=@_;
    my($sth,$close);
    if (! $dbObj){
	$HPSS::OMODE = 1;
	$dbObj  = &hpss_open_database();
	$close  = 1;
    } else {
	$close  = 0;
    }

    if  ( $dbObj ){
	if ( $sth=$dbObj->prepare("SELECT count(*) FROM RunStatus") ){
	    my($count);
	    $sth->execute();
	    $sth->bind_columns( \$count );
	    if ( $sth->fetch() ){
		$sth->finish();
		if ( $count < 500 ){
		    return;
		}
	    }
	}
	$dbObj->do("DELETE LOW_PRIORITY FROM RunStatus");
    }
    &hpss_close_database($dbObj) if ($close);

}


# ----------------------------------------------------------------------
#                Messages Print in Debug/Info/Die mode.
# ----------------------------------------------------------------------
sub     die_message  {  &print_message("Fatal",@_); die "\n";}
sub     info_message {  &print_message("Info",@_);}

sub     debug_message{
    my(@args)=@_;
    if($HPSS::DEBUG){
	&print_message("Debug",@args);
    }
}

# sets the log file for all IO to arg1 and returns
# previous setting. "" means STDOUT.
sub     hpss_set_logfile
{
    my($flnm)=@_;
    my($prev)=$HPSS::LOGFIL;

    $HPSS::LOGFIL = $flnm;
    return $prev;
}

sub	print_message
{
    my($sev,$routine,@messages) = @_;
    my($mess,$head);
    my($FO);

    if ($HPSS::LOGFIL eq ""){
	$FO = STDOUT;
    } else {
	$FO = FO;
	$|  = 1;
	if ( -e $HPSS::LOGFIL ){
	    open($FO,">>$HPSS::LOGFIL");
	} else {
	    open($FO, ">$HPSS::LOGFIL");
	}
    }

    if ($sev ne ""){ $head = sprintf("HPSS %5s :: ",$sev);}
    else           { $head = "";}

    foreach $mess (@messages){
	printf $FO "$head%12.12s : %s",$routine,$mess;
    }
    if ($HPSS::LOGFIL ne ""){
	close($FO);
    }
}




# ----------------------------------------------------------------------
#                 Misc Routines.
# ----------------------------------------------------------------------

# return version
sub hpss_get_version { return $HPSS::VERSION;}

# Manages Status vs what it means. Some options are not used yet.
sub	hpss_status_string
{
    my($val) = @_;

    return "New"	           if ($val ==  0); # File has been entered in DDB
    return "Submitted/In Progress" if ($val ==  1); # File was queued for Submit
    return "Delayed"               if ($val == 11); # File was queued but nothing happened
    return "Restored"	           if ($val ==  2); # File is restored/already on disk
    return "Failure"	           if ($val ==  3); # Failed to restore
    return "Marked for requeue"    if ($val ==  4); # Requeued for later processing

    return "Stalled or vanished"   if ($val ==  5); # Job was submitted but vanished
    return "Rejected"              if ($val ==  6); # request was rejected

    return "Deleted"               if ($val == 36); # Entry marked for delete

    return "Bogus"                 if ($val ==666); # Bogus record

    # in case one component does not have a new status, 
    # need a default
    return "Unknown"; 
}


# Just in case
sub hpss_date
{
    my($date) = @_;

    &UnixDate($date,"%b %e %Y at %T");
}


#
# Note - routine will be added in standalone code + general pm
#
# Parse by myself and return in a format compatible with &ParseDate("today");
# This was added in 2013 as Date::Manip function returned 00:00:00 for the
# time, an indication that the TZ is not set properly.
sub Today
{
    my(@dt) = localtime();
    return sprintf("%4s%2.2d%2.2d%2.2d:%2.2d:%2.2d",
		   (1900+$dt[5]),$dt[4]+1,$dt[3],$dt[2],$dt[1],$dt[0]);
}



# getlogin() appeared to be unreliable
sub GetLogin
{
    if( ! defined($HPSS::USER) ){
	#my($user)=getlogin(); bad !! bad !! bad !! Gets the account prior
	# to su.

	my($user) = getpwuid($<);

	#if( ! defined($user) ){
	#    $user = getpwuid($<);
	#}
	#if( ! defined($user) ){
	#    chomp($user = `whoami`);
	#}
	# whoami command as well (does not exists
	# on some systems). id always works unless
	# there is a problem and interraction in
	# the .cshrc/.login. The pattern should save
	# us.
	if ( ! defined($user) ){
	    chomp($user = `id`);
	    $user =~ m/(uid=\d+\()(.*)\)(\s+gid=)/;
	    $user = $2;
	}
	$HPSS::USER = $user;
    }
    if( $HPSS::USER eq ""){
	&die_message("GetLogin","Cannot get user id by any method\n");
    } else {
	$HPSS::USER;
    }
}

#
# Get the node table in associative array %HPSS::NODES
#
sub GetNFSNode
{
    my($disk)=@_;

    if( defined($HPSS::NODES{$disk}) ){
	$HPSS::NODES{$disk};
    } else {
	"";
    }
}


# -------------------------------------------------------------------
# This was added in April 2001 to finally treat the HPSS return
# codes we can parse from the log file
# -------------------------------------------------------------------
sub hpss_parse_log
{
    my($dbObj,$DataBase,$logfile)=@_;
    my($line,$tmp,$job,$cmd,$sth,$date);
    my($reason,$requeue,$pause,$st);
    my(@items,@all);

    &info_message("hpss_parse_log","Parsing $logfile\n");
    $pause = 0;
    $st    = "";
    $job   = $logfile;
    $job   =~ s/.*\///g;
    $job   =~ s/\..*//g;

    if ( open(FLOG,"$logfile") ){
	while ( defined($line = <FLOG>) ){
	    @items = split(" ",$line);
	    if($items[2] eq "FAILED"){
		# default
		$reason = "Unkown Error : Batch system error $items[4]";
		$requeue= 0;
		# see if we have that one in our built-in table.
		$tmp    = int($items[4]);

		if( $tmp != 0){
		    $tmp = -$tmp;
		    #&info_message("hpss_parse_log","Searching for errno=$tmp\n");
		    $sth = $dbObj->prepare("SELECT * FROM StatusInfo WHERE id=$tmp");
		    if($sth){
			$sth->execute();
			@all = $sth->fetchrow();
			#&info_message("hpss_parse_log",join(";",@all)."\n");
			if($#all != -1){
			    $reason  = $all[1];
			    $requeue = $all[2];
			    $pause  += $all[3];
			    if ( $all[3] != 0){
				$job =~ m/(.*_)(\d+)/;
				&info_message("hpss_parse_log","HPSS Error=$tmp [$reason] found in $2\n");
				# one error returned for now
				if ($st eq ""){
				    $st = "HPSS Error=$tmp [$reason] found in $2";
				}
			    }
			    if($requeue){ $reason .= " *** REQUEUED ***";}
			}
			$sth->finish();
		    } else {
			&info_message("hpss_parse_log","Prepare command failed\n");
		    }
		}


		# In any cases, this one has failed.
		#&info_message("hpss_parse_log","$items[1]\n");

		$line = (split("\@",$items[1]))[0];
		$line = (split("\/",$line))[2];
		($user,$fid) = split(/\./,$line);

		# BUT note that this is "soft" i.e. if in the mean time, the
		# user has resubmitted it and everything was fine, the table
		# will NOT accept an update. We are basically trapping ONLY
		# the files
		# falsly beleived to be "restored".
		&info_message("hpss_parse_log","Catching $user $fid ??\n");
		$date= &Today();
		$date=~ s/://g;
		$cmd = "INSERT INTO AccntGlobal VALUES($fid,\"$user\",$date,0,\"$reason\")";
		if( ! $dbObj->do($cmd) ){
		    &info_message("hpss_parse_log","$fid failed insert with error [".$DBI::errstr."]\n");
		    if ( $DBI::errstr =~ m/Duplicate entry/i ){
			$cmd = "UPDATE AccntGlobal SET PDate=$date, user=\"$user\", Status=\"$reason\" WHERE id=$fid";
			if ( ! $dbObj->do($cmd) ){
			    &info_message("hpss_parse_log","$fid failed to execute $cmd [".$DBI::errstr."]\n");
			}
		    } else {
			&info_message("hpss_parse_log","$fid failed to execute $cmd [".$DBI::errstr."]\n");
		    }
		}
		#else {
		# Set it to failure or requeue
		&info_message("hpss_parse_log","$fid will now set $HPSS::DDBTBLNAM id=$fid with Status=".($requeue?4:3)."\n");
		if($requeue){
		    $dbObj->do("UPDATE LOW_PRIORITY $HPSS::DDBTBLNAM SET Status=4, Retries=Retries+1 WHERE id=$fid");
		} else {
		    $dbObj->do("UPDATE LOW_PRIORITY $HPSS::DDBTBLNAM SET Status=3 WHERE id=$fid");
		}
		#}
	    }
	}
	close(FLOG);
    } else {      # open(FLOG,...
	 &info_message("hpss_parse_log","*** FAILURE to open $logfile\n");
    }
    return ($pause,$st);
}



1;


#  ----------------------- :
#    Date of Revision      :  9-DEC-1998
#    Change Author         : JLAURET
#    Purpose of Revision   : Turn it into a module.
#                          : Next step (if necessary) would be to turn it into
#                            a package with real Object-like interface.
#  ----------------------- :
#    Date of Revision      : 11-FEB-1999
#    Change Author         : JLAURET
#    Purpose of Revision   :  Several places have return value while not
#                          : necessary but left for consistency.
#  ----------------------- :
#    Date of Revision      : XX-APR-2001
#    Change Author         : JLAURET
#    Purpose of Revision   :  Missing advertized option -k, made the log file
#                          : treatement here, minor bug fixes, better parsing
#           (now accepts -r /disk/file i.e. without node name), reshaped help,
#           and -v option.
#
# See the Changes file for then on for a history of changes.
#
# Copyright 1998-2000 (c) Jerome Lauret <jlauret at mail.chem.sunysb.edu>
# Copyright 2000-2020 (c) Jerome Lauret <jlauret at bnl.gov>
# Distributed under the GNU General Public License
#



