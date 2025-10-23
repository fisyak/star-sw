// Create a 2D wire geometry
s = 10;  // side length of enclosing region
r = 1;   // radius of wire

lcBoundary = 0.4;  // characteristic length near enclosing region
lcWire = 0.4;      // characteristic length near wire

// Create the bounding box.
pbox0 = newp; Point(pbox0) = {-s/2, s/2,  0, lcBoundary};
pbox1 = newp; Point(pbox1) = {s/2,  s/2,  0, lcBoundary};
pbox2 = newp; Point(pbox2) = {s/2,  -s/2, 0, lcBoundary};
pbox3 = newp; Point(pbox3) = {-s/2, -s/2, 0, lcBoundary};
lbox0 = newc; Line(lbox0)  = {pbox0, pbox1};
lbox1 = newc; Line(lbox1)  = {pbox1, pbox2};
lbox2 = newc; Line(lbox2)  = {pbox2, pbox3};
lbox3 = newc; Line(lbox3)  = {pbox3, pbox0};
llbox = newreg; Line Loop(llbox) = {lbox0, lbox1, lbox2, lbox3};

// Create the wire.
pcenter = newp; Point(pcenter) = {0,  0,  0, lcWire};
pwire0 = newp; Point(pwire0) = {r,  0,  0, lcWire};
pwire1 = newp; Point(pwire1) = {0,  -r, 0, lcWire};
pwire2 = newp; Point(pwire2) = {-r, 0,  0, lcWire};
pwire3 = newp; Point(pwire3) = {0,  r,  0, lcWire};
cwire0 = newc; Circle(cwire0) = {pwire0, pcenter, pwire1};
cwire1 = newc; Circle(cwire1) = {pwire1, pcenter, pwire2};
cwire2 = newc; Circle(cwire2) = {pwire2, pcenter, pwire3};
cwire3 = newc; Circle(cwire3) = {pwire3, pcenter, pwire0};
llwire = newreg; Line Loop(llwire) = {cwire0, cwire1, cwire2, cwire3};

// Create the surfaces.
physcbox = newreg; Physical Curve(physcbox) = {lbox0, lbox1, lbox2, lbox3};
psbox  = newreg; Plane Surface(psbox) = {llbox, llwire};
physsbox = newreg; Physical Surface(physsbox) = {psbox};

physcwire = newreg; Physical Curve(physcwire) = {cwire0, cwire1, cwire2, cwire3};
pswire = newreg; Plane Surface(pswire) = {llwire};
physswire = newreg; Physical Surface(physswire) = {pswire};

//Mesh.Algorithm = 8;
Mesh.RecombinationAlgorithm = 2;
Mesh.ElementOrder = 2;
Mesh.SecondOrderIncomplete = 1;
Mesh.SubdivisionAlgorithm = 1;

Mesh 2;
RecombineMesh;
RefineMesh;
