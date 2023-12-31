<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html> 
  <head>
    <title>Reconstruction versus Simulation</title>
  </head>
  <body>
    <h1>Reconstruction versus Simulation</h1>
    <h2>Legend</h2>
<p>The plots are designed to answer on the following questions:
  <ul>
      <li> What tracks (globals  and primaries) can be considered as "good" ones depending on total no. of fit points and no. of bad hits ? </li>
      <li> What is the track parameters and their errors dependence on the track kinematics (&phi;, &eta;, 1/pT) ? </li>
      <li> What is the track paramerer pulls dependence on above kinematics ? </li>
      <li> What is the track reconstruction efficiencies for : </li>
      <ul>
           <li> Geometrical acceptance (MC only), </li>
           <li> Reconstruction effiency for track with only match between MC and RC </li>
           <li> Clones, for multiple (>1) match between single MC track to RC one, </li>
           <li> Lost tracks, MC tracks which have no RC partner. </li>
           <li> Ghost tracks, RC tracks which have no MC partner. </li>
      </ul> 
      <li> Color scheme: <font color=black>&nbsp;&bull; Positive</font> and <font color=red>&nbsp;&bull; Negative</font> Tracks. </li>
      <li> Results of Gauss fit for slices are presented as &bull; for &mu; and as  box for &sigma;.  </li>
      <li>Navigations:
      <ul>
      <li> <name="#1.1.1">Global tracks
      </ul>
  </ul>
<hr>
      <?php
$DD = '';
//$dirs = array('Piplus_200_20201503', 'Piplus_300_20201503', 'Piplus_701_20214001', 'Proton_701_20214001', 'Proton_702_20214001', 'Proton_703_20214001');
$dirs = array('AuAu_200_production_2014_Piminus_P18ih.SL18h');
$TracksVertices = array("Tracks","Vertices");
$TitleTrType = array("Global", "Primary");
$TitlePiDtype = array("dEdxPiD", "ToFPiD");
$TitleCharge = array("(+)", "(-)");   
$NamesF    = array("electron","antiproton","kaon-","pion-","muon-","dbar","tbar","He3Bar","alphabar"
	      "positron","proton"    ,"kaon+","pion+","muon+","deuteron"   ,"triton"   ,"He3"    ,"alpha");
$ParticleType = array("All","Pion");
$VarSet = array("NoHits","EtapT");
$dEdxTypes = array("I70","Fit","dNdx");
$ToFTypes = array("dM2","dBetaInv");
/*
foreach ($car as $x => $y) {
  echo "$x: $y <br>";
}
*/

$plotNameMatch = array(
 "Mc" =>       "Mc tracks All",                        
 "Tpc" =>      "Mc tracks which have >= 15 Mc Tpc Hits",        
 "Rec" =>      "Rc tracks matched with only Mc track",                
 "Clone" =>    "Mc tracks matched with > 1 Rc track (Clone)",             
 "Ghost" =>    "Rc tracks without Mc partner",                  
 "Lost" =>     "Mc tracks without reconstructed one",               
 "ToF" =>      "Mc tracks which have >= 15 Mc Tpc and > 0 ToF Hits",
 "RecToF" =>   "Rc tracks matched with only Mc track with ToF",
 "GhostToF" => "Rc tracks without Mc partner with ToF",
 "LostToF" =>  "Mc tracks without reconstructed one in ToF",
 "EToF" =>     "Mc tracks which have >= 15 Mc Tpc and > 0 EToF Hits",
 "RecEToF" =>  "Rc tracks matched with only Mc track with EToF",
 "GhostEToF" =>"Rc tracks without Mc partner with EToF",
 "LostEToF" => "Mc tracks without reconstructed one in EToF",
 "Hft" =>      "Mc tracks with HFT",
 "RecHft" =>   "Rc tracks matched with only Mc track with HFT",
 "GhostHft" => "Rc tracks with HFT without Mc partner with HFT",
 "LostHft" =>  "Mc tracks without reconstructed one in Hft"
);
$plotVar = array(         //no.fit                  
		 "ChiSqXY" =>   "#chi^{2}_{Track}/NDF",        
		 "ChiSqZ" =>    "#chi^{2}_{Vx} ",              
		 "dDcaXY" =>    "difference in Dca_{XY}",      
		 "dDcaZ" =>     "difference in Dca_{Z}",       
		 "dPsi" =>      "difference in  #Psi ",        
		 "dPti" =>      "difference in q/pT",          
		 "dPtiR" =>     "difference in relative q/pT", 
		 "dTanL" =>     "difference in tan( #lambda )",
		 "deta" =>      "difference in  #eta",         
		 "pDcaXY" =>    "pull in Dca_{XY}",            
		 "pDcaZ" =>     "pull in Dca_{Z}",             
		 "pPsi" =>      "pull in  #Psi ",              
		 "pPti" =>      "pull in q/pT",                
		 "pPtiR" =>     "pull in relative q/pT",       
		 "pTanL" =>     "pull in tan( #lambda )",      
		 "peta" =>      "pull for  #eta",              
		 "Phi" =>       "#phi (degrees)"              
			  );
