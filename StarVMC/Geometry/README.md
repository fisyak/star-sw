# STAR detector geometry summary

This table summarizes the standard STAR detector geometry tags in `StarVMC/Geometry` and the AgML/VMC translation path (`mgr/agmlParser.py` + `mgr/Dyson`). It is derived from the canonical alias list in `StRoot/StChain/GeometryDbAliases.h` and the XML module definitions under `StarVMC/Geometry`.

For each year, the baseline tag is the entry without a trailing letter (for example, `y2015` is the baseline for `y2015a`, `y2015b`, ...). Each later tag row describes what changed relative to that baseline. Non-standard `dev*`, `upgr*`, and experimental variants are omitted.

| Year | Geometry tag | Detector modules / baseline and differences |
|---|---|---|
| 2027 | `y2027` | Baseline 2027 geometry: end-of-line placeholder tag with the cave-only setup retained as the current `y2027` configuration. |
| 2026 | `y2026` | Baseline 2026 geometry: same as `y2025/y2025a`. |
| 2026 | `y2026a` | Updated 2026 production geometry: same overall detector layout as `y2026`, but uses the `SCON15` support configuration instead of `SCON14`. |
| 2025 | `y2025` | Baseline 2025 geometry.|
| 2025 | `y2025a` | Same as `y2025`; production geometry alias identical to the 2025 production configuration. |
| 2025 | `y2025b` | Updated 2025 production geometry: same detector stack as `y2025`, but with the `SCON15` support configuration replacing `SCON14`. |
| 2024 | `y2024` | Baseline 2024 geometry. |
| 2024 | `y2024a` | Same as `y2024`; this is the 2024 production tag in the standard detector layout. |
| 2024 | `y2024b` | Same as `y2024`, but the 2024 production geometry includes the 200.0 cm FXT option. |
| 2024 | `y2024c` | Current best 2024 tag: same detector stack as `y2024b`, but with the updated support configuration and the standard production fixed-target setup. |
| 2023 | `y2023` | Baseline 2023 geometry. |
| 2023 | `y2023a` | Same as `y2023`; first production release for the 2023 configuration. |
| 2023 | `y2023b` | Same as `y2023a`; production geometry with the 200.0 cm FXT option. |
| 2023 | `y2023c` | Current best 2023 tag: same production stack as `y2023b`, but with the updated support configuration in the fixed-target setup. |
| 2022 | `y2022` | Baseline 2022 geometry: Forward tracking and calorimetry added. |
| 2022 | `y2022a` | Same as `y2022`; production geometry for the 2022 run setup. |
| 2022 | `y2022b` | Same as `y2022`; production version with the 200.0 cm FXT option. |
| 2022 | `y2022c` | Current best 2022 tag: same detector stack as `y2022b`, with the updated support configuration for the current production geometry. |
| 2021 | `y2021` | Baseline 2021 geometry. |
| 2021 | `y2021a` | Same as `y2021`; first production geometry for 2021. |
| 2021 | `y2021b` | Same as `y2021`; production geometry with the 200.0 cm FXT option. |
| 2021 | `y2021c` | Current best 2021 tag: same production stack as `y2021b`, with the updated support configuration. |
| 2020 | `y2020` | Baseline 2020 geometry. |
| 2020 | `y2020a` | Same as `y2020`; fast-offline geometry for the 2020 run period. |
| 2020 | `y2020b` | Same as `y2020`; production geometry with the 200.0 cm FXT option. |
| 2020 | `y2020c` | Current best 2020 tag: same fixed-target setup as `y2020b`, but using the updated `SCON15` support model. |
| 2019 | `y2019` | Baseline 2019 geometry. |
| 2019 | `y2019a` | Same as `y2019`; first production release geometry. |
| 2019 | `y2019b` | Same as `y2019a`; 2019 production geometry with the FXT option. |
| 2019 | `y2019c` | Current best 2019 tag: same fixed-target configuration as `y2019b`, but with the updated `SCON15` support model. |
| 2018 | `y2018` | Baseline 2018 geometry. |
| 2018 | `y2018a` | Same as `y2018`; physics production geometry A. |
| 2018 | `y2018b` | Same as `y2018`; physics production geometry B. |
| 2018 | `y2018c` | Same as `y2018`; physics production geometry C with the 200.7 cm FXT setup. |
| 2018 | `y2018d` | Current best 2018 tag: same fixed-target geometry as `y2018c`, with the corrected production support configuration. |
| 2017 | `y2017` | Baseline 2017 geometry:  HFT removed.  Return to the old support cone. |
| 2017 | `y2017a` | Same as `y2017`; production geometry for the 2017 run period. |
| 2017 | `y2017b` | Current best 2017 tag: same production stack as `y2017a`, with the updated support configuration in the current best geometry. |
| 2016 | `y2016` | Baseline 2016 geometry. |
| 2016 | `y2016a` | Same as `y2016`; production geometry for the 2016 run period. |
| 2016 | `y2016x` | Same as `y2016`; production geometry for the 2016 run period, with misalignment support. |
| 2015 | `y2015` | Baseline 2015 geometry. |
| 2015 | `y2015a` | Same as `y2015`; production geometry A. |
| 2015 | `y2015b` | Same as `y2015`; production geometry with the corrected MTD radii. |
| 2015 | `y2015c` | Same as `y2015b`; revised MTD radii corrections. |
| 2015 | `y2015d` | Same as `y2015c`; production geometry with the IST overlap correction. |
| 2015 | `y2015x` | Same as `y2015c`; production geometry with the IST overlap correction with misalignment support. |
| 2014 | `y2014` | Baseline 2014 geometry: TPC + TOF/BTOF + barrel/endcap EMC + MTD. |
| 2014 | `y2014a` | Same as `y2014`; production geometry A. |
| 2014 | `y2014b` | Same as `y2014a`; production geometry B. |
| 2014 | `y2014c` | Same as `y2014b`; production geometry with the IST overlap correction applied. |
| 2014 | `y2014x` | Same as `y2014b`; production geometry with the IST overlap correction applied with misaligment support. |
| 2013 | `y2013` | Baseline 2013 geometry: Adds PIXEL/IST in the first-cut configuration. Replace support cone with IDSM.|
| 2013 | `y2013_1` | Same as `y2013`; pixel-included 2013 geometry. |
| 2013 | `y2013_2` | Same as `y2013` but without the pixel detector; only the silicon tracker/SSD/IST layout for the no-pixel variant. |
| 2013 | `y2013_1a` | Same as `y2013_1`; first production geometry with the pixel detector. |
| 2013 | `y2013_2a` | Same as `y2013_2`; first production no-pixel geometry. |
| 2013 | `y2013_1b` | Same as `y2013_1`; second production geometry with the pixel detector. |
| 2013 | `y2013_2b` | Same as `y2013_2`; second production no-pixel geometry. |
| 2013 | `y2013_1c` | Same as `y2013_1`; final 2013 production geometry with the pixel detector. |
| 2013 | `y2013_2c` | Same as `y2013_2`; final 2013 production no-pixel geometry. |
| 2012 | `y2012` | Baseline 2012 geometry. |
| 2012 | `y2012a` | Same as `y2012`; MTD missing in the preliminary geometry. |
| 2012 | `y2012b` | Same as `y2012a`; adds the MTD to the 2012 geometry. |
| 2011 | `y2011` | Baseline 2011 geometry: TPC + TOF/BTOF + barrel/endcap EMC; standard 2011 detector layout. |
| 2011 | `y2011a` | Same as `y2011`; production geometry tag for the 2011 run period. |
| 2011 | `y2011b` | Same as `y2011a`; 2011 geometry with the wall structure included. |
| 2011 | `y2011c` | Current best 2011 tag: same physical detector stack as `y2011b`, with the standard 2011 production configuration carried forward. |
| 2010 | `y2010` | Baseline 2010 geometry: TPC + full BTOF + barrel/endcap EMC. |
| 2010 | `y2010a` | Same as `y2010`; 2010 production geometry tag. |
| 2010 | `y2010b` | Same as `y2010`; TOF fix and TPC endcap adjustments. |
| 2010 | `y2010c` | Same as `y2010`; honey sandwich fix applied in the 2010 geometry. |
| 2010 | `y2010d` | Current best 2010 tag: same 2010 production stack as `y2010c`, with the later support configuration in the current best geometry. |
| 2009 | `y2009` | Baseline 2009 geometry: TPC + TOF + barrel/endcap EMC; standard 2009 detector stack. |
| 2009 | `y2009a` | Same as `y2009`; ECal geometry update for the 2009 production configuration. |
| 2009 | `y2009b` | Same as `y2009a`; older tracking cuts in the EEMC retained for this production tag. |
| 2009 | `y2009c` | Same as `y2009`; TOF fix and TPC endcap redistribution. |
| 2009 | `y2009d` | Same as `y2009`; honey sandwich fix applied. |
| 2009 | `y2009e` | Current best 2009 tag: same 2009 detector stack as `y2009d`, with the later support configuration carried forward. |
| 2008 | `y2008` | Baseline 2008 geometry: TPC + EMC + BTOF; SVT/SSD are out and the geometry reflects the post-SVT setup. |
| 2008 | `y2008a` | Same as `y2008`; cone in a separate SCON configuration. |
| 2008 | `y2008b` | Same as `y2008`; latest TPC/ECAL/CALB configuration for 2008. |
| 2008 | `y2008c` | Same as `y2008`; TOF fix and TPC endcap reuse. |
| 2008 | `y2008d` | Same as `y2008`; honey sandwich fix. |
| 2008 | `y2008e` | Same as `y2008`; lower-EM central calorimeter cuts applied. |
| 2008 | `y2008f` | Current best 2008 tag: same 2008 production stack as `y2008e`, with the later support configuration carried forward. |
| 2007 | `y2007` | Baseline 2007 geometry: TPC + EMC + TOF in the base 2007 detector layout. |
| 2007 | `y2007g` | Same as `y2007`; SVT dead material included. |
| 2007 | `y2007h` | Same as `y2007g`; TPC2009 configuration with the 2007 detector stack. |
| 2006 | `y2006` | Baseline 2006 geometry: TPC + EMC + FPD + support structure, with the SSD and detector updates from the 2006 baseline. |
| 2006 | `y2006c` | Same as `y2006`; 2006 geometry with the new FPD and SSD/CALB updates, with PMD removed. |
| 2006 | `y2006g` | Same as `y2006c`; includes SVT dead material. |
| 2006 | `y2006h` | Same as `y2006g`; includes the ECal v6 and TPC2009 updates. |
| 2005 | `y2005` | Baseline 2005 geometry: TPC + SVT + SSD + EMC + FPD. |
| 2005 | `y2005b` | Same as `y2005`; updated 2005 production geometry. |
| 2005 | `y2005f` | Same as `y2005`; dead-area SSD/CALB2 update and related detector modifications. |
| 2005 | `y2005g` | Same as `y2005f`; adds SVT dead material. |
| 2005 | `y2005h` | Same as `y2005g`; includes the TPC2009 update. |
| 2005 | `y2005i` | Same as `y2005h`; includes the ECAL v6 update. |
| 2004 | `y2004` | Baseline 2004 geometry: TPC + SVT + SSD + EMC + FPD. |
| 2004 | `y2004a` | Same as `y2004`; 2004 geometry tag for the production setup. |
| 2004 | `y2004c` | Same as `y2004`; AgML-based production geometry, with the final 2004 detector layout. |
| 2004 | `y2004y` | Same as `y2004`; a 2004 production alias in the standard detector stack. |
| 2003 | `y2003` | Baseline 2003 geometry: TPC + SVT + SSD + EMC. |
| 2003 | `y2003x` | Same as `y2003`; 2003 production variant with the standard detector configuration. |
| 2001 | `y2001` | Baseline 2001 geometry: TPC + SVT + EMC. |
| 2001 | `y2001n` | Same as `y2001`; alternate 2001 production alias for the same detector layout. |
| 2000 | `y1h` | Baseline operating geometry for the 2000 setup: TPC + SVT + EMC. |
| 2000 | `y2000` | Same as `y1h`; canonical year-2000 alias used in the STAR VMC configuration. |

