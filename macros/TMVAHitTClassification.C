#if defined(__CLING__)
#define __ROOT6__
#else /* ! __CLING__ */
#if ROOT_VERSION_MAJOR >= 6
#define __ROOT6__
#else /* ! ROOT_VERSION_MAJOR >= 6 */
#endif /* ROOT_VERSION_MAJOR >= 6 */
#endif /* __CLING__ */
#ifdef __ROOT6__
/// from original  /cvmfs/star.sdcc.bnl.gov/TFG/star/ROOT/5.34.39/root/tmva/test/TMVAClassification.C
///                                                                              /
/// (note that the backslashes are mandatory)                                     
/// If no method given, a default set of classifiers is used.                     
///                                                                               
/// The output file "TMVA.root" can be analysed with the use of dedicated         
/// macros (simply say: root -l <macro.C>), which can be conveniently             
/// invoked through a GUI that will appear at the end of the run of this macro.   
/// Launch the GUI via the command:                                               
///                                                                               
///    root.exe  'Chain.C+("../*.root","HitT")' 'TMVAHitTClassification.C+("O")'  
///    root.exe  ./TMVAGui.C                                                      
///                                                                               
#else /* __ROOT6__ */
/// from original $ROOTSYS/tutorials/machine_learning/TMVAClassification.C
/// 
/// As input data is used TPC clusters with flag=2 (deconvoluted)
/// Goal is to find optimum cut to merge cluster. Creteia is IdTruth.
///
///     root  'Chain.C+("../*.root","HitT")' 'TMVAHitTClassification.C+("I")'
///
#endif /* __ROOT6__ */
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include "TInterpreter.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TObjArray.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TTreeIter.h"
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#ifdef __ROOT6__
#include "TMVA/DataLoader.h"
#include "TMVA/TMVAGui.h"
#endif /*  __ROOT6__ */
#include "TMath.h"
#include "TH1.h"
#include "TH2.h"
int TMVAHitTClassification( TString Opt = "I", TString myMethodList = "" )
{
   // The explicit loading of the shared libTMVA is done in TMVAlogon.C, defined in .rootrc
   // if you use your private .rootrc, or run from a different directory, please copy the
   // corresponding lines from .rootrc


   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();

#if ROOT_VERSION_MAJOR < 6
   // to get access to the GUI and all tmva macros
   TString thisdir = gSystem->DirName(gInterpreter->GetCurrentMacroName());
   gROOT->SetMacroPath(thisdir + ":" + gROOT->GetMacroPath());
   gROOT->ProcessLine(".L TMVAGui.C");

#endif /* ! __ROOT6__ */
   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

   // Cut optimisation
   Use["Cuts"]            = 0; // 1;
   Use["CutsD"]           = 0; // 1;
   Use["CutsPCA"]         = 0;
   Use["CutsGA"]          = 0;
   Use["CutsSA"]          = 0;
   //
   // 1-dimensional likelihood ("naive Bayes estimator")
   Use["Likelihood"]      = 0; // 1;
   Use["LikelihoodD"]     = 0; // the "D" extension indicates decorrelated input variables (see option strings)
   Use["LikelihoodPCA"]   = 0; // 1; // the "PCA" extension indicates PCA-transformed input variables (see option strings)
   Use["LikelihoodKDE"]   = 0;
   Use["LikelihoodMIX"]   = 0;
   //
   // Mutidimensional likelihood and Nearest-Neighbour methods
   Use["PDERS"]           = 0; // 1;
   Use["PDERSD"]          = 0;
   Use["PDERSPCA"]        = 0;
   Use["PDEFoam"]         = 0; // 1;
   Use["PDEFoamBoost"]    = 0; // uses generalised MVA method boosting
   Use["KNN"]             = 0; // 1; // k-nearest neighbour method
   //
   // Linear Discriminant Analysis
   Use["LD"]              = 0; // 1; // Linear Discriminant identical to Fisher
   Use["Fisher"]          = 0;
   Use["FisherG"]         = 0;
   Use["BoostedFisher"]   = 0; // uses generalised MVA method boosting
   Use["HMatrix"]         = 0;
   //
   // Function Discriminant analysis
   Use["FDA_GA"]          = 0; // 1; // minimisation of user-defined function using Genetics Algorithm
   Use["FDA_SA"]          = 0;
   Use["FDA_MC"]          = 0;
   Use["FDA_MT"]          = 0;
   Use["FDA_GAMT"]        = 0;
   Use["FDA_MCMT"]        = 0;
   //
   // Neural Networks (all are feed-forward Multilayer Perceptrons)
   Use["MLP"]             = 0; // Recommended ANN
   Use["MLPBFGS"]         = 0; // Recommended ANN with optional training method
   Use["MLPBNN"]          = 0; // 1; // Recommended ANN with BFGS training method and bayesian regulator
   Use["CFMlpANN"]        = 0; // Depreciated ANN from ALEPH
   Use["TMlpANN"]         = 0; // ROOT's own ANN

#ifdef R__HAS_TMVACPU
   Use["DNN_CPU"]         = 0; // 1; // Multi-core accelerated DNN.
#else
   Use["DNN_CPU"]         = 0;
#endif
   //
   // Support Vector Machine
   Use["SVM"]             = 0; // 1;
   //
   // Boosted Decision Trees
   Use["BDT"]             = 1; // uses Adaptive Boost
   Use["BDTG"]            = 0; // uses Gradient Boost
   Use["BDTB"]            = 0; // uses Bagging
   Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
   Use["BDTF"]            = 0; // allow usage of fisher discriminant for node splitting
   //
   // Friedman's RuleFit method, ie, an optimised series of cuts ("rules")
   Use["RuleFit"]         = 0; // 1;
   // ---------------------------------------------------------------

   std::cout << std::endl;
   std::cout << "==> Start TMVAHitTClassification" << std::endl;

   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);

         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
            std::cout << std::endl;
            return 1;
         }
         Use[regMethod] = 1;
      }
   }

   // --------------------------------------------------------------------------------------------------

   TTree *tree = (TTree *) gROOT->GetListOfSpecials()->FindObject("HitT");
   if (! tree) return 0;
   // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
   TString outfileName("TMVACHitTC");
   outfileName += Opt; outfileName += ".root";
