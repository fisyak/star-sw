#include <math.h>
#include "Stiostream.h"
#include <string>
#include <map>
#include "TError.h"
#include "TVector3.h"
#include "StiMaterial.h"
#include "StiShape.h"
#include "StiPlanarShape.h"
#include "StiCylindricalShape.h"
#include "StiPlacement.h"
#include "StiDetectorContainer.h"
#include "StiDetector.h"
#include "Sti/StiToolkit.h"
#include "StiUtilities/StiDebug.h"
#include "StiMapUtilities.h"
#include "TMath.h"
#include "TString.h"
#include "TObjString.h"
#include "TGeoManager.h"
#include "TGeoMaterial.h"
#include "TGeoMedium.h"
int    StiDetector::mgIndex=0;
double StiDetector::mgValue[3]={0};


//______________________________________________________________________________
StiDetector::StiDetector()
{
  reset();
}
//______________________________________________________________________________
void StiDetector::reset()
{
  setName("");
  memset(mBeg,0,mEnd-mBeg+1);
  _key[0] = _key[1] = -1;
}

//______________________________________________________________________________
StiDetector::~StiDetector()
{}

//______________________________________________________________________________
void StiDetector::copy(StiDetector &detector){

  isActiveFunctor = detector.isActiveFunctor;

  gas = detector.getGas();
  material = detector.getMaterial();
  shape = detector.getShape();
  placement = detector.getPlacement();
  _cos  = detector._cos;
  _sin  = detector._sin;
  setName(detector.getName());
}
 
