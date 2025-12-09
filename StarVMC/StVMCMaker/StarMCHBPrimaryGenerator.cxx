// $Id: StarMCHBPrimaryGenerator.cxx,v 1.1.1.1 2008/12/10 20:45:52 fisyak Exp $
#include "StarMCHBPrimaryGenerator.h"
#include "tables/St_particle_Table.h"
#include "TDatabasePDG.h"

ClassImp(StarMCHBPrimaryGenerator);
struct HepEvent_t {
  Int_t            itrac;
  particle_st          p;
};
//_____________________________________________________________________________
StarMCHBPrimaryGenerator::StarMCHBPrimaryGenerator(const Char_t *HbFile, TDataSet *Data) : 
  StarMCPrimaryGenerator(), fHBFileName(HbFile), fHBTree(0), fHBFile(0), 
  fEntry(-1), fnEntries(0), fHbtId(999), fData(Data) 
{
  fHBFile = new TFile(fHBFileName.Data());
  assert(fHBFile);
  cout << "StarMCHBPrimaryGenerator open " << fHBFileName << endl;
  if (Debug()) fHBFile->ls();
}
//_____________________________________________________________________________
void StarMCHBPrimaryGenerator::GeneratePrimary() {// generate primaries from HBOOK NTuple
  static HepEvent_t event;
  static Int_t   &itrac = *(&event.itrac);
  static Int_t   &ip    = *(&event.itrac);
  static Int_t   &istat = *(&event.p.isthep);
  static Int_t   &ipdg  = *(&event.p.idhep);
  static Int_t   &moth1 = *(&event.p.jmohep[0]);
  static Int_t   &moth2 = *(&event.p.jmohep[1]);
  static Int_t   &idau1 = *(&event.p.jdahep[0]);
  static Int_t   &idau2 = *(&event.p.jdahep[1]);
  static Float_t *Pxyz  =   &event.p.phep[0];
  static Float_t &ener  = *(&event.p.phep[3]);
  static Float_t &mass  = *(&event.p.phep[4]);
  static Float_t *Vxyz  =   &event.p.vhep[0];
  static Float_t &Vtime = *(&event.p.vhep[3]);
  static St_particle *particle = 0;
  static Double_t ct = TMath::Ccgs()/0.1; // mm s^-1
  Double_t polx = 0, poly = 0, polz = 0;
  // Add one primary particle to the user stack (derived from TVirtualMCStack).
  // Track ID (filled by stack)
  Int_t ntr;
  // Option: to be tracked
  Int_t toBeDone = 1; 
  if (! fHBTree) {
    fHBTree = (TTree*) fHBFile->Get(Form("h%i",fHbtId));
    assert(fHBTree);
    fHBTree->SetBranchAddress("itrac",&event.itrac);
    fHBTree->SetBranchAddress("istat",&event.p.isthep);
    fHBTree->SetBranchAddress("ipdg" ,&event.p.idhep);
    fHBTree->SetBranchAddress("moth1",&event.p.jmohep[0]);
    fHBTree->SetBranchAddress("moth2",&event.p.jmohep[1]);
    fHBTree->SetBranchAddress("idau1",&event.p.jdahep[0]);
    fHBTree->SetBranchAddress("idau2",&event.p.jdahep[1]);
    fHBTree->SetBranchAddress("Pxyz" ,&event.p.phep[0]);
    fHBTree->SetBranchAddress("ener" ,&event.p.phep[3]);
    fHBTree->SetBranchAddress("mass" ,&event.p.phep[4]);
    fHBTree->SetBranchAddress("Vxyz" ,&event.p.vhep[0]);
    fHBTree->SetBranchAddress("Vtime",&event.p.vhep[3]);
    fnEntries = fHBTree->GetEntriesFast();
    fEntry = 0;
  }
  if (fData) {
    particle = (St_particle *) fData->Find("particle");
    if (particle) SafeDelete(particle);
    particle = new St_particle("particle",100);
    fData->Add(particle);
  }
    
  Int_t nbytes = 0, nb = 0;
  if (Debug()) 
    printf("entry  trk ist   ipdg   m1    m2  d1   d2    Pxyz[3]                    "
	   " ener         mass      Vxyz[3]                       Vtime\n");
  Int_t NpHEP = 0;
  Int_t NPrim = 0;
  //  Int_t IdGen = 0;
  particle_st header;
  Int_t   *IdEvHep =   &header.jmohep[0];
  Float_t &Mass    = *(&header.phep[4]);
  Float_t *Hpar    =   &header.phep[0];
  Float_t *Comp    =   &header.vhep[0];
  header.isthep    = -1;
  for (; fEntry<fnEntries;fEntry++) {
    Long64_t ientry = fHBTree->LoadTree(fEntry);
    if (ientry < 0) break;
    nb = fHBTree->GetEntry(fEntry);   nbytes += nb;
    if (Debug()) {
#if 0
      printf("%5i%5i%4i%7i%5i%5i%5i%5i",
	     (int) ientry, event.itrac, event.p.isthep, event.p.idhep, 
	     event.p.jmohep[0],event.p.jmohep[1], 
	     event.p.jdahep[0],event.p.jdahep[1]);
      printf("%10.3f%10.3f%10.3f%10.3f%10.3f%10.3f%10.3f%10.3f%10.3f\n",
	     event.p.phep[0], event.p.phep[1], event.p.phep[2], event.p.phep[3], event.p.phep[4], 
	     event.p.vhep[0], event.p.vhep[1], event.p.vhep[2], event.p.vhep[3]);	     
#endif
      printf("%5i%5i%4i%7i%5i%5i%5i%5i",
	     (int) ientry, itrac, istat, ipdg, 
	     moth1,moth2, 
	     idau1,idau2);
      printf("%10.3f%10.3f%10.3f%10.3f%10.3f%10.3f%10.3f%10.3f%10.3f\n",
	     Pxyz[0], Pxyz[1], Pxyz[2], ener, mass, 
	     Vxyz[0], Vxyz[1], Vxyz[2], Vtime);	     
    }
    if (istat >= 10) {
      if (ipdg > 999990) {
	if (ipdg == 999999) {
	  for (Int_t i = 0; i < 4; i++) {IdEvHep[i] = (int) Pxyz[i]; Mass = Pxyz[4];}
	  NpHEP=ip;
	} else {
	  if ( ipdg == 999998) {for (Int_t i = 0; i < 4; i++) Hpar[i] = Pxyz[i];}
	  else {
	    if ( ipdg== 999997)  {for (Int_t i = 0; i < 4; i++) Comp[i] = Pxyz[i];}
	  }
	}
	header.isthep = istat;
	header.idhep  = ipdg;
      }
    } else {
      if (! NPrim && header.isthep > 0) particle->AddAt(&header);
      if (particle) {particle->AddAt(&event.p.isthep); /* IdGen = particle->GetNRows(); */}
      if ( TDatabasePDG::Instance()->GetParticle(event.p.idhep)) {
	// Add particle to stack 
	Int_t parent = event.p.jmohep[0] - 1;
	toBeDone = 1;
	if (event.p.isthep >= 2 || event.p.jdahep[0] || event.p.jdahep[1]) toBeDone = 0;
	fStarStack->PushTrack(toBeDone, parent, event.p.idhep, 
				event.p.phep[0], event.p.phep[1], 
				event.p.phep[2], event.p.phep[3],// px, py, pz, e, 
				fCurOrigin.x()+event.p.vhep[0]/10, 
				fCurOrigin.y()+event.p.vhep[1]/10, 
				fCurOrigin.z()+event.p.vhep[2]/10, 
				event.p.vhep[3]/ct,//vx, vy, vz, tof, (mm->cm) 
				polx, poly, polz, 
				kPPrimary, ntr, 1., 2); // mech, &ntr, weight, status
      } else {
	if (Debug())
	  cout << "StarMCHBPrimaryGenerator::GeneratePrimaries\t" << event.p.idhep << " is not in TDatabasePDG. skip it." << endl;
      }
      NPrim++;
      if (event.itrac == -1 || event.itrac == 65535 || NPrim == NpHEP) {fEntry++; break;}
    }
  }
  Int_t NPrimary = fStarStack->GetNtrack();
  fStarStack->SetNprimaries(NPrimary);
}