#if ROOT_VERSION_MAJOR < 6
   TFile *outputFile = TFile::Open(outfileName, "RECREATE");
#else /* __ROOT6__ */
   std::unique_ptr<TFile> outputFile{TFile::Open(outfileName, "RECREATE")};
#endif /* !__ROOT6__ */
   if (!outputFile || outputFile->IsZombie()) {
      throw std::runtime_error("ERROR: could not open output file");
   }
   // Book QA histograms
   gDirectory->mkdir("QA");
   gDirectory->cd("QA");
   TH2F *Ov[2] = {
     new TH2F("OvS","Signal ; time Overlap ; pad Overlap", 41, -35.5, 5.5, 29, -24.5, 4.5),
     new TH2F("OvB","Background ; time Overlap ; pad Overlap", 41, -35.5, 5.5, 29, -24.5, 4.5)
   };
   TH2F *dPT[2] = {
     new TH2F("dPTS","Signal ; dtime bucket ; dpad", 105, -15.5, 5.5, 100, -14.5, 5.5),
     new TH2F("dPTB","Background ; dtime bucket ; dpad", 105, -15.5, 5.5, 100, -14.5, 5.5)
   };
   TH2F *AdcL[2] = {
     new TH2F("AdcLS","Signal ; log(AdcK) ; log(AdcL)", 60, 3.5, 9.5, 60, 3.5, 9.5),
     new TH2F("AdcLB","Background ; log(AdcK) ; log(AdcL)", 60, 3.5, 9.5, 60, 3.5, 9.5)
   };
   TH1D *AdcLD[2] = {
     new TH1D("AdcLDS","Signal ; log(AdcK) - log(AdcL)", 200, -10.0, 10.0),
     new TH1D("AdcLDB","Background ; log(AdcK) - log(AdcL)", 200, -10.0, 10.0)
   };
   TH2F *dPTC[2] = {
     new TH2F("dPTCS","Signal after cut; dtime bucket ; dpad", 105, -15.5, 5.5, 100, -14.5, 5.5),
     new TH2F("dPTCB","Background after cut ; dtime bucket ; dpad", 105, -15.5, 5.5, 100, -14.5, 5.5)
   };
   TH2F *AdcLC[2] = {
     new TH2F("AdcLCS","Signal  after cut; log(AdcK) ; log(AdcL)", 60, 3.5, 9.5, 60, 3.5, 9.5),
     new TH2F("AdcLCB","Background  after cut; log(AdcK) ; log(AdcL)", 60, 3.5, 9.5, 60, 3.5, 9.5)
   };
   TH1D *AdcLDC[2] = {
     new TH1D("AdcLDCS","Signal  after cut; log(AdcK) - log(AdcL)", 200, -10.0, 10.0),
     new TH1D("AdcLDCB","Background  after cut; log(AdcK) - log(AdcL)", 200, -10.0, 10.0)
   };
   // Create the factory object. Later you can choose the methods
   // whose performance you'd like to investigate. The factory is
   // the only TMVA object you have to interact with
   //
   // The first argument is the base of the name of all the
   // weightfiles in the directory weight/
   //
   // The second argument is the output file for the training results
   // All TMVA output can be suppressed by removing the "!" (not) in
   // front of the "Silent" argument in the option string
