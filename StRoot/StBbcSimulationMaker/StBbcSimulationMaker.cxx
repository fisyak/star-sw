/*!
Created by <a href="http://www.star.bnl.gov/~kopytin> 
Mikhail Kopytine </a> on Aug 20, 2002.

Here are
<A HREF="http://www.star.bnl.gov/STAR/comp/pkg/dev/StRoot/St_TLA_Maker/README"> Victor Perevoztchikov's instructions on how to write an St***Maker </A>
 */
#ifdef __APPLE__
#include <sys/types.h>
#endif
#include "StBbcSimulationMaker.h"
#include "g2t/St_g2t_bbc_Module.h"
#include "tables/St_g2t_track_Table.h"
#include "tables/St_g2t_vertex_Table.h" 
#include "TDataSetIter.h"
#include "TRandom.h"
#include <vector>
#include "StEvent.h"
#include "StTriggerDetectorCollection.h"
#include "StBbcTriggerDetector.h"
#include "StMessMgr.h"

TRandom BbcRndm = TRandom(0);

ClassImp(StBbcSimulationMaker)

static const Float_t BbcTimingRMS = 900.E-12; /*! BBC timing resolution in seconds
for a single MIP according to the
<a href="http://connery.star.bnl.gov/protected/highpt/jacobs/BBC_proposal3.ps">
Proposal </a>.					*/



static const UShort_t NPMTsmall1 = 16;
static const UShort_t NPMTlarge1 = 8;
static const UShort_t NPMT1 = NPMTsmall1+NPMTlarge1;//# of PMTs on one side (East/West)
static const UShort_t NPMT2 = 2*NPMT1; // ditto on both sides
static const Float_t dE1MIPper_gcm2 = 1.95E-3;  // in GeV/(g/cm**2), for polystyrene
static const Float_t PolystereneDensity = 1.032;   // in g/cm**3
static const Float_t TyleThickness = 1.; // in cm
static const Float_t dE_1MIP = dE1MIPper_gcm2*PolystereneDensity*TyleThickness;
static const Float_t NPhotoelectrons_1MIP = 15.; 
static const Float_t pC_per_Photoelectron = 0.3;
static const Short_t NADCbins = 256; /* bins are numbered from 0 to 255 */
static const Short_t NTDCbins = 256; /* ditto */
static const Float_t pC_perADCbin = 0.25; /* Central trigger barrel 
				   Digitizer Boards (CDB) have such 
				   conversion gain (see STAR NIM) */
static const Float_t ADC0 = 0.;  /* beginning of ADC range */
static const Float_t s_perTDCbin = .1E-9; /* so that 25.6 ns is full range (guess) */
static const Float_t TDC0 = 0.;  /* beginning of TDC range */
static const Float_t OuterFactor = 0.8; /* larger scintillators of the outer ring
				  have less light output by this factor, 
				  compared with the inner ring, per
				  equal ionization */
static const Float_t SinglePhotoElectronResolution = 0.3; // according to Les Bland
/* Numbering: the real PMT numbering (used in the map) starts from 1.
ALL OTHERS start from 0 !
 */


// Note: BBC new factors are calibrated by 2017 p+p runs
const short ADCBin = 4096;

const float LightFactor[NPMT2] = {1., 1., 0.95, 0.92, 1., 1., 1., 1., 0.9, 0.96, 0.95, 1., 0.95, 0.97, 1., 1.,    // East small 
                                  0.33, 0.298, 0.25, 0.26, 0.22, 0.4, 0.24, 0.26,                                 // East large
                                  1.2, 0.9, 1., 0.6, 1., 1., 1.2, 1.2, 1.25, 0.4, 1., 1., 0.95, 0.95, 0.94, 0.95, // West small
                                  0., 0.243, 0., 0.2, 0.24, 0.18, 0.19, 0.2};                                     // West large

const float TileResolution[NPMT2] = {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, // East small
                                     0.6, 0.6, 0.4, 0.5, 0.5, 0.6, 0.4, 0.5,                                         // East large
                                     0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.5, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3, // West small
                                     0., 0.5, 0., 0.5, 0.6, 0.6, 0.4, 0.65};                                         // West large

const float pC_per_ADCBins[NPMT2] = {0.03, 0.03, 0.033, 0.033, 0.03, 0.03, 0.022, 0.03, 0.021, 0.022, 0.024, 0.03, 0.024, 0.024, 0.025, 0.027, // East small
                                     0.0226, 0.028, 0.021, 0.023, 0.014,  0.0125, 0.012, 0.0125,                                               // East large
                                     0.031, 0.03, 0.03, 0.018, 0.03, 0.03, 0.023, 0.024, 0.028, 0.005, 0.03, 0.03, 0.028, 0.023, 0.022, 0.028, // West small
                                     0., 0.027, 0., 0.06, 0.013, 0.014, 0.0129, 0.02};                                                         // West large

