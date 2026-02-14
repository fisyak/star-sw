<!doctype html>
<!--
<?php
 Header("Cache-Control: must-revalidate");

 $offset = 60 * 60 * 24 * 3;
 $ExpStr = "Expires: " . gmdate("D, d M Y H:i:s", time() + $offset) . " GMT";
 Header($ExpStr);
?>
-->
<meta http-equiv="Cache-Control" content="no-cache, no-store, must-revalidate" />
<meta http-equiv="Pragma" content="no-cache" />
<meta http-equiv="Expires" content="0" />
<html>

<head>
  <meta charset="UTF-8">
  <title>KFParticle Analysis</title>
  <link rel="stylesheet" href=".style.css">
  <script src=".sorttable.js"></script>
</head>

&nbsp;<br>
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
exec("ls -1d 20??", $years); //, $return_val);
print("<ol>\n");
foreach ($years as $year) {
  print("<li><a href=\"$year/indexKFPQA.php\">$year</a>\n");
}
print("</ol>\n");

?>

   
</body>

</html>
