// $Id: StKFVertexMaker.h,v 2.5 2018/01/03 21:23:36 smirnovd Exp $

#ifndef STAR_StKFVertexMaker
#define STAR_StKFVertexMaker

/*!
 *                                                                     
 * \class  StKFVertexMaker
 * \author fisyak
 * \date   2012/04/18
 * \brief  virtual base class for Maker
 *
 */                                                                      

#ifndef StMaker_H
#include "StMaker.h"
#endif
#include <map>
using std::map;
#include "TObjArray.h"
#include "TSpectrum.h"
#include "Math/Functor.h"
#include "Math/GSLMinimizer1D.h"
#include "StEnumerations.h"
#include "TCanvas.h"
#include "THStack.h"
#include "KFParticle/KFParticle.h"
class StEvent;
class StVertex;
class StPrimaryVertex;
class StEvent;
class StGlobalTrack;
class StPrimaryTrack;
class StDcaGeometry;
class StTrack;
class StTrackNode;
class StKFVerticesCollection;
class StKFVertex;
class StKFTrack;
class StKFVertexMaker : public StMaker {
 public: 
  StKFVertexMaker(const Char_t *name="KFVertex");
  virtual                       ~StKFVertexMaker();						   		   
  KFParticle 	 	 	*AddBeamTrack();                                      		  		   
  KFParticle 	 	 	*AddTrackAt(const StDcaGeometry *dca,Int_t kg);	   	  		   
  KFParticle     	 	*AddTrackAt(const StGlobalTrack *gTrack);		   	  		   
  KFParticle 	 	 	*AddTrackAt(const KFParticle *particleO,Int_t kg);	   	  		   
  static Double_t	 	 AnnelingFcn(Double_t TInv=1);					  		   
  TCanvas        	 	*Canvas() {return fc1;}					  		   
  void           	 	 CalculateRank(StPrimaryVertex *primV);			  		   
  void                           SimpleMindedRank(StPrimaryVertex *primV);	
  void                           TMVARank(StPrimaryVertex *primV);
  void           	 	 Clear(Option_t *option="");					  		   
  virtual Int_t                  InitRun(Int_t runumber);
  void           	 	 Fit();							  		   
  virtual void                   ReFitToVertex();  
  virtual void                   ReFitToStVertex();  
  virtual StPrimaryTrack 	*FitTrack2Vertex(StKFVertex *V, StKFTrack* track, StPrimaryVertex *primV);
  virtual StPrimaryTrack 	*FitTrack2Vertex(const KFParticle &VKF, KFParticle& P, StPrimaryVertex *primV);
  TH1F           	 	*GetVertexZPlots(Int_t pass = 0) {return fVertexZPlots[pass];}	  		   
  virtual Int_t  	 	 Make();							  		   
  Int_t          	 	 MakeParticles();						  		   
  Bool_t                         FillVertex(const KFParticle *KVx, StVertex *V);
  void                   	 PrimaryVertices();	
  void                           ClearParentIDs();
  StKFVerticesCollection 	*PrimaryVertexSeeds(Int_t *parents);								   
  void                   	 SecondaryVertices();								   
  void                   	 SetCanvas(TCanvas *c1) {fc1 = c1;}						   
  void                   	 SetDefaultTempLog(Double_t tLog = 2) {fTempLog = tLog;}			   
  static void                    SetProbCut(Double_t prob) {fgProbCut = prob;}
  void                   	 SetZwindow(Double_t z = 2) {fzWindow = z;}					   
  TH1                       	*VertexZPlot() {return fVertexZPlot;}                                             
  void                           PrintParticles();
  void                           PrintPrimVertices();
#if !defined(__CINT__) && !defined(__CLING__)
  void                           ResetDaughterIds(KFParticle *particle, vector<KFParticle> &particles);
#endif
  static Int_t                   Key2(Int_t Id1, Int_t Id2) {return (Id1 > Id2) ? 1000000*Id1 + Id2 : 1000000*Id2 + Id1;}
 protected:
  TObjArray                     *fParticles; // KF particles = global tracks + decay particles
  TObjArray                     *fVertices;  // KF vertices and decay particles
  Int_t     			 fPass;    
  Int_t     			 fNzBins;  
  Int_t     			 fNPasses; 
  TSpectrum 			*fSpectrum;
  Double_t  			 fzWindow; 
  static StKFVerticesCollection *fgcVertices;  // current vertex collection
  Double_t                       fTempLog;
  ROOT::Math::GSLMinimizer1D    *fminBrent;
  ROOT::Math::Functor1D         *func;
  TH1F                          *fVertexZPlots[2];
  TH1                           *fVertexZPlot;
  THStack                       *fStack;
  Bool_t                         mBeamLine;
  KFParticle                     fKFPbeamLine;
  StPrimaryVertexOrder           mVertexOrderMethod; // will default to 0 i.e. orderByNumberOfDaughters
  TCanvas                       *fc1;
  StEvent                       *pEvent;
  Int_t                          fNGoodGlobals;
  Int_t                          fLastGlobalId;
  static Double_t                fgProbCut; // Cut for fits
  static map<Int_t,StTrackNode*> fTrackNodeMap;
  /// Displayed on session exit, leave it as-is please ...
  virtual const char *GetCVS() const {
    static const char cvs[]="Tag $Name:  $ $Id: StKFVertexMaker.h,v 2.5 2018/01/03 21:23:36 smirnovd Exp $ built " __DATE__ " " __TIME__ ; 
    return cvs;
  }

  ClassDef(StKFVertexMaker,0)   //StAF chain virtual base class for Makers
};
// $Log: StKFVertexMaker.h,v $
// Revision 2.5  2018/01/03 21:23:36  smirnovd
// StKFVertexMaker: Added missing include
//
// Revision 2.4  2014/08/06 11:43:59  jeromel
// Suffix on literals need to be space (later gcc compiler makes it an error) - first wave of fixes
//
// Revision 2.3  2013/04/10 22:14:20  fisyak
// Roll back to version 04/04/2013
//
// Revision 2.1  2012/05/07 14:56:14  fisyak
// Add StKFVertexMaker
//
#endif /* STAR_StKFVertexMaker */