const int shift_ADC0[NPMT2] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   // East small
                               0, 0, 0, 0, -15, 0, -15, 0,                       // East large
                               0, 0, 0, 0, 0, 0, 0, 0, 0, -60, 0, 0, 0, 0, 0, 0, // West small
                               0, 0, 0, 0, -10, -7, -15, -10};                   // West large

//____________________________________________________________________________

bool IsSmall(Short_t iPMT)
{
  /// true for inner annulus (small tiles)
  if ( 0<=iPMT && iPMT<NPMTsmall1) return 1;
  if ( NPMT1<=iPMT && iPMT<NPMT1+NPMTsmall1) return 1;
  return 0;
}

/*------------------------------------------------------------------------*/
class BbcTOF 
{
  /*! This class is designed to be used exclusively by StBbcSimulationMaker
(hence no header). It keeps and increments all the information required and
in the end generates response based on that + noise.
*/
private:
   //  vector<float> Times;
  Float_t Times[NPMT2];
public: 
  //  BbcTOF():Times(vector<float>(NPMT2)){};  // NPMT1 !
  BbcTOF() {memset(Times, 0, sizeof(Times));}
  ~BbcTOF(){};
  void AddTOF(UShort_t ipmt, Float_t time)
  {
    /*! for the TOF, take the smallest one among the PMT's tiles; 
      add resolution error 
     */
    if (Times[ipmt]==0 || Times[ipmt]>time) {Times[ipmt]=time;}
  }
  Float_t GetTOF(UShort_t ipmt)  
  {
    /// returns TOF in s

    Float_t tof = 0;
    if (Times[ipmt]!=0.){ tof = Times[ipmt]+BbcRndm.Gaus(0.,BbcTimingRMS); }
    return tof;
  }
  Short_t GetTDC(UShort_t ipmt)
  { 
    /// returns digitized (TAC) TOF
    Float_t T = this->GetTOF(ipmt);

    if (T<TDC0) {return 0;}
    Short_t N = (short)((T-TDC0)/s_perTDCbin);
    if (N>=NTDCbins) {return NTDCbins-1;}
    return N;
  }

};
/*------------------------------------------------------------------------*/
class BbcDE
{
  /*! This class is designed to be used exclusively by StBbcSimulationMaker
(hence no header). It allows me to construct the energy measurement of a PMT 
by incrementing values of a vector; when that is finished, it returns 
the response based on that + noise.
   */
private:
  //  vector<float> dE;
  Float_t dE[NPMT2];
public:
  //  BbcDE():dE(vector<float>(NPMT2)){};
  BbcDE() {memset(dE, 0, sizeof(dE));}
  ~BbcDE(){};
  void AddDE(UShort_t ipmt, Float_t de)
  {
    de *= LightFactor[ipmt];
    dE[ipmt] += de;
  }
  Float_t GetDE(UShort_t ipmt)
  {
    /// returns DE in pC of PMT signal
    float PoissonMean = dE[ipmt]/dE_1MIP*NPhotoelectrons_1MIP;
    short NPhotoelectrons = BbcRndm.Poisson(PoissonMean);
    float Q = pC_per_Photoelectron*
      (1+BbcRndm.Gaus(0.,TileResolution[ipmt]))*NPhotoelectrons;
    return Q;
  }
  Short_t GetADC(UShort_t ipmt)
  {
    /// returns digitized (ADC) amplitude
    float A = this->GetDE(ipmt);
    short N = (short)(A/pC_per_ADCBins[ipmt] + shift_ADC0[ipmt]);
    if (N>=ADCBin) {return ADCBin-1;}
    if (N<0){return 0;}
    return N;
  }
};
//_____________________________________________________________________________
/// BbcSimulation constructor
/*!
  const char *name -  the name of this constructor
  The first comment lines after the opening bracket
  ({) of a member function are considered as a member function description 
  See <A HREF="http://root.cern.ch/root/Documentation.html"> ROOT HTML documentation </A>

 */
StBbcSimulationMaker::StBbcSimulationMaker(const char *name):StMaker(name)
{
  /*! See StBbcSimulationMaker.h and README for description of this class.
   */
}

