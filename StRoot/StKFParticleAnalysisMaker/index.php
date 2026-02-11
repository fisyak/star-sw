<!doctype html>
<html>

<head>
  <meta charset="UTF-8">
  <title>KFParticle Analysis</title>
  <link rel="stylesheet" href=".style.css">
  <script src=".sorttable.js"></script>
</head>

&nbsp;<br>
<?php
$DD = ''; 
$plots = array(
	       "Title*.txt"
	       ,"K0s*.png"
	       ,"ppbarM2.png"
	       ,"dEdx.png"
	       ,"Hyperons.png"
	       ,'Mass_H34L.png'
	       );
//________________________________________________________________________________
function latest_File($directory,$pattern) {
  // Get all files in the directory
  $files = array_filter(scandir($directory), function($file) use ($directory) {
      return is_file($directory . DIRECTORY_SEPARATOR . $file);
    });
  // Create an associative array with filename => modification time
  $fileModTimes = [];
  foreach ($files as $file) {
    if (preg_match($pattern, $file)) {
      $filePath = $directory . DIRECTORY_SEPARATOR . $file;
      $fileModTimes[$file] = filemtime($filePath);
    }
  }
  // Sort files by modification time descending (newest first)
  arsort($fileModTimes);

  // $fileModTimes now contains files ordered by time
  foreach ($fileModTimes as $file => $modTime) {
    echo $file . ' - ' . date('Y-m-d H:i:s', $modTime) . "<br>";
  }
  return $file;
}
//________________________________________________________________________________
function build_page($year,$section,$figNo,$Plots,$DD,$dirs) {
  $runs = "";
  foreach ($dirs as $r) {$runs = $runs . " " . $r;}
  $html = '  <hr>  <h3><a name="' . $year . '">' . $year . ': ' . $runs .  '</a></h3>  &nbsp;<br>  <hr>';
  $figNo = 0;
  // start table
  $html .= '<table width="90%" border="1" cellspacing="2" cellpadding="0">';
  print("$html\n"); $html = "";
  foreach( $Plots as $fig) {
    $html .= '<tr>';
    foreach($dirs as $dir) {
      $html .= '<th>' . $dir . '</th>';
    }
    $html .= '</tr>';
    $figNo++;
    $html .= '<tr>';
  print("$html\n"); $html = "";
    $dirNo = 0;
    foreach($dirs as $dir) {
      $pattern = $dir . "/" . $fig;
      //      $files = latest_File($dir,$fig);
      $files = [];
      exec("ls -1tr $pattern 2> /dev/null",$files);
      $count = count($files);
      if ($count == 0) {$files[] = "";}
      //      print_r($files);
      $dirNo++;
      if ($dirNo == 1) {
	$html .= '<td><a name="' . $section . 'Fig.' . $figNo. '">Fig.' . $figNo . '</a>';
      } else {
	$html .= '<td>';
      }
      if ( $figNo == 1) {
	$html .= '<object data="' . $files[0] . '"  type="text/plain" width="400" style="height: 300px"></td>';
      } else {
	$html .= '<img src="' . $files[0] . '" alt="" width="400" border="0"></td>';
      }
    }
    $html .= '</tr>';
  print("$html\n"); $html = "";
  }
  // finish table and return it
  $html .= '</table>';
  print("$html");
  return $html;
}
//________________________________________________________________________________
?>
<body>
<h1>KFParticle Analysis</h1>
<h2>Samples</h2>
<h2>Legend</h2>
<p>The plots are designed to see diffrences between different datasets and different productions in Ks0, p/pbar M2, dE/dx, and hyperons including BES-I sample.
  The datasets are grouped by year of data taking  and energies.

  <ul>
  <li>HLT means that these data set is available on HLT farm.
  <li>RCF means that these data set is available on RCF farm.
  <li>dev means the Fast Offline.
  </ul>

   
<?php
  $years = [];
exec("ls -1d 20??", $years); //, $return_val);