$ParticleType = array("All","Pion");
$VarSet = array("NoHits","EtapT");
$dEdxTypes = array("I70","Fit","dNdx");
$ToFTypes = array("dM2","dBetaInv");
$pmNames[2] = array("pos","neg");
$eff = array(
	     "GeomA" =>"Geometrical acceptance",
	     "EffA" => "Efficiency over all",   
	     "EffG" => "Efficiency wrt Geom",   
	     "CloneA" =>"Clone  over all",       
	     "CloneG" =>"Clone wrt Geom",        
	     "LostA" =>"Lost over all",         
	     "LostG" =>"Lost wrt Geom",         
	     "GhostA" =>"Ghost over all",        
	     "GhostG" =>"Ghost wrt Geom",        
	     );
//                               Eta pT  Phi
static  const Char_t *proj3[3] = {"x","y","z"};

$figNo = 0; 
function build_tableC($head,$section,$title,$tag) {
  // start table
  global $dirs;;
  global $DD;
  global $figNo;
  $html  = '<h4><a name "' . $head . ' Global  tracks.  All.Kinema">' . $section . ' ' . $title . '</a></h4>';
  $html .= '<table width="90%" border="1" cellspacing="2" cellpadding="0">';
  // header row
  $html .= '<tr>';
  foreach($dirs as $dir) {
    $html .= '<th>' . $dir . '</th>';
  }
  $html .= '</tr>';
  $ndirs = count($dirs);
  $dir = $dirs[$ndirs-1];
  $path = $dirs[0] . "/" . $tag . '*.png';
  //  echo "path = $path";
  $figs = glob($path); // echo "ndirs = $ndirs, figs = $figs[0] $figs[1] ";
  foreach( $figs as $figD) {
    $fig = basename($figD);
    $figNo++;
    $html .= '<tr>';
    $dirNo = 0;
    foreach($dirs as $dir) {
      $dirNo++;
      if ($dirNo == 1) {
	$html .= '<td><a name="' . $section . 'Fig.' . $figNo. '">Fig.' . $figNo . '</a>';
      } else {
	$html .= '<td>';
      }
      $html .= '<img src="' . $DD . $dir .'/' . $fig . '" alt="" width="400" border="0"></td>';
    }
    $html .= '</tr>';
  }
  // finish table and return it
  $html .= '</table>';
  return $html;
}
?>
<H1>1. Tracks</H1>
<H2>1.1. Quality of reconstructed tracks with respect to MC.</H2>
<h3>1.1.1. Global tracks.</h3>
<hr>
<?php 
echo '<H2>1.1. Quality of reconstructed tracks with respect to MC.</H2>';
#if 0
foreac
echo '<h3>1.1.1. Global tracks.</h3>';
echo build_tableC('Global  tracks.  All. No. of fit and bad points.','1.1.1.1', 'Global  tracks.  All. No. of fit and bad points.',    'Tracks_Global_Rec_All_NoHits_'); 
echo build_tableC('Global  tracks.  All.Kinema',                     '1.1.1.2', 'Global  tracks.  All.Track parameters',               'Tracks_Global_Rec_All_EtapT_C');
echo build_tableC('Global  tracks.  All.Kinema',                     '1.1.1.2', 'Global  tracks.  All.Track parameters',               'Tracks_Global_Rec_All_EtapT_d');
echo build_tableC('Global  tracks.  All.Kinema',                     '1.1.1.2', 'Global  tracks.  All.Track parameters',               'Tracks_Global_Rec_All_EtapT_p');
echo build_tableC('Global  tracks.  Pions.NoHits',                   '1.1.1.3', 'Global  tracks.  Pions. No. of fit and bad points.',  'Tracks_Global_Rec_Pion_NoHits_');
echo build_tableC('Global  tracks.  Pions.Kinema',                   '1.1.1.4', 'Global  tracks.  Pions.Track parameters',             'Tracks_Global_Rec_Pion_EtapT_C');
echo build_tableC('Global  tracks.  Pions.Kinema',                   '1.1.1.4', 'Global  tracks.  Pions.Track parameters',             'Tracks_Global_Rec_Pion_EtapT_d');
echo build_tableC('Global  tracks.  Pions.Kinema',                   '1.1.1.4', 'Global  tracks.  Pions.Track parameters',             'Tracks_Global_Rec_Pion_EtapT_p');
#endif
echo '<h3>1.1.2. Primary tracks. </h3>';
echo build_tableC('Primary  tracks.  All.NoHits',		     '1.1.2.1', 'Primary  tracks.  All. No. of fit and bad points.',   'Tracks_Primary_Rec_All_NoHits_'); 
echo build_tableC('Primary  tracks.  All.Kinema',                    '1.1.2.2', 'Primary  tracks.  All.Track parameters',              'Tracks_Primary_Rec_All_EtapT_C');
echo build_tableC('Primary  tracks.  All.Kinema',                    '1.1.2.2', 'Primary  tracks.  All.Track parameters',              'Tracks_Primary_Rec_All_EtapT_d');
echo build_tableC('Primary  tracks.  All.Kinema',                    '1.1.2.2', 'Primary  tracks.  All.Track parameters',              'Tracks_Primary_Rec_All_EtapT_p');
echo build_tableC('Primary  tracks.  Pions.NoHits',                  '1.1.2.3', 'Primary  tracks.  Pions. No. of fit and bad points.', 'Tracks_Primary_Rec_Pion_NoHits_');
echo build_tableC('Primary  tracks.  Pions.Kinema',                  '1.1.2.4', 'Primary  tracks.  Pions.Track parameters',            'Tracks_Primary_Rec_Pion_EtapT_C');
echo build_tableC('Primary  tracks.  Pions.Kinema',                  '1.1.2.4', 'Primary  tracks.  Pions.Track parameters',            'Tracks_Primary_Rec_Pion_EtapT_d');
echo build_tableC('Primary  tracks.  Pions.Kinema',                  '1.1.2.4', 'Primary  tracks.  Pions.Track parameters',            'Tracks_Primary_Rec_Pion_EtapT_p');
// echo '<H2>1.2. Track reconstuction efficiencies.</H2>';
// echo '<h3>1.2.1. Global tracks. All.</h3>';
// echo build_tableC('Global tracks.  All. Geometrical acceptance',     '1.2.1.1', 'Global tracks.  All. Geometrical acceptance.',        'Tracks_Global_Tpc_All_EtapT_GeomAPhi_');
// echo build_tableC('Global tracks.  All. Efficiency over all',        '1.2.1.2', 'Global tracks.  All. Efficiency over all.',           'Tracks_Global_Rec_All_EtapT_EffAPhi_');
// echo build_tableC('Global tracks.  All. Efficiency wrt Geom',        '1.2.1.3', 'Global tracks.  All. Efficiency wrt Geom.',           'Tracks_Global_Rec_All_EtapT_EffGPhi_');
// echo build_tableC('Global tracks.  All. Clone  over all',            '1.2.1.4', 'Global tracks.  All. Clone  over all.',               'Tracks_Global_Clone_All_EtapT_CloneAPhi_');
// echo build_tableC('Global tracks.  All. Clone wrt Geom',             '1.2.1.5', 'Global tracks.  All. Clone wrt Geom.',                'Tracks_Global_Clone_All_EtapT_CloneGPhi_');
// echo build_tableC('Global tracks.  All. Lost over all',              '1.2.1.6', 'Global tracks.  All. Lost over all.',                 'Tracks_Global_Lost_All_EtapT_LostAPhi_');
// echo build_tableC('Global tracks.  All. Lost wrt Geom',              '1.2.1.7', 'Global tracks.  All. Lost wrt Geom.',                 'Tracks_Global_Lost_All_EtapT_LostGPhi_');
// echo build_tableC('Global tracks.  All', 'Ghost over all',           '1.2.1.8', 'Global tracks.  All', 'Ghost over all.',              'Tracks_Global_Ghost_All_EtapT_GhostAPhi_');
// echo build_tableC('Global tracks.  All', 'Ghost wrt Geom',           '1.2.1.9', 'Global tracks.  All', 'Ghost wrt Geom.',              'Tracks_Global_Ghost_All_EtapT_GhostGPhi_');
// echo '<h3>1.2.2. Global tracks. Pions.</h3>';
// echo build_tableC('Global tracks.  Pions. Geometrical acceptance',   '1.2.2.1', 'Global tracks.  Pions. Geometrical acceptance.',      'Tracks_Global_Tpc_Pion_EtapT_GeomAPhi_');
// echo build_tableC('Global tracks.  Pions. Efficiency over all',      '1.2.2.2', 'Global tracks.  Pions. Efficiency over all.',         'Tracks_Global_Rec_Pion_EtapT_EffAPhi_');
// echo build_tableC('Global tracks.  Pions. Efficiency wrt Geom',      '1.2.2.3', 'Global tracks.  Pions. Efficiency wrt Geom.',         'Tracks_Global_Rec_Pion_EtapT_EffGPhi_');
// echo build_tableC('Global tracks.  Pions. Clone  over all',          '1.2.2.4', 'Global tracks.  Pions. Clone  over all.',             'Tracks_Global_Clone_Pion_EtapT_CloneAPhi_');
// echo build_tableC('Global tracks.  Pions. Clone wrt Geom',           '1.2.2.5', 'Global tracks.  Pions. Clone wrt Geom.',              'Tracks_Global_Clone_Pion_EtapT_CloneGPhi_');
// echo build_tableC('Global tracks.  Pions. Lost over all',            '1.2.2.6', 'Global tracks.  Pions. Lost over all.',               'Tracks_Global_Lost_Pion_EtapT_LostAPhi_');
// echo build_tableC('Global tracks.  Pions. Lost wrt Geom',            '1.2.2.7', 'Global tracks.  Pions. Lost wrt Geom.',               'Tracks_Global_Lost_Pion_EtapT_LostGPhi_');
// echo build_tableC('Global tracks.  Pions. Ghost over all',           '1.2.2.8', 'Global tracks.  Pions', 'Ghost over all.',            'Tracks_Global_Ghost_Pion_EtapT_GhostAPhi_');
// echo build_tableC('Global tracks.  Pions. Ghost wrt Geom',           '1.2.2.9', 'Global tracks.  Pions', 'Ghost wrt Geom.',            'Tracks_Global_Ghost_Pion_EtapT_GhostGPhi_');
// echo '<h3>1.2.3. Primary tracks. All.</h3>';
// echo build_tableC('Primary tracks.  All. Geometrical acceptance',    '1.2.3.1', 'Primary tracks.  All. Geometrical acceptance.',       'Tracks_Primary_Tpc_All_EtapT_GeomAPhi_');
// echo build_tableC('Primary tracks.  All. Efficiency over all',       '1.2.3.2', 'Primary tracks.  All. Efficiency over all.',          'Tracks_Primary_Rec_All_EtapT_EffAPhi_');		     
// echo build_tableC('Primary tracks.  All. Efficiency wrt Geom',	     '1.2.3.3', 'Primary tracks.  All. Efficiency wrt Geom.',          'Tracks_Primary_Rec_All_EtapT_EffGPhi_');		     
// echo build_tableC('Primary tracks.  All. Clone  over all',    	     '1.2.3.4', 'Primary tracks.  All. Clone  over all.',              'Tracks_Primary_Clone_All_EtapT_CloneAPhi_');		     
// echo build_tableC('Primary tracks.  All. Clone wrt Geom',     	     '1.2.3.5', 'Primary tracks.  All. Clone wrt Geom.',               'Tracks_Primary_Clone_All_EtapT_CloneGPhi_');		     
// echo build_tableC('Primary tracks.  All. Lost over all',      	     '1.2.3.6', 'Primary tracks.  All. Lost over all.',                'Tracks_Primary_Lost_All_EtapT_LostAPhi_');		     
// echo build_tableC('Primary tracks.  All. Lost wrt Geom',      	     '1.2.3.7', 'Primary tracks.  All. Lost wrt Geom.',                'Tracks_Primary_Lost_All_EtapT_LostGPhi_');		     
// echo build_tableC('Primary tracks.  All. Ghost over all',   	     '1.2.3.8', 'Primary tracks.  All. Ghost over all.',               'Tracks_Primary_Ghost_All_EtapT_GhostAPhi_');		     
// echo build_tableC('Primary tracks.  All. Ghost wrt Geom',    	     '1.2.3.9', 'Primary tracks.  All. Ghost wrt Geom.',               'Tracks_Primary_Ghost_All_EtapT_GhostGPhi_');                
// echo '<h3>1.2.4. Primary tracks. Pions.</h3>';
// echo build_tableC('Primary tracks.  Pions. Geometrical acceptance',  '1.2.4.1', 'Primary tracks.  Pions. Geometrical acceptance.',     'Tracks_Primary_Tpc_Pion_EtapT_GeomAPhi_');
// echo build_tableC('Primary tracks.  Pions. Efficiency over all',     '1.2.4.2', 'Primary tracks.  Pions. Efficiency over all.',        'Tracks_Primary_Rec_Pion_EtapT_EffAPhi_');
// echo build_tableC('Primary tracks.  Pions. Efficiency wrt Geom',     '1.2.4.3', 'Primary tracks.  Pions. Efficiency wrt Geom.',        'Tracks_Primary_Rec_Pion_EtapT_EffGPhi_');
// echo build_tableC('Primary tracks.  Pions. Clone  over all',         '1.2.4.4', 'Primary tracks.  Pions. Clone  over all.',            'Tracks_Primary_Clone_Pion_EtapT_CloneAPhi_');
// echo build_tableC('Primary tracks.  Pions. Clone wrt Geom',          '1.2.4.5', 'Primary tracks.  Pions. Clone wrt Geom.',             'Tracks_Primary_Clone_Pion_EtapT_CloneGPhi_');
// echo build_tableC('Primary tracks.  Pions. Lost over all',           '1.2.4.6', 'Primary tracks.  Pions. Lost over all.',              'Tracks_Primary_Lost_Pion_EtapT_LostAPhi_');
// echo build_tableC('Primary tracks.  Pions. Lost wrt Geom',           '1.2.4.7', 'Primary tracks.  Pions. Lost wrt Geom.',              'Tracks_Primary_Lost_Pion_EtapT_LostGPhi_');
// echo build_tableC('Primary tracks.  Pions', 'Ghost over all',        '1.2.4.8', 'Primary tracks.  Pions. Ghost over all.',             'Tracks_Primary_Ghost_Pion_EtapT_GhostAPhi_');
// echo build_tableC('Primary tracks.  Pions', 'Ghost wrt Geom',        '1.2.4.9', 'Primary tracks.  Pions. Ghost wrt Geom.',             'Tracks_Primary_Ghost_Pion_EtapT_GhostGPhi_');
// echo '<H2>1.3. TPC dE/dx PiD.</H2>';
// echo '<h3>1.3.1. Global tracks. </h3>';
// echo build_tableC('Global  tracks. e-',                              '1.3.1.1', 'Global  tracks. e-',      
// echo build_tableC('Global  tracks. proton',                          '1.3.1.2', 'Global  tracks. proton',  'Tracks_Global_dEdxPiD_proton_ZI70');   
// echo build_tableC('Global  tracks. kaon-',                           '1.3.1.3', 'Global  tracks. kaon-',   'Tracks_Global_dEdxPiD_kaon_ZI70');	   
// echo build_tableC('Global  tracks. pi-',                             '1.3.1.4', 'Global  tracks. pi-',     'Tracks_Global_dEdxPiD_pion_ZI70');	   
// echo build_tableC('Global  tracks. mu-',    			     '1.3.1.5', 'Global  tracks. mu-',     'Tracks_Global_dEdxPiD_muon_ZI70');	    
// 													   'Tracks_Global_dEdxPiD_deuteron_ZI70'); 
// echo '<h3>1.3.2. Primary tracks. </h3>';
// echo build_tableC('Primary  tracks. proton',			     '1.3.2.2', 'Primary  tracks. proton', 'Tracks_Primary_dEdxPiD_kaon_ZI70');	  
// echo build_tableC('Primary  tracks. kaon-', 			     '1.3.2.3', 'Primary  tracks. kaon-',  'Tracks_Primary_dEdxPiD_pion_ZI70');	  
// echo '<H2>1.4. ToF PiD</H2>';
// echo '<h3>1.4.1. Global tracks. </h3>';
// echo build_tableC('Global  tracks. e-',     			     '1.4.1.1', 'Global  tracks. e-',      'Tracks_Global_ToFPiD_proton_dM2');	  
// echo build_tableC('Global  tracks. proton', 			     '1.4.1.2', 'Global  tracks. proton',  'Tracks_Global_ToFPiD_kaon_dM2');	  
// echo build_tableC('Global  tracks. kaon-',  			     '1.4.1.3', 'Global  tracks. kaon-',   'Tracks_Global_ToFPiD_pion_dM2');	  
// echo build_tableC('Global  tracks. pi-',    			     '1.4.1.4', 'Global  tracks. pi-',     'Tracks_Global_ToFPiD_muon_dM2');	  
// echo build_tableC('Global  tracks. mu-','   			      1.4.1.5', 'Global  tracks. mu-',     'Tracks_Global_ToFPiD_deuteron_dM2');	  

// echo '<h3>1.4.2. Primary tracks. </h3>';
// echo build_tableC('Primary  tracks. e-',     			     '1.4.1.1', 'Primary  tracks. e-',     'Tracks_Primary_ToFPiD_elector_dM2');	  
// echo build_tableC('Primary  tracks. proton',			     '1.4.2.2', 'Primary  tracks. proton', 'Tracks_Primary_ToFPiD_kaon_dM2');	  
// echo build_tableC('Primary  tracks. kaon-', 			     '1.4.2.3', 'Primary  tracks. kaon-',  'Tracks_Primary_ToFPiD_pion_dM2');	  
// echo build_tableC('Primary  tracks. pi-',    			     '1.4.2.4', 'Primary  tracks. pi-',    'Tracks_Primary_ToFPiD_muon_dM2');       

?>
<hr style="width: 100%; height: 2px;">
<hr>
</body>
</html>