//_____________________________________________________________________________
/// This is BbcSimulation destructor
/*!
  The first comment lines after the opening bracket
  ({) of a member function are considered as a member function description 
  
  The first comment lines after the opening bracket
  ({) of a member function are considered as a member function description 
  see: <A HREF="http://root.cern.ch/root/Documentation.html"> ROOT HTML documentation </A> 

 */
StBbcSimulationMaker::~StBbcSimulationMaker()
{
  //
}


//_____________________________________________________________________________
/// Init - is a first method the top level StChain calls to initialize all its makers 
Int_t StBbcSimulationMaker::Init()
{
  /*!
Associate volume ID with channel ID -- use map
MLK: GEANT numbering (set up by Yiqun, see bbcmgeo.g) is as follows:
* West is 1, East is 2;
* inner annulus (small tiles) is 1, outer is 2;
* triplet numbering is counterclockwise azimuthally, looking at the West 
detector along the z axis (i.e. from inside !!!) (East is rotated 180 deg.
arong the vertical axis.) 
(<a href="http://wwwinfo.cern.ch/asdoc/geant_html3/node83.html#GDRAWC">GDRAWC
</a> -- direction of view is along the axis.)
* withing a triplet, tile numbering is counterclockwise, looking at the West
detector along the z axis, and starting with the rightmost tile.

Les Bland: BBC scintillator tiles numbers are specified 
<a href="http://www.star.bnl.gov/STAR/html/bbc_l/geom/front_view.html">
here.
</a>
This shows a schematic of the BBC scintillator array from a vantage point 
that is outside (!!! MLK) of the STAR magnet. The same numbering scheme 
applies from appropriate vantage points for both the east and west sides of 
STAR.
  */
  //   BBC tile           BBC PMT number      Comments/description
  // --------           --------------      --------------------
  for (Short_t iew=1; iew<=2; iew++)
    {
      Short_t EW = iew*1000; // for VID
      //      Short_t EWshift = (iew-1)*NPMT1; if Akio numbered from West
      Short_t EWshift = (2-iew)*NPMT1; // for PMT
      /*!
PMT numbering: Akio Ogawa numbers channels in the data structure starting
 from East.
VID numbering: Yiqun followed STAR standard in the GSTAR code:
first West, then East.
       */
  //      1                    1              inner small hex tile, 12:00 pos'n 90 degrees
  Geant2PMT[EW+113] = EWshift+1;
  //      2                    2              inner small hex tile,  2:00 pos'n 30 degrees
  Geant2PMT[EW+123] = EWshift+2;
  //      3                    3              inner small hex tile,  4:00 pos'n -30 degrees
  Geant2PMT[EW+133] = EWshift+3;
  //      4                    4              inner small hex tile,  6:00 pos'n -90 degrees
  Geant2PMT[EW+143] = EWshift+4;
  //      5                    5              inner small hex tile,  8:00 pos'n -150 degrees
  Geant2PMT[EW+153] = EWshift+5;
  //      6                    6              inner small hex tile, 10:00 pos'n 150 degrees
  Geant2PMT[EW+163] = EWshift+6;
  //      7                    7              outer small hex tile, 11:00 pos'n 120 degrees
  Geant2PMT[EW+111] = EWshift+7;
  //      8                    8              outer small hex tile, 12:00 pos'n 90 degrees
  Geant2PMT[EW+112] = EWshift+8;
  //      9                    7              outer small hex tile,  1:00 pos'n 60 degrees
  Geant2PMT[EW+121] = EWshift+7;
  //     10                    9              outer small hex tile,  2:00 pos'n 30 degrees
  Geant2PMT[EW+122] = EWshift+9;
  //     11                   10              outer small hex tile,  3:00 pos'n 0 degrees
  Geant2PMT[EW+131] = EWshift+10;
  //     12                   11              outer small hex tile,  4:00 pos'n -30 degrees
  Geant2PMT[EW+132] = EWshift+11;
  //     13                   12              outer small hex tile,  5:00 pos'n -60 degrees
  Geant2PMT[EW+141] = EWshift+12;
  //     14                   13              outer small hex tile,  6:00 pos'n -90 degrees
  Geant2PMT[EW+142] = EWshift+13;
  //     15                   12              outer small hex tile,  7:00 pos'n -120 degrees
  Geant2PMT[EW+151] = EWshift+12;
  //     16                   14              outer small hex tile,  8:00 pos'n -150 degrees
  Geant2PMT[EW+152] = EWshift+14;
  //     17                   15              outer small hex tile,  9:00 pos'n 180 degrees
  Geant2PMT[EW+161] = EWshift+15;
  //     18                   16              outer small hex tile, 10:00 pos'n 150 degrees
  Geant2PMT[EW+162] = EWshift+16;

  //     19                   17              inner large hex tile, 12:00 pos'n 90 degrees
  Geant2PMT[EW+213] = EWshift+17;
  //     20                   18              inner large hex tile,  2:00 pos'n 30 degrees
  Geant2PMT[EW+223] = EWshift+18;
  //     21                   18              inner large hex tile,  4:00 pos'n -30 degrees
  Geant2PMT[EW+233] = EWshift+18;
  //     22                   19              inner large hex tile,  6:00 pos'n -90 degrees
  Geant2PMT[EW+243] = EWshift+19;
  //     23                   20              inner large hex tile,  8:00 pos'n -150 degrees
  Geant2PMT[EW+253] = EWshift+20;
  //     24                   20              inner large hex tile, 10:00 pos'n 150 degrees
  Geant2PMT[EW+263] = EWshift+20;
  //     25                   21              outer large hex tile, 11:00 pos'n 120 degrees
  Geant2PMT[EW+211] = EWshift+21;
  //     26                   21              outer large hex tile, 12:00 pos'n 90 degrees
  Geant2PMT[EW+212] = EWshift+21;
  //     27                   21              outer large hex tile,  1:00 pos'n 60 degrees
  Geant2PMT[EW+221] = EWshift+21;
  //     28                   22              outer large hex tile,  2:00 pos'n 30 degrees
  Geant2PMT[EW+222] = EWshift+22;
  //     29                   22              outer large hex tile,  3:00 pos'n 0 degrees
  Geant2PMT[EW+231] = EWshift+22;
  //     30                   22              outer large hex tile,  4:00 pos'n -30 degrees
  Geant2PMT[EW+232] = EWshift+22;
  //     31                   23              outer large hex tile,  5:00 pos'n -60 degrees
  Geant2PMT[EW+241] = EWshift+23;
  //     32                   23              outer large hex tile,  6:00 pos'n -90 degrees
  Geant2PMT[EW+242] = EWshift+23;
  //     33                   23              outer large hex tile,  7:00 pos'n -120 degrees
  Geant2PMT[EW+251] = EWshift+23;
  //     34                   24              outer large hex tile,  8:00 pos'n -150 degrees
  Geant2PMT[EW+252] = EWshift+24;
  //     35                   24              outer large hex tile,  9:00 pos'n 180 degrees
  Geant2PMT[EW+261] = EWshift+24;
  //     36                   24              outer large hex tile, 10:00 pos'n 150 degrees
  Geant2PMT[EW+262] = EWshift+24;
    }

  // Create Histograms    
#ifdef BbcSimQa
  QaFile = new TFile("StBbcSimQa.root","recreate");
  QaBbcPmtdE = new TH1F("QaBbcPmtdE","BBC PMT",NPMT2,-0.5,NPMT2-0.5);
  QaBbcPmtTime = new TH1F("QaBbcPmtTime","BBC PMT",NPMT2,-0.5,NPMT2-0.5);
  QaBbcEastVid = 
    new TH1F("QaBbcEastVid","BBC PMT with East VID",256,-0.5,255.5);
  QaBbcWestVid = 
    new TH1F("QaBbcWestVid","BBC PMT with West VID",256,-0.5,255.5);
  QaBbcEastPmt =
    new TH1F("QaBbcEastPmt","BBC PMT with East #", 256,-0.5,255.5);
  QaBbcWestPmt =
    new TH1F("QaBbcWestPmt","BBC PMT with West #", 256,-0.5,255.5);
  // create a test map, reverse w.r.t. Geant2PMT 
  typedef map<short,short>::const_iterator CI;

  for (CI I=Geant2PMT.begin(); I!=Geant2PMT.end(); ++I)
    {
      PMT2Geant[(*I).second] = (*I).first;
    }
#endif  

   return StMaker::Init();
}

