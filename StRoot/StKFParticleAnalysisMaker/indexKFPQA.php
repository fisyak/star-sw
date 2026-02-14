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
	       "Title*Ks_M_*.txt"
	       ,"Ks_M*.png"
	       ,"Title*Ks_y-phi-M*.txt"
	       ,"Ks_y-phi-M*.png"
	       ,"ppbarM2.png"
	       ,"dEdx.png"
	       ,"Hyperons.png"
	       ,'Mass_H34L.png'
	       );
//________________________________________________________________________________
function build_page($section,$figNo,$Plots,$DD,$dirs) {
  $runs = "";
  foreach ($dirs as $r) {$runs = $runs . " " . $r;}
  $html = '  <hr>  <h3><a name="' . $dirs[0] . '">'  . $runs .  '</a></h3>  &nbsp;<br>  <hr>';
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
      if (preg_match("/.txt/",$files[0], $matches)) {
	$html .= '<object data="' . $files[0] . '"  type="text/plain" width="400" style="height: 300px"></td>';
      } else {
	$html .= '<img src="' . $files[0] . '" alt="" width="400" border="0"></td>';
      }
    }
    $html .= '</tr>';
    print("$html\n"); $html = "";
  }
  $html .= '</table>';
  print("$html");
  return;
}
//________________________________________________________________________________
?>
<body>
<h1>KFParticle Analysis</h1>
<h2>Legend</h2>
<p>The plots are designed to see diffrences between different datasets and different productions in Ks0, p/pbar M2, dE/dx, and hyperons including BES-I sample.
  The datasets are grouped by year of data taking  and energies.
  <ul>
  <li>TFG productions has been done on HLT farm with TFG vesion of STAR libraries.
  <li>P2?i? stands for thee official production done on RCF.
  <li>dev means the Fast Offline.
  </ul>
<h2>Plots content</h2>
  <p>For a given data samples it is provided side by side plots for different productions (earliest one is the first).
  <ol>
    <li>Summary of Ks0 mass fit 
    <li>Invariant mass distribution
    <li>Summary of Ks0 mass fit with pT > 1 GeV/c
    <li>Invariant mass distribution with pT > 1 GeV/c
    <li> p and pbar M<sup>2</sup> distribution from BTof versus log<sub>10</sub>p
  <li>log<sub>10</sub>(dE/dx) versus log<sub>10</sub>(p)
    <li>Hyperon mass fits
    <li> H3L and H4L fits.
  </ol>

<h2>Samples</h2>

   
<?php

$years = [];
//exec("ls -1d 20??", $years); //, $return_val);
exec("basename `pwd`", $years); //, $return_val);
//print_r($years);
//print_r($years);
$section = 0;
$figNo = 0;
$prodTotal = [];
$tags = [];
foreach ($years as $year) {
  //  print("<h2>$year</h2>\n");
  $runs = [];
  //  exec("cd $year; ls -1d * | sed -e 's/_.*//' -e 's/\.[a-zA-Z].*//' | sort -u", $runs);
  exec("ls -1d * | grep -v index | sed -e 's/_.*//' -e 's/\.[a-zA-Z].*//' | sort -u", $runs);
//    print "$year\n";
//    print_r($runs);
  foreach ($runs as $run) {
    //    print "$run\n";
    $prods = [];
    //    exec("ls -1dr $year/$run*P2*; ls -ldt $year/$run*TFG* ", $prods);
    //    exec("cd $year; ls -1dr $run*", $prods);
    exec("ls -1dr $run*", $prods);
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
    if ($total + $count <= 4){//  && ($year < 2019 || $year > 2021)) {
      foreach ($prodSorted as $p) {array_push($prodTotal, $p);}
      $total = count($prodTotal);
      if ($total >= 4) {
	//	print("prodTotal =============== \n");
	//	print_r($prodTotal);
	$tags[$prodTotal[0]] = $prodTotal;
	// build_page($year,++$section,$figNo,$plots,"",$prodTotal);
	$prodTotal = [];
      }
    } else if ($total > 0) {
      //      print("prodTotal =============== \n");
      //      print_r($prodTotal);
	$tags[$prodTotal[0]] = $prodTotal;
      // build_page($year,++$section,$figNo,$plots,"",$prodTotal);
      $prodTotal = [];
      foreach ($prodSorted as $p) {array_push($prodTotal, $p);}
      $total = count($prodTotal);
      if ($total >= 4) {
	//	print("prodTotal =============== \n");
	//	print_r($prodTotal);
	$tags[$prodTotal[0]] = $prodTotal;
	// build_page($year,++$section,$figNo,$plots,"",$prodTotal);
	$prodTotal = [];
      }
    } if ($prodTotal && $total >= 4) {
      //      print("prodTotal =============== \n");
      //      print_r($prodTotal);
      //      print("total = $total\n");
      //      print_r($prodTotal);
      $tags[$prodTotal[0]] = $prodTotal;
      // build_page($year,++$section,$figNo,$plots,"",$prodTotal);
      $prodTotal = [];
    } else if ($total == 0 && $count > 3) {
      foreach ($prodSorted as $p) {array_push($prodTotal, $p);}
      //      print("prodTotal =============== \n");
      //      print_r($prodTotal);
	$tags[$prodTotal[0]] = $prodTotal;
      // build_page($year,++$section,$figNo,$plots,"",$prodTotal);
      $prodTotal = [];
    }
  }
  if ($year > 2011) {
    $total = count($prodTotal);
    if ($total > 0) {
      //  print("prodTotal =============== \n");
      //  print_r($prodTotal);
	$tags[$prodTotal[0]] = $prodTotal;
      // build_page($year,++$section,$figNo,$plots,"",$prodTotal);
    }
  }
}
$total = count($prodTotal);
if ($total > 0) {
  //  print("prodTotal =============== \n");
  //  print_r($prodTotal);
	$tags[$prodTotal[0]] = $prodTotal;
  // build_page($year,++$section,$figNo,$plots,"",$prodTotal);
}
// ancor
print "<ol>\n";
foreach ($tags as $tag) {
  $prods = "";
  foreach ($tag as $p) {$prods .=  $p . ";";}
  print '<li> <a href="#' . $tag[0] . '">' . $prods . '</a>';
  print "\n";
} 
print "</ol>\n";

foreach ($tags as $tag) {
  build_page(++$section,$figNo,$plots,"",$tag);
}?>

   
</body>

</html>