#if ROOT_VERSION_MAJOR < 6
   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
   auto *dataloader = factory;
#else /* __ROOT6__ */
   auto factory = std::make_unique<TMVA::Factory>(
      "TMVAHitTClassification", outputFile.get(),
      "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification");
   auto dataloader_raii = std::make_unique<TMVA::DataLoader>("dataset");
   auto *dataloader = dataloader_raii.get();
#endif /* __ROOT6__ */
   // If you wish to modify default settings
   // (please check "src/Config.h" to see all available global options)
   //
   //    (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
   //    (TMVA::gConfig().GetIONames()).fWeightFileDir = "myWeightDirectory";

//    static const Char_t *vTpcHitMRPair ="sec:row:"
//      "qK:padK:tbkK:padKmn:padKmx:tbkKmn:tbkKmx:IdTK:QAK:flagK:zK:adcK:"
//      "qL:padL:tbkL:padLmn:padLmx:tbkLmn:tbkLmx:IdTL:QAL:flagL:zL:adcL:"
//      "padOv:tbkOv";
   TTreeIter iter(tree);
   UInt_t NVars = 0;
// dataloader->AddSpectator( "sec"   ,  "sec"    , "units", 'F' ); NVars++; static const Float_t&     sec                                      = iter("sec");   
   dataloader->AddSpectator( "row"   ,  "row"    , "units", 'F' ); NVars++; static const Float_t&     row                                      = iter("row");   
// dataloader->AddSpectator( "qK"    ,  "qK"     , "units", 'F' ); NVars++; static const Float_t&     qK                                       = iter("qK");    
   dataloader->AddSpectator( "padK"  ,  "padK"   , "units", 'F' ); NVars++; static const Float_t&     padK                                     = iter("padK");  
   dataloader->AddSpectator( "tbkK"  ,  "tbkK"   , "units", 'F' ); NVars++; static const Float_t&     tbkK                                     = iter("tbkK");  
// dataloader->AddSpectator( "padKmn",  "padKmn" , "units", 'F' ); NVars++; static const Float_t&     padKmn                                   = iter("padKmn");
// dataloader->AddSpectator( "padKmx",  "padKmx" , "units", 'F' ); NVars++; static const Float_t&     padKmx                                   = iter("padKmx");
// dataloader->AddSpectator( "tbkKmn",  "tbkKmn" , "units", 'F' ); NVars++; static const Float_t&     tbkKmn                                   = iter("tbkKmn");
// dataloader->AddSpectator( "tbkKmx",  "tbkKmx" , "units", 'F' ); NVars++;  static const Float_t&     tbkKmx                                   = iter("tbkKmx");
/* dataloader->AddSpectator( "IdTK"  ,  "IdTK"   , "units", 'F' ); NVars++; */ static const Float_t&     IdTK                                     = iter("IdTK");  
/* dataloader->AddSpectator( "QAK"   ,  "QAK"    , "units", 'F' ); NVars++; */ static const Float_t&     QAK                                      = iter("QAK");   
/* dataloader->AddSpectator( "flagK" ,  "flagK"  , "units", 'F' ); NVars++; */ static const Float_t&     flagK                                    = iter("flagK"); 
   dataloader->AddSpectator( "zK"    ,  "zK"     , "units", 'F' ); NVars++; static const Float_t&     zK                                       = iter("zK");    
   dataloader->AddSpectator( "adcK"  ,  "adcK"   , "units", 'F' ); NVars++; static const Float_t&     adcK                                     = iter("adcK");  
