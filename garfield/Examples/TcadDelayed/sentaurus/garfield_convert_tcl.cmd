file mkdir output/converted
cd output/converted

# Convert all .tdr files to .dat and .grd for use with Garfield++
set tdr_files [glob "../n@node|weighting_vector@*.tdr"]

foreach tdr $tdr_files {
  puts "$tdr"
  catch {exec tdx -dd "$tdr" "$tdr"}
}