//______________________________________________________________________________
ostream& operator<<(ostream& os, const StiDetector& d) {
  Double_t xyzD[2] = {0};
  const StiShape *shape = d.getShape();
  const StiPlacement *place = d.getPlacement();
  if (shape->getShapeCode() == kPlanar) {
    xyzD[0] = place->getNormalRadius()*TMath::Cos(place->getNormalRefAngle());
    xyzD[1] = place->getNormalRadius()*TMath::Sin(place->getNormalRefAngle()) + place->getNormalYoffset();
  }
  os   << Form("%25s xy %7.2f %7.2f",d.getName().c_str(), xyzD[0], xyzD[1])
       << "\t" << *d.getPlacement()
       << "\t" << *d.getShape()
       << "\tMat:" << *d.getMaterial()
       << "\tGas:" << *d.getGas();
  return os;
}
//______________________________________________________________________________
void StiDetector::Print(const char *opt) const {
  TString Opt(opt);
  if (! Opt.Contains("TGeo",TString::kIgnoreCase)) {
    cout << *this << endl;
  } else {
//     Int_t imat = gGeoManager->GetListOfMaterials()->GetEntries();
//     Int_t imed = gGeoManager->GetListOfMedia()->GetEntries();
    Int_t indx = 0;
    cout << "//" << *this << endl;
    static TString Top, Vol, medname;
    static Int_t entry = 0;
    TString name(getName().c_str());
#if 0
    if (name.Contains("Tpc") || 
	name.Contains("TIFC") || 
	name.Contains("TOFC")	) return;
#endif
    TObjArray *obj = name.Tokenize("/");
    Int_t nParsed = obj->GetEntries();
    TString top = ((TObjString *) obj->At(0))->GetName();
    if (top.Contains("_")) {
      indx = top.Index("_");
      top = TString(top,indx);
    }
    if (top != Top) {
      Top = top;
      cout << "  TGeoVolumeAssembly *" << Top.Data() << " = new TGeoVolumeAssembly(\"" << Top.Data() << "\");" << endl;
      cout << "  CAVE->AddNode(" << Top.Data() << ",1,gGeoIdentity);" << endl;
    }
    TString vol = ((TObjString *) obj->At(nParsed-1))->GetName();
    if (vol.Contains("_")) {
      indx = vol.Index("_");
      vol = TString(vol,indx);
    }
    if (vol != Vol) {
      Vol = vol;
      entry = 0;
      // TGeoVolumeMulti *TPAD = gGeoManager->MakeVolumeMulti("TPAD", GetMed("TPCE_SENSITIVE_GAS")); TPAD->SetTitle("TPAD");
      medname = TString(getMaterial()->getName().c_str());
      cout << "  med = gGeoManager->GetMedium(\"" << medname.Data() << "\");" << endl;
      cout << "  if (! med) {" << endl;
      cout << "    imat = gGeoManager->GetListOfMaterials()->GetEntries();" << endl;
      cout << "    imed = gGeoManager->GetListOfMedia()->GetEntries();" << endl;
      cout << "     mat = new TGeoMaterial(\"" << medname.Data() << "\","
	   << getMaterial()->getA() << "," << getMaterial()->getZ()<< "," << getMaterial()->getDensity() << "," 
	   << getMaterial()->getX0() << "); mat->SetUniqueID(imat);" << endl;
      //	   << getMaterial()->getX0() << "); mat->SetUniqueID(" << imat << ");" << endl;
      cout << "     med = new TGeoMedium(\"" << medname.Data() << "\",0, imat" // gGeoManager->GetMaterial(\"" << medname.Data() << "\")->GetUniqueID()"
	   << ",0,0,20,20,10,0.2488534,0.1000000E-01,1.15055); "
	//	   << ",0); "
	   << "med->SetUniqueID(imed);" << endl;
      //	   << "med->SetUniqueID(" << imed << ");" << endl;

      cout << "  }" << endl;
      cout << "  TGeoVolumeMulti *" << Vol.Data() << " = gGeoManager->MakeVolumeMulti(\"" << Vol.Data() << "\", GetMed(\"" << medname.Data() << "\")); " 
	   << Vol.Data() << "->SetTitle(\"" << Vol.Data() << "\");" << endl;
      //      cout << "  " << Top.Data() << "->AddNodeOverlap(" << Vol.Data() << ",1,gGeoIdentity);" << endl;
      //      cout << "  " << Top.Data() << "->AddNode(" << Vol.Data() << ",1,gGeoIdentity);" << endl;
    } else {
      entry++;
    }
    /*
      TPAD->AddVolume(gGeoManager->MakeBox("TPAD",GetMed("TPCE_SENSITIVE_GAS"),0.8999996,13,104.8516));
      TPAD->SetLineColor(2);
      TPAD->AddVolume(gGeoManager->MakeBox("TPAD",GetMed("TPCE_SENSITIVE_GAS"),0.8,13,104.8516));
      TPAD->AddVolume(gGeoManager->MakeBox("TPAD",GetMed("TPCE_SENSITIVE_GAS"),0.8,13.5,104.8516));
      ...
      TPSS->AddNode(TPAD->GetVolume(0),1,new TGeoTranslation(54.1,0,-0.1414948));
      TPSS->AddNode(TPAD->GetVolume(1),2,new TGeoTranslation(55.8,0,-0.1414948));
      ...
    */
    const StiShape *shape = getShape();
    switch (shape->getShapeCode()) {
    case kPlanar:
      cout << "  " <<  Vol.Data() << "->AddVolume(gGeoManager->MakeBox(\"" << Vol.Data() << "\", gGeoManager->GetMedium(\"" << medname.Data() << "\")";
      cout << "," << shape->getHalfWidth() 
	   << "," << shape->getThickness()/2
	   << "," << shape->getHalfDepth();
      break;
    case kCylindrical:
      if (shape->getOpeningAngle() < (TMath::TwoPi()-0.001) ) {
	cout << "  " <<  Vol.Data() << "->AddVolume(gGeoManager->MakeTubs(\"" << Vol.Data() << "\", gGeoManager->GetMedium(\"" << medname.Data() << "\")";
	cout << "," <<  shape->getOuterRadius() - shape->getThickness() // rmin
	     << "," <<  shape->getOuterRadius()                         // rmax
	     << "," <<  shape->getHalfDepth()                           // Dz
	     << "," << -shape->getOpeningAngle()*TMath::RadToDeg()/2
	     << "," << +shape->getOpeningAngle()*TMath::RadToDeg()/2;
      } else {
	cout << "  " <<  Vol.Data() << "->AddVolume(gGeoManager->MakeTube(\"" << Vol.Data() << "\", gGeoManager->GetMedium(\"" << medname.Data() << "\")";
	cout << "," <<  shape->getOuterRadius() - shape->getThickness() // rmin
	     << "," <<  shape->getOuterRadius()                         // rmax
	     << "," <<  shape->getHalfDepth();                          // Dz
      }
      break;
    default: assert(0);
    }
    cout <<  "));" << endl;
    const StiPlacement *place = getPlacement();
    Double_t xyzD[3] = {0};
    if (shape->getShapeCode() == kPlanar) {
      xyzD[0] = place->getNormalRadius()*TMath::Cos(place->getNormalRefAngle());
      xyzD[1] = place->getNormalRadius()*TMath::Sin(place->getNormalRefAngle()) + place->getNormalYoffset();
    }
    xyzD[2] = place->getZcenter();
    if (TMath::Abs(place->getNormalRefAngle()) < 1e-7) {
      cout << "  " << Top.Data() << "->AddNode(" << Vol.Data() << "->GetVolume(" << entry << ")," << entry+1
	   << ", new TGeoTranslation(" 
	   <<         xyzD[0] // place->getNormalYoffset()
	   << ", " << xyzD[1] // place->getNormalRadius()
	   << ", " << xyzD[2] //place->getZcenter()
	   << "));" << endl;
    } else {
      cout << "  rot = new TGeoRotation(\"next\"); rot->RotateZ(" << TMath::RadToDeg()*place->getNormalRefAngle() << ");" << endl;
      cout << "  " << Top.Data() << "->AddNode(" << Vol.Data() << "->GetVolume(" << entry << ")," << entry+1
	   << ", new TGeoCombiTrans(" 
	   <<          xyzD[0] //place->getNormalYoffset()
	   <<  ", " << xyzD[1] //", " << place->getNormalRadius()
	   <<  ", " << xyzD[2] //", " << place->getZcenter()
	   << ", rot));" << endl;
    }
  }
}
//______________________________________________________________________________
int StiDetector::splitIt(StiDetVect &vect,double dXdY,int nMax)
{
static int nCall=0; nCall++;


  vect.resize(1);
  vect[0]=this;
  assert(shape);
  int iShape = shape->getShapeCode();
  float deltaX = shape->getThickness();
  float halfZ  = shape->getHalfDepth(); 
  float nRadius = placement->getNormalRadius();
  if (iShape >= kCylindrical)  nRadius = shape->getOuterRadius()-deltaX/2;

  if (nRadius < deltaX/2) {		// non splitable
    printf("StiDetector::splitIt %s Non splitable Rnormal < thickness/2 %g %g\n"
          ,getName().c_str(),nRadius,deltaX/2);
    return 1;
  }
  int nSplit = deltaX/dXdY + 0.5;
  if (nSplit<=1) return 1;
  if (nSplit>nMax) nSplit=nMax;

//		OK, we mast split it.

   vect.clear();
   float dX = deltaX/nSplit;
   double sumWeight = 0;
   for (int iSplit=0; iSplit<nSplit; iSplit++) 
   {
     float xc = -deltaX/2 +dX/2+iSplit*dX;  
//		Create small part of  detector
     StiDetector *det = StiToolkit::instance()->getDetectorFactory()->getInstance();
     det->copy(*this);
     TString ts(getName());
     if (iSplit) { ts+="_"; ts+=iSplit;} 
     det->setName(ts.Data());
//		Create shape
     ts = shape->getName();
     if (iSplit) { ts+="_"; ts+=iSplit;} 
     StiShape *myShape =0;
     float myRadius = nRadius+xc;
assert(myRadius>1e-2 && myRadius < 1e3);
     if (iShape==kPlanar) 	{//Planar shape
       Float_t halfY = shape->getHalfWidth();
       myShape = new StiPlanarShape(ts.Data(),halfZ,dX,halfY);

     } else if (iShape>=kCylindrical) {//Cylinder shape
       float angle  = shape->getOpeningAngle(); 
       myShape = new StiCylindricalShape(ts.Data(),halfZ,dX,myRadius+dX/2,angle);

     } else { assert(0 && "Wrong shape type");}

//		Create placement
     StiPlacement *place = new StiPlacement;
     *place = *placement;
     place->setNormalRep(placement->getNormalRefAngle(),myRadius,placement->getNormalYoffset());
     det->setShape(myShape);
     place->setLayerRadius(myRadius);
     det->setPlacement(place);
     sumWeight += det->getWeight();
     vect.push_back(det);
   }
   this->copy(*vect[0]); 
   this->setName(vect[0]->getName());
//   delete vect[0];
    StiToolkit::instance()->getDetectorFactory()->free(vect[0]);
    vect[0] = this;
//    if (vect.size()>1) {
//      printf("StiDetector::splitIt %s is splitted into %d peaces\n",getName().c_str(),vect.size());}
//    assert(fabs(startWeight-sumWeight)<1e-3*startWeight);


   return vect.size();
}
//______________________________________________________________________________
double StiDetector::getVolume() const
{
return shape->getVolume();
}
//______________________________________________________________________________
    double StiDetector::getWeight() const
{
return shape->getVolume()*material->getDensity();
}
//______________________________________________________________________________
int StiDetector::insideL(const double xl[3],int mode,double fakt) const 
{
double rN = placement->getNormalRadius();
double myErr = rN*(fakt-1);
if (myErr<0.1) myErr = 0.1;
if (myErr>10.) myErr = 10.;
double thick = shape->getThickness();
do {
 if (shape->getShapeCode()==1) { //Planar
   if (mode&1) { 
     mgIndex = 1;
     mgValue[1] = thick/2*fakt;
     mgValue[0] = fabs(xl[0]-rN)-mgValue[1]-myErr;
     if (mgValue[0]>0) break;
   }
   if (mode&2) {
     mgIndex = 2;
     double y = xl[1]-placement->getNormalYoffset();
     mgValue[1] = shape->getHalfWidth()*fakt;
     mgValue[0]  = fabs(y)-mgValue[1]-myErr;
     if (mgValue[0]>0) break;
   }
 } else {
   if (mode&1) {
     mgIndex = 1;
     mgValue[1] = thick/2*fakt;
     double rxy = sqrt(xl[0]*xl[0]+xl[1]*xl[1]);
     mgValue[0] = (fabs(rxy-rN)-mgValue[1]-myErr);
     if (mgValue[0]>0) break;
   }

   if (mode&2) {
     mgIndex = 2;
     double ang = atan2(xl[1],xl[0]);
     if (ang<-M_PI) ang +=M_PI*2;
     if (ang> M_PI) ang -=M_PI*2;
     mgValue[1] = shape->getOpeningAngle()/2 *fakt;
     mgValue[0] = (fabs(ang)-mgValue[1]-myErr/rN);
     if (mgValue[0]>0)	break;
   }
 } 
   if (mode&4) {
     mgIndex = 3;
     mgValue[1] = shape->getHalfDepth()*fakt;
     double z = xl[2]-placement->getZcenter();  
     mgValue[0] = (fabs(z)-mgValue[1]-myErr);
     if (mgValue[0]>0)	break;
   }
   mgIndex = 0;
   return 1;
 } while(0);
 static Int_t noError = 0;
 if (noError < 13) {
   noError++;
  ::Error("StiDetector::insideL","Det=%s XYZ=(%g %g %g)"
         ,getName().c_str(),xl[0],xl[1],xl[2]);
  ::Error("StiDetector::insideL","idx=%d val=%g %g"
         ,mgIndex,mgValue[0],mgValue[1]);
 }
  return 0;
}
//______________________________________________________________________________

/**
 * A setter for most of the detector properties. We do not pass arguments in
 * a constructor because StiDetector-s are normally created by an StiFactory.
 *
 * \author Dmitri Smirnov, BNL
 */
void StiDetector::setProperties(std::string name, StiIsActiveFunctor* activeFunctor,
   StiShape* shape, StiPlacement* placement, StiMaterial* gas, StiMaterial* material)
{
   setName(name.c_str());
   setIsActive(activeFunctor);
   setShape(shape);
   setPlacement(placement);
   setGas(gas);
   setMaterial(material);
}
//______________________________________________________________________________
int StiDetector::insideG(const double xl[3],int mode,double fakt) const 
{
  TVector3 xg(xl);
  double alfa = getPlacement()->getNormalRefAngle();
  xg.RotateZ(-alfa);
  return insideL(&xg[0],mode,fakt);
}
//______________________________________________________________________________
void StiDetector::getDetPlane(double plane[4]) const 
{
  plane[0] = - getPlacement()->getNormalRadius();
  plane[1] = _cos;
  plane[2] = _sin;
  plane[3] = 0.;
}
