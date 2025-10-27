This folder contains three simple examples illustrating the two-dimensional version of the neBEM (nearly-exact Boundary Element Method) field solver implemented in the class `ComponentNeBem2d`. 

The first example (`triangle`) considers a right-angled triangle with an altitude of 1 cm. The hypothenuse is grounded and the legs are kept at a fixed potential of 1 V.
The exact numerical values for this configuration can be calculated using a series expansion (Chapter 5, Section 1.1.6 of Ref. 1) and are reproduced in the table below. 

| y [cm]      | Potential [V] |
| ----------- | ----------- |
| 0.1 | 0.165973895 |
| 0.2 | 0.326353080 |
| 0.3 | 0.476078222 |
| 0.4 | 0.611014157 |
| 0.5 | 0.728113328 |
| 0.6 | 0.825364529 |
| 0.7 | 0.901598676 |
| 0.8 | 0.956238103 |
| 0.9 | 0.989057910 |

The second example (`dielectric`) considers a dielectric slab between two parallel conducting plates. 

The third example (`wire`) calculates the potential of a wire inside a regular polygon.
 
## References
1. E. Durand, *Electrostatique. T.2: Problèmes géneraux; conducteurs*, Masson, 1966