//print_r($years);
$section = 0;
$figNo = 0;
$prodTotal = [];
$year = 0;
foreach ($years as $year) {
  //  print("<h2>$year</h2>\n");
  $runs = [];
  exec("cd $year; ls -1d * | sed -e 's/_.*//' -e 's/\.[a-zA-Z].*//' | sort -u", $runs);
//    print "$year\n";
//    print_r($runs);
  foreach ($runs as $run) {
    //    print "$run\n";
    $prods = [];
    //    exec("ls -1dr $year/$run*P2*; ls -ldt $year/$run*TFG* ", $prods);
    //    exec("cd $year; ls -1dr $run*", $prods);
    exec("ls -1dr $year/$run*", $prods);
    //    print_r($prods);
    // sort P before TFG
    $prodP = []; $p = 0;
    $prodT = []; $t = 0;
    $prodU = []; $u = 0;
    
    foreach ($prods as $prod) {
      if (preg_match("/P2/",$prod, $matches)) {
	$prodP[] = $prod;
        $p++;
      } else if (preg_match("/TFG/",$prod, $matches)) {
	$prodT[] = $prod;
        $t++;
      } else {
	$prodU[] = $prod;
        $u++;
      }
    }
    //    print ("p = $p, t = $t, u = $u\n");
    $prodSorted = [];
    foreach ($prodP as $p) {array_push($prodSorted, $p);}
    foreach ($prodT as $p) {array_push($prodSorted, $p);}
    foreach ($prodU as $p) {array_push($prodSorted, $p);}
    $count = count($prodSorted);
    $total = count($prodTotal);
    //    print("count = $count, total = $total\n");
    //    print_r($prodSorted);
    if ($total + $count <= 4) {
      foreach ($prodSorted as $p) {array_push($prodTotal, $p);}
      $total = count($prodTotal);
      if ($total >= 4) {
	//	print("prodTotal =============== \n");
	//	print_r($prodTotal);
	build_page($year,++$section,$figNo,$plots,"",$prodTotal);
	$prodTotal = [];
      }
    } else if ($total > 0) {
      //      print("prodTotal =============== \n");
      //      print_r($prodTotal);
      build_page($year,++$section,$figNo,$plots,"",$prodTotal);
      $prodTotal = [];
      foreach ($prodSorted as $p) {array_push($prodTotal, $p);}
      $total = count($prodTotal);
      if ($total >= 4) {
	//	print("prodTotal =============== \n");
	//	print_r($prodTotal);
	build_page($year,++$section,$figNo,$plots,"",$prodTotal);
	$prodTotal = [];
      }
    } if ($total >= 4) {
      //      print("prodTotal =============== \n");
      //      print_r($prodTotal);
      build_page($year,++$section,$figNo,$plots,"",$prodTotal);
      $prodTotal = [];
    } else if ($total == 0 && $count > 3) {
      foreach ($prodSorted as $p) {array_push($prodTotal, $p);}
      //      print("prodTotal =============== \n");
      //      print_r($prodTotal);
      build_page($year,++$section,$figNo,$plots,"",$prodTotal);
      $prodTotal = [];
    }
  }
}
$total = count($prodTotal);
if ($total > 0) {
  //  print("prodTotal =============== \n");
  //  print_r($prodTotal);
  build_page($year,++$section,$figNo,$plots,"",$prodTotal);
}
/*
//echo $return_val;
        // Opens directory
        $myDirectory=opendir(".");
        
        // Gets each entry
        while($entryName=readdir($myDirectory)) {
          $dirArray[]=$entryName;
        }
        // Closes directory
        closedir($myDirectory);
        // Counts elements in array
        $indexCount=count($dirArray);
        
        // Sorts files
        sort($dirArray);
        
        // Loops through the array of files
        for($index=0; $index < $indexCount; $index++) {
          $year = $dirArray[$index];
     	  if (! fnmatch("20??",$year)) {continue;}
          // Gets File Names
          $name=$dirArray[$index];
          $namehref=$dirArray[$index];
          // Gets file size 
          $size=number_format(filesize($dirArray[$index]));
          
          // Gets Date Modified Data
	  //          $modtime=date("M j Y g:i A", filemtime($dirArray[$index]));
	  //          $timekey=date("YmdHis", filemtime($dirArray[$index]));
	  $subDir = opendir($year);
          // Gets each entry
	  $productions = "";
	  $count = 0;
          while($entryName=readdir($subDir)) {
	     $m = strncmp(".",$entryName,1);
//	     echo "$entryName  $m\n";
	     if ($m == 0) continue;
             $subdirArray[]=$entryName;
	     $productions = $productions . $entryName . " ";
             $count++;
	     if ($count > 4) {
	       print("<h2>$year\t$productions</h2>\n");
	       $productions = "";
	       $count = 0;
	     }
          }
          // Print 'em
	  if ($count > 0) {
	    print("<h2>$year\t$productions</h2>\n");
	  }	
	}
*/
      ?>

   
</body>

</html>