The major pattern is consistent across the years: the baseline tag defines the detector stack for the year, and the `a`, `b`, `c`, ... suffixes describe minor production-alias or configuration variations (for example, alternate production releases, FXT options, fixed-target setups, MTD corrections, or TPC/ECAL geometry updates), while the `dev*` and `upgr*` families are intentionally left out because they are not the standard detector configurations.

## Forward tracking geometry aliases

The `StarGeo.xml` file also includes a separate family of forward-tracking aliases with the prefix `ft20...`, such as `ft2022c`, `ft2023c`, `ft2024c`, `ft2025b`, and `ft2026a`. These are not the standard production `y20xxy` tags; they are special tracking-oriented aliases that carry the same year-specific detector stack but explicitly select the forward-tracking variant of the FST geometry.  They also prune out the midrapidity detectors.  Only the forward trackers, forward calorimeters, beam pipe, support cone, epds and bbcs are included.  i.e. the tracking detectors and materials which forward tarcks may impinge upon.

In practice, these tags mirror the corresponding standard-year production configuration while keeping the forward branch distinct from the regular detector tags. The pattern is:

- `ft2022c` tracks the `y2022c` / `SCON15` detector stack with the forward-tracking geometry variant.
- `ft2023c` tracks the `y2023c` / `SCON15` detector stack with the forward-tracking geometry variant.
- `ft2024c` tracks the `y2024c` / `SCON15` detector stack with the forward-tracking geometry variant.
- `ft2025b` tracks the `y2025b` / `SCON15` detector stack with the forward-tracking geometry variant.
- `ft2026a` tracks the `y2026a` / `SCON15` detector stack with the forward-tracking geometry variant.

These aliases are used to separate the forward-tracking setup from the main production geometry labels, and they should be read as a special-purpose geometry family rather than as part of the standard yearly alias list.

