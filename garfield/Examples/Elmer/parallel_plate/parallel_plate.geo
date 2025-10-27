//----------------------------------------------------------------------
// parallel_plate.geo
// A parallel plate capacitor built from two gf_rectangle objects.
// ---------------------------------------------------------------------

// Create the counters.
n_physv = 1; // physical volumes
n_physs = 1; // physical surfaces
n_bdry = 0;  // number of boundary surfaces

// Include the components.
Include "gf_rectangle.geo";

// Create outer bounding box; first set parameters and then return values.
x0 = 0; y0 = 0; z0 = 0; lc = 1; l = 2; w = 2; h = 2;
sl = -1; s1 = -1; s2 = -1; s3 = -1; s4 = -1; s5 = -1; s6 = -1;
Call gf_rectangle;

// Create the inner box, the top and bottom of which will be assigned voltages.
x0 = 0; y0 = 0; z0 = 0; lc = 1; l = 1; w = 1; h = 1;
sl = -1; s1 = -1; s2 = -1; s3 = -1; s4 = -1; s5 = -1; s6 = -1;
Call gf_rectangle;

// Save the surface IDs for the top and bottom of the inner box and volume.
s_top_plate = s5;
s_bottom_plate = s6;
vol_inner = newv; Volume(vol_inner) = {sl};

// Create physical surfaces for the top and bottom plates.
physs_top_plate = n_physs; Physical Surface(physs_top_plate) = {s_top_plate}; n_physs += 1;
physs_bottom_plate = n_physs; Physical Surface(physs_bottom_plate) = {s_bottom_plate}; n_physs += 1;

// Create the bounding volume.
vol_bound = newv; Volume(vol_bound) = {bounds[]};

// Create the physical volumes.
physv_gas = n_physv; Physical Volume(physv_gas) = {vol_inner, vol_bound}; n_physv += 1;
physv_dielectric = n_physv; Physical Volume(physv_dielectric) = {vol_inner}; n_physv += 1;