// dataloader->AddSpectator( "qL"    ,  "qL"     , "units", 'F' ); NVars++; static const Float_t&     qL                                       = iter("qL");    
   dataloader->AddSpectator( "padL"  ,  "padL"   , "units", 'F' ); NVars++; static const Float_t&     padL                                     = iter("padL");  
   dataloader->AddSpectator( "tbkL"  ,  "tbkL"   , "units", 'F' ); NVars++; static const Float_t&     tbkL                                     = iter("tbkL");  
// dataloader->AddSpectator( "padLmn",  "padLmn" , "units", 'F' ); NVars++; static const Float_t&     padLmn                                   = iter("padLmn");
// dataloader->AddSpectator( "padLmx",  "padLmx" , "units", 'F' ); NVars++; static const Float_t&     padLmx                                   = iter("padLmx");
// dataloader->AddSpectator( "tbkLmn",  "tbkLmn" , "units", 'F' ); NVars++; static const Float_t&     tbkLmn                                   = iter("tbkLmn");
// dataloader->AddSpectator( "tbkLmx",  "tbkLmx" , "units", 'F' ); NVars++; static const Float_t&     tbkLmx                                   = iter("tbkLmx");
/* dataloader->AddSpectator( "IdTL"  ,  "IdTL"   , "units", 'F' ); NVars++; */ static const Float_t&     IdTL                                     = iter("IdTL");  
/* dataloader->AddSpectator( "QAL"   ,  "QAL"    , "units", 'F' ); NVars++; */ static const Float_t&     QAL                                      = iter("QAL");   
/* dataloader->AddSpectator( "flagL" ,  "flagL"  , "units", 'F' ); NVars++; */ static const Float_t&     flagL                                    = iter("flagL"); 
   dataloader->AddSpectator( "zL"    ,  "zL"     , "units", 'F' ); NVars++; static const Float_t&     zL                                       = iter("zL");    
   dataloader->AddSpectator( "adcL"  ,  "adcL"   , "units", 'F' ); NVars++; static const Float_t&     adcL                                     = iter("adcL");  
   dataloader->AddSpectator( "padOv" ,  "padOv"  , "units", 'F' ); NVars++; static const Float_t&     padOv                                    = iter("padOv"); 
   dataloader->AddSpectator( "tbkOv" ,  "tbkOv"  , "units", 'F' ); NVars++; static const Float_t&     tbkOv                                    = iter("tbkOv"); 
   dataloader->AddSpectator( "dpad"  ,  "dpad"   , "units", 'F' ); NVars++; 
   dataloader->AddSpectator( "dtbk"  ,  "dtbk"   , "units", 'F' ); NVars++;
   dataloader->AddVariable ( "AdcLD"  , "AdcLD"  , "units", 'F' ); NVars++;
   // global event weights per tree (see below for setting event-wise weights)
   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;
   // To give different trees for training and testing, do as follows:
   // Use the following code instead of the above two or four lines to add signal and background
   // training and test events "by hand"
   // NOTE that in this case one should not give expressions (such as "var1+var2") in the input
   //      variable definition, but simply compute the expression before adding the event
   // ```cpp
   // --- begin ----------------------------------------------------------
   std::vector<Double_t> vars( NVars ); // vector has size of number of input variables
   Int_t ev = 0, evS = 0, evB = 0;
   Bool_t inner = Opt.Contains("I",TString::kIgnoreCase);
   while (iter.Next() > 0) {
     ev++;
     if (flagK != 2 && flagL !=2) continue;
     if (inner) {
       if ( row >  40) continue;
     }  else {
       if ( row <= 40) continue;
     }
     Float_t  treevars[14] = {row, 
			      padK, tbkK, zK, adcK,
			      padL, tbkL, zL, adcL,
			      padOv, tbkOv,
			      padK-padL, tbkK-tbkL,
			      Float_t (TMath::Log(adcK)-TMath::Log(adcL))
     };
     for (UInt_t ivar=0; ivar<NVars; ivar++) vars[ivar] = treevars[ivar];
     // add training and test events; here: first half is training, second is testing
     // note that the weight can also be event-wise
     Int_t sb = 0;
     if (IdTK != IdTL) sb = 1;
     Ov[sb]->Fill(tbkOv, padOv);
     dPT[sb]->Fill(tbkK-tbkL, padK-padL);
     AdcL[sb]->Fill(TMath::Log(adcK),TMath::Log(adcL));
     AdcLD[sb]->Fill(vars[13]);  // TMath::Log(adcK)-TMath::Log(adcL));
     // Cut
     if (tbkOv < -2 ||  // two empty time buckets between clusters. no.gap in pads
	 padOv <  0 ) continue;
     dPTC[sb]->Fill(tbkK-tbkL, padK-padL);
     AdcLC[sb]->Fill(TMath::Log(adcK),TMath::Log(adcL));
     AdcLDC[sb]->Fill(vars[13]); // TMath::Log(adcK)-TMath::Log(adcL));
     if (! sb) {// && QAK > 90 && QAL > 90) { // Signal
       evS++;
       if (evS%2) dataloader->AddSignalTrainingEvent( vars, signalWeight );
       else                   dataloader->AddSignalTestEvent    ( vars, signalWeight );
     } else { //Background
       evB++;
       // add training and test events; here: first half is training, second is testing
       // note that the weight can also be event-wise
       if (evB%2) dataloader->AddBackgroundTrainingEvent( vars, backgroundWeight );
       else       dataloader->AddBackgroundTestEvent    ( vars, backgroundWeight );
     }
     //    if (ev > 100000) break;
   }
   outputFile->Write();
   // --- end ------------------------------------------------------------
   // ```
   // End of tree registration

   // Tell the factory/dataloader how to use the training and testing events
   //
   TCut mycut = "";
   dataloader->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );
   //
   // To also specify the number of testing events, use:
   // ### Book MVA methods
   //
   // Please lookup the various method configuration options in the corresponding cxx files, eg:
   // src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/old_site/optionRef.html
   // it is possible to preset ranges in the option string in which the cut optimisation should be done:
   // "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable

   // Cut optimisation
   if (Use["Cuts"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kCuts, "Cuts",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "Cuts",
#endif /* __ROOT6__ */
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" );

   if (Use["CutsD"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kCuts, "CutsD",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsD",
#endif /* __ROOT6__ */
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=Decorrelate" );

   if (Use["CutsPCA"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kCuts, "CutsPCA",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsPCA",
#endif /* __ROOT6__ */
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=PCA" );

   if (Use["CutsGA"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kCuts, "CutsGA",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsGA",
#endif /* __ROOT6__ */
                           "H:!V:FitMethod=GA:CutRangeMin[0]=-10:CutRangeMax[0]=10:VarProp[1]=FMax:EffSel:Steps=30:Cycles=3:PopSize=400:SC_steps=10:SC_rate=5:SC_factor=0.95" );

   if (Use["CutsSA"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kCuts, "CutsSA",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsSA",
#endif /* __ROOT6__ */
                           "!H:!V:FitMethod=SA:EffSel:MaxCalls=150000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );

   // Likelihood ("naive Bayes estimator")
   if (Use["Likelihood"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kLikelihood, "Likelihood",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "Likelihood",
#endif /* __ROOT6__ */
                           "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" );

   // Decorrelated likelihood
   if (Use["LikelihoodD"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodD",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodD",
#endif /* __ROOT6__ */
                           "!H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=Decorrelate" );

   // PCA-transformed likelihood
   if (Use["LikelihoodPCA"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodPCA",
                           "!H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=PCA" ); 
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodPCA",
                           "!H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=PCA" );
#endif /* __ROOT6__ */

   // Use a kernel density estimator to approximate the PDFs
   if (Use["LikelihoodKDE"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodKDE",
                           "!H:!V:!TransformOutput:PDFInterpol=KDE:KDEtype=Gauss:KDEiter=Adaptive:KDEFineFactor=0.3:KDEborder=None:NAvEvtPerBin=50" ); 
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodKDE",
                           "!H:!V:!TransformOutput:PDFInterpol=KDE:KDEtype=Gauss:KDEiter=Adaptive:KDEFineFactor=0.3:KDEborder=None:NAvEvtPerBin=50" );
#endif /* __ROOT6__ */

   // Use a variable-dependent mix of splines and kernel density estimator
   if (Use["LikelihoodMIX"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodMIX",
                           "!H:!V:!TransformOutput:PDFInterpolSig[0]=KDE:PDFInterpolBkg[0]=KDE:PDFInterpolSig[1]=KDE:PDFInterpolBkg[1]=KDE:PDFInterpolSig[2]=Spline2:PDFInterpolBkg[2]=Spline2:PDFInterpolSig[3]=Spline2:PDFInterpolBkg[3]=Spline2:KDEtype=Gauss:KDEiter=Nonadaptive:KDEborder=None:NAvEvtPerBin=50" ); 
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodMIX",
                           "!H:!V:!TransformOutput:PDFInterpolSig[0]=KDE:PDFInterpolBkg[0]=KDE:PDFInterpolSig[1]=KDE:PDFInterpolBkg[1]=KDE:PDFInterpolSig[2]=Spline2:PDFInterpolBkg[2]=Spline2:PDFInterpolSig[3]=Spline2:PDFInterpolBkg[3]=Spline2:KDEtype=Gauss:KDEiter=Nonadaptive:KDEborder=None:NAvEvtPerBin=50" );
#endif /* __ROOT6__ */

   // Test the multi-dimensional probability density estimator
   // here are the options strings for the MinMax and RMS methods, respectively:
#ifdef __ROOT6__
   //
#endif /* __ROOT6__ */
   //      "!H:!V:VolumeRangeMode=MinMax:DeltaFrac=0.2:KernelEstimator=Gauss:GaussSigma=0.3" );
   //      "!H:!V:VolumeRangeMode=RMS:DeltaFrac=3:KernelEstimator=Gauss:GaussSigma=0.3" );
   if (Use["PDERS"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kPDERS, "PDERS",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kPDERS, "PDERS",
#endif /* __ROOT6__ */
                           "!H:!V:NormTree=T:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600" );

   if (Use["PDERSD"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kPDERS, "PDERSD",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kPDERS, "PDERSD",
#endif /* __ROOT6__ */
                           "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=Decorrelate" );

   if (Use["PDERSPCA"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kPDERS, "PDERSPCA",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kPDERS, "PDERSPCA",
#endif /* __ROOT6__ */
                           "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=PCA" );

   // Multi-dimensional likelihood estimator using self-adapting phase-space binning
   if (Use["PDEFoam"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kPDEFoam, "PDEFoam",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kPDEFoam, "PDEFoam",
#endif /* __ROOT6__ */
                           "!H:!V:SigBgSeparate=F:TailCut=0.001:VolFrac=0.0666:nActiveCells=500:nSampl=2000:nBin=5:Nmin=100:Kernel=None:Compress=T" );

   if (Use["PDEFoamBoost"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kPDEFoam, "PDEFoamBoost",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kPDEFoam, "PDEFoamBoost",
#endif /* __ROOT6__ */
                           "!H:!V:Boost_Num=30:Boost_Transform=linear:SigBgSeparate=F:MaxDepth=4:UseYesNoCell=T:DTLogic=MisClassificationError:FillFoamWithOrigWeights=F:TailCut=0:nActiveCells=500:nBin=20:Nmin=400:Kernel=None:Compress=T" );

   // K-Nearest Neighbour classifier (KNN)
   if (Use["KNN"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kKNN, "KNN",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kKNN, "KNN",
#endif /* __ROOT6__ */
                           "H:nkNN=20:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:!Trim" );

   // H-Matrix (chi2-squared) method
   if (Use["HMatrix"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kHMatrix, "HMatrix", "!H:!V:VarTransform=None" );
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kHMatrix, "HMatrix", "!H:!V:VarTransform=None" );
#endif /* __ROOT6__ */

   // Linear discriminant (same as Fisher discriminant)
   if (Use["LD"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kLD, "LD", "H:!V:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kLD, "LD", "H:!V:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );
#endif /* __ROOT6__ */

   // Fisher discriminant (same as LD)
   if (Use["Fisher"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );
#endif /* __ROOT6__ */

   // Fisher with Gauss-transformed input variables
   if (Use["FisherG"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kFisher, "FisherG", "H:!V:VarTransform=Gauss" );
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kFisher, "FisherG", "H:!V:VarTransform=Gauss" );
#endif /* __ROOT6__ */

   // Composite classifier: ensemble (tree) of boosted Fisher classifiers
   if (Use["BoostedFisher"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kFisher, "BoostedFisher", 
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kFisher, "BoostedFisher",
#endif /* __ROOT6__ */
                           "H:!V:Boost_Num=20:Boost_Transform=log:Boost_Type=AdaBoost:Boost_AdaBoostBeta=0.2:!Boost_DetailedMonitoring" );

   // Function discrimination analysis (FDA) -- test of various fitters - the recommended one is Minuit (or GA or SA)
   if (Use["FDA_MC"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kFDA, "FDA_MC",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_MC",
#endif /* __ROOT6__ */
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:SampleSize=100000:Sigma=0.1" );

   if (Use["FDA_GA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kFDA, "FDA_GA",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:PopSize=300:Cycles=3:Steps=20:Trim=True:SaveBestGen=1" );
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_GA",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:PopSize=100:Cycles=2:Steps=5:Trim=True:SaveBestGen=1" );
#endif /* __ROOT6__ */

   if (Use["FDA_SA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kFDA, "FDA_SA",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_SA",
#endif /* __ROOT6__ */
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=SA:MaxCalls=15000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );

   if (Use["FDA_MT"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kFDA, "FDA_MT",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_MT",
#endif /* __ROOT6__ */
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=2:UseImprove:UseMinos:SetBatch" );

   if (Use["FDA_GAMT"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kFDA, "FDA_GAMT",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_GAMT",
#endif /* __ROOT6__ */
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:Cycles=1:PopSize=5:Steps=5:Trim" );

   if (Use["FDA_MCMT"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kFDA, "FDA_MCMT",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_MCMT",
#endif /* __ROOT6__ */
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:SampleSize=20" );

   // TMVA ANN: MLP (recommended ANN) -- all ANNs in TMVA are Multilayer Perceptrons
   if (Use["MLP"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator" );
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator" );
#endif /* __ROOT6__ */

   if (Use["MLPBFGS"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kMLP, "MLPBFGS", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:!UseRegulator" );
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLPBFGS", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:!UseRegulator" );
#endif /* __ROOT6__ */

   if (Use["MLPBNN"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kMLP, "MLPBNN", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:UseRegulator" ); // BFGS training with bayesian regulators
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLPBNN", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=60:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:UseRegulator" ); // BFGS training with bayesian regulators


   // Multi-architecture DNN implementation.
   if (Use["DNN_CPU"] or Use["DNN_GPU"]) {
      // General layout.
      TString layoutString ("Layout=TANH|128,TANH|128,TANH|128,LINEAR");

      // Define Training strategy. One could define multiple strategy string separated by the "|" delimiter

      TString trainingStrategyString = ("TrainingStrategy=LearningRate=1e-2,Momentum=0.9,"
                                        "ConvergenceSteps=20,BatchSize=100,TestRepetitions=1,"
                                        "WeightDecay=1e-4,Regularization=None,"
                                        "DropConfig=0.0+0.5+0.5+0.5");

      // General Options.
      TString dnnOptions ("!H:V:ErrorStrategy=CROSSENTROPY:VarTransform=N:"
                          "WeightInitialization=XAVIERUNIFORM");
      dnnOptions.Append (":"); dnnOptions.Append (layoutString);
      dnnOptions.Append (":"); dnnOptions.Append (trainingStrategyString);

      // Cuda implementation.
      if (Use["DNN_GPU"]) {
         TString gpuOptions = dnnOptions + ":Architecture=GPU";
         factory->BookMethod(dataloader, TMVA::Types::kDL, "DNN_GPU", gpuOptions);
      }
      // Multi-core CPU implementation.
      if (Use["DNN_CPU"]) {
         TString cpuOptions = dnnOptions + ":Architecture=CPU";
         factory->BookMethod(dataloader, TMVA::Types::kDL, "DNN_CPU", cpuOptions);
      }
   }
#endif /* __ROOT6__ */

   // CF(Clermont-Ferrand)ANN
   if (Use["CFMlpANN"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kCFMlpANN, "CFMlpANN", "!H:!V:NCycles=2000:HiddenLayers=N+1,N"  ); // n_cycles:#nodes:#nodes:...  
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kCFMlpANN, "CFMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N"  ); // n_cycles:#nodes:#nodes:...
#endif /* __ROOT6__ */

   // Tmlp(Root)ANN
   if (Use["TMlpANN"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kTMlpANN, "TMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N:LearningMethod=BFGS:ValidationFraction=0.3"  ); // n_cycles:#nodes:#nodes:...
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kTMlpANN, "TMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N:LearningMethod=BFGS:ValidationFraction=0.3"  ); // n_cycles:#nodes:#nodes:...
#endif /* __ROOT6__ */

   // Support Vector Machine
   if (Use["SVM"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kSVM, "SVM", "Gamma=0.25:Tol=0.001:VarTransform=Norm" );
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kSVM, "SVM", "Gamma=0.25:Tol=0.001:VarTransform=Norm" );
#endif /* __ROOT6__ */

   // Boosted Decision Trees
   if (Use["BDTG"]) // Gradient Boost
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kBDT, "BDTG",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG",
#endif /* __ROOT6__ */
                           "!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2" );

   if (Use["BDT"])  // Adaptive Boost
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kBDT, "BDT",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT",
#endif /* __ROOT6__ */
                           "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );

   if (Use["BDTB"]) // Bagging
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kBDT, "BDTB",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTB",
#endif /* __ROOT6__ */
                           "!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20" );

   if (Use["BDTD"]) // Decorrelation + Adaptive Boost
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kBDT, "BDTD",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTD",
#endif /* __ROOT6__ */
                           "!H:!V:NTrees=400:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:VarTransform=Decorrelate" );

   if (Use["BDTF"])  // Allow Using Fisher discriminant in node splitting for (strong) linearly correlated variables
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kBDT, "BDTMitFisher",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTF",
#endif /* __ROOT6__ */
                           "!H:!V:NTrees=50:MinNodeSize=2.5%:UseFisherCuts:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20" );

   // RuleFit -- TMVA implementation of Friedman's method
   if (Use["RuleFit"])
#if ROOT_VERSION_MAJOR < 6
      factory->BookMethod( TMVA::Types::kRuleFit, "RuleFit",
#else /* __ROOT6__ */
      factory->BookMethod( dataloader, TMVA::Types::kRuleFit, "RuleFit",
#endif /* __ROOT6__ */
                           "H:!V:RuleFitModule=RFTMVA:Model=ModRuleLinear:MinImp=0.001:RuleMinDist=0.001:NTrees=20:fEventsMin=0.01:fEventsMax=0.5:GDTau=-1.0:GDTauPrec=0.01:GDStep=0.01:GDNSteps=10000:GDErrScale=1.02" );

   // For an example of the category classifier usage, see: TMVAHitTClassificationCategory
   //
   // --------------------------------------------------------------------------------------------------
   //  Now you can optimize the setting (configuration) of the MVAs using the set of training events
   // STILL EXPERIMENTAL and only implemented for BDT's !
   //
   //     factory->OptimizeAllMethods("SigEffAtBkg0.01","Scan");
   //     factory->OptimizeAllMethods("ROCIntegral","FitGA");
   //
   // --------------------------------------------------------------------------------------------------

   // Now you can tell the factory to train, test, and evaluate the MVAs
   //
   // Train MVAs using the set of training events
   factory->TrainAllMethods();

   // Evaluate all MVAs using the set of test events
   factory->TestAllMethods();

   // Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();

   // --------------------------------------------------------------

   // Save the output
   outputFile->Write();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAHitTClassification is done!" << std::endl;

   // Launch the GUI for the root macros
#if ROOT_VERSION_MAJOR < 6
			   //   if (!gROOT->IsBatch()) TMVAGui( outfileName );
#else /* __ROOT6__ */
   if (!gROOT->IsBatch()) TMVA::TMVAGui( outfileName );

#endif /* __ROOT6__ */
   return 0;
}
#if 0
int main( int argc, char** argv )
{
   // Select methods (don't look at this code - not of interest)
   TString methodList;
   for (int i=1; i<argc; i++) {
      TString regMethod(argv[i]);
      if(regMethod=="-b" || regMethod=="--batch") continue;
      if (!methodList.IsNull()) methodList += TString(",");
      methodList += regMethod;
   }
   return TMVAHitTClassification(methodList);
}
#endif