//_____________________________________________________________________________
Int_t StBbcSimulationMaker::Make()
{
/// Make - this method is called in loop for each event

 TDataSet* ds= GetInputDS("geant");
 assert(ds);
 StEvent* event = (StEvent*)GetInputDS("StEvent");
 assert(event);
 St_g2t_ctf_hit* g2t_bbc_hit = (St_g2t_ctf_hit*) GetDataSet("geant/g2t_bbc_hit");
 if (g2t_bbc_hit) 
   {
     St_g2t_track *g2t_track = (St_g2t_track *) GetDataSet("geant/g2t_track"); //  if (!g2t_track)    return kStWarn;
     g2t_track_st *track = 0;
     Int_t NT = 0;
     if (g2t_track) {track = g2t_track->GetTable(); NT = g2t_track->GetNRows();}
     St_g2t_vertex  *g2t_ver = (St_g2t_vertex *) GetDataSet("geant/g2t_vertex");// if (!g2t_ver)      return kStWarn;
     g2t_vertex_st     *gver = 0;
     Int_t NV = 0;
     if (g2t_ver) {
       gver = g2t_ver->GetTable();
       NV = g2t_ver->GetNRows();
     }     
     Short_t nBBChits = g2t_bbc_hit->GetNRows();
     BbcTOF TOFdata;
     BbcDE DEdata;
     g2t_ctf_hit_st *bbc_hit = g2t_bbc_hit->GetTable();
     for (Short_t iBBChit=0; iBBChit<nBBChits; iBBChit++)
     {
       Int_t Id         = bbc_hit[iBBChit].track_p;
       Int_t id3 = 0;
       if (Id <= 0 || Id > NT) {
	 LOG_ERROR << "StBbcSimulationMaker::Make: g2t_bbc_hit table does not matched with g2t_track: track Id = " << Id << " and NT = " <<  NT << " skip the hit" << endm;
	 g2t_bbc_hit->Print(iBBChit,1);
	 continue;
       }
       if (track)  id3        = track[Id-1].start_vertex_p;
       if (id3 <= 0 || id3 > NV) {
	 LOG_ERROR << "StBbcSimulationMaker::Make: g2t_bbc_hit table does not matched with g2t_vertex: id3 = " << id3 << " and NV = " << NV << " skip the hit" << endm;
	 g2t_bbc_hit->Print(iBBChit,1);
	 if (Id > 0) g2t_track->Print(Id-1,1);
	 continue;
       }
       //       assert(id3 > 0 && id3 <= NV);
       Double_t tof = 0;
       if (gver) tof = gver[id3-1].ge_tof;
       //       if (TMath::Abs(tof) > 50e-9) continue; // 50 ns cut
       Float_t De = bbc_hit[iBBChit].de;
       Float_t TOF = tof + bbc_hit[iBBChit].tof;
       Short_t Vid =  bbc_hit[iBBChit].volume_id;

       Short_t PMTid = Geant2PMT[Vid];
       if (PMTid == 0) {
	 LOG_ERROR << "Cannot find a  PMTid in Geant2PMT for Vid = " << Vid << endm;
	 continue;
       }
       PMTid -= 1;
       DEdata.AddDE(PMTid,De);
       TOFdata.AddTOF(PMTid,TOF);
     }

     StTriggerDetectorCollection* myTrig =event->triggerDetectorCollection();
     if (!myTrig) {
       Warning("Make"," NoStTriggerDetectorCollection, Make the new one\n");
       myTrig = new StTriggerDetectorCollection;
       event->setTriggerDetectorCollection(myTrig);
     }
     StBbcTriggerDetector& myBbc = myTrig->bbc();


     for (UShort_t iPMT = 0; iPMT<NPMT2; iPMT++)
       {	  
	  Short_t ADC = DEdata.GetADC(iPMT);
#ifdef BbcSimQa
	  //	  QaBbcPmtAdc->Fill(iPMT,ADC);
	  Short_t Vid = PMT2Geant[iPMT+1];

	  if (Vid<2000) {QaBbcWestVid->Fill(ADC);}
	  if (Vid>2000) {QaBbcEastVid->Fill(ADC);}
	  if (iPMT<NPMT1) {QaBbcEastPmt->Fill(ADC);}
	  if (NPMT1<=iPMT && iPMT<NPMT2) {QaBbcWestPmt->Fill(ADC);}
	  QaBbcPmtTime->Fill(iPMT,TOFdata.GetTOF(iPMT));
	  QaBbcPmtdE->Fill(iPMT,DEdata.GetDE(iPMT));
#endif
	  myBbc.setAdc(iPMT, ADC);
	  if (IsSmall(iPMT))
	    {
	      Short_t TDC = TOFdata.GetTDC(iPMT);
	      myBbc.setTdc(iPMT, TDC);
	    }
	}
   }
else
  {
    gMessMgr->Info
      ("MLK StBbcSimulationMaker::Make() could not inst g2t_bbc_hit\n");
  }

 return kStOK;
}
///////////////////////////////////////////////////////////////////////
Int_t StBbcSimulationMaker::Finish()
{
  /// end of run
#ifdef BbcSimQa
  QaFile->Write();
  QaFile->Close();
#endif
  return StMaker::Finish();
}









