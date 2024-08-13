/**
 * \class StPicoDst
 * \brief Main class that keeps TClonesArrays with main classes
 *
 * The StPicoDstClass holds pointers to the picoArrays with all data
 */

#ifndef StPicoDst_h
#define StPicoDst_h

// ROOT headers
#include "TClonesArray.h"

// PicoDst headers
#include "StPicoArrays.h"

// Forward declarations
class StPicoEvent;
class StPicoTrack;
class StPicoEmcTrigger;
class StPicoMtdTrigger;
class StPicoBTowHit;
class StPicoBTofHit;
class StPicoETofHit;
class StPicoMtdHit;
class StPicoEpdHit;
class StPicoBbcHit;
class StPicoFmsHit;
class StPicoBEmcPidTraits;
class StPicoBTofPidTraits;
class StPicoETofPidTraits;
class StPicoMtdPidTraits;
class StPicoTrackCovMatrix;
class StPicoBEmcSmdEHit;
class StPicoBEmcSmdPHit;
class StPicoETofHit;
class StPicoETofPidTraits;
class StPicoMcVertex;
class StPicoMcTrack;

//_________________
class StPicoDst {

 public:
#ifdef __TFG__VERSION__
  StPicoDst() { fgPicoDst = this;}
  virtual ~StPicoDst() {fgPicoDst = 0;}
  virtual Bool_t IsGoodTrigger() const;
#else /* ! __TFG__VERSION__ */
  /// Default constructor
  StPicoDst() { /* emtpy */}
  /// Destructor
  ~StPicoDst() { /* empty*/ }
#endif /* __TFG__VERSION__ */

  /// Set the pointers to the TClonesArrays
  void set(TClonesArray**);
  /// Reset the pointers to the TClonesArrays to 0
  void unset();
  /// Return pointer to the n-th TClonesArray
  TClonesArray* picoArray(Int_t type) { return picoArrays[type]; }
  /// Return pointer to current StPicoEvent (class holding the event wise information)
  StPicoEvent* event() { return (StPicoEvent*)picoArrays[StPicoArrays::Event]->UncheckedAt(0); }
  /// Return pointer to i-th track
  StPicoTrack* track(Int_t i) { return (StPicoTrack*)picoArrays[StPicoArrays::Track]->UncheckedAt(i); }
  /// Return pointer to i-th trigger data
  StPicoEmcTrigger* emcTrigger(Int_t i) { return (StPicoEmcTrigger*)picoArrays[StPicoArrays::EmcTrigger]->UncheckedAt(i); }
  /// Return pointer to i-th MTD trigger data
  StPicoMtdTrigger* mtdTrigger(Int_t i) { return (StPicoMtdTrigger*)picoArrays[StPicoArrays::MtdTrigger]->UncheckedAt(i); }
  /// Return pointer to i-th btow hit
  StPicoBTowHit* btowHit(Int_t i) { return (StPicoBTowHit*)picoArrays[StPicoArrays::BTowHit]->UncheckedAt(i); }
  /// Return pointer to i-th btof hit
  StPicoBTofHit* btofHit(Int_t i) { return (StPicoBTofHit*)picoArrays[StPicoArrays::BTofHit]->UncheckedAt(i); }
  /// Return pointer to i-th mtd hit
  StPicoMtdHit*  mtdHit(Int_t i) { return (StPicoMtdHit*)picoArrays[StPicoArrays::MtdHit]->UncheckedAt(i); }
  /// Return pointer to i-th bbc hit
  StPicoBbcHit* bbcHit(Int_t i) { return (StPicoBbcHit*)picoArrays[StPicoArrays::BbcHit]->UncheckedAt(i); }
  /// Return pointer to i-th epd hit
  StPicoEpdHit* epdHit(Int_t i) { return (StPicoEpdHit*)picoArrays[StPicoArrays::EpdHit]->UncheckedAt(i); }
  /// Return pointer to i-th fms hit
  StPicoFmsHit*  fmsHit(Int_t i) { return (StPicoFmsHit*)picoArrays[StPicoArrays::FmsHit]->UncheckedAt(i); }
  /// Return pointer to i-th emc pidTraits
  StPicoBEmcPidTraits* bemcPidTraits(Int_t i) { return (StPicoBEmcPidTraits*)picoArrays[StPicoArrays::BEmcPidTraits]->UncheckedAt(i); }
  /// Return pointer to i-th btof pidTraits
  StPicoBTofPidTraits* btofPidTraits(Int_t i) { return (StPicoBTofPidTraits*)picoArrays[StPicoArrays::BTofPidTraits]->UncheckedAt(i); }
  /// Return pointer to i-th mtd pidTraits
  StPicoMtdPidTraits* mtdPidTraits(Int_t i) { return (StPicoMtdPidTraits*)picoArrays[StPicoArrays::MtdPidTraits]->UncheckedAt(i); }
  /// Return pointer to i-th track covariance matrix
  StPicoTrackCovMatrix* trackCovMatrix(Int_t i) { return (StPicoTrackCovMatrix*)picoArrays[StPicoArrays::TrackCovMatrix]->UncheckedAt(i); }
  /// Return pointer to i-th BEMC SMD eta hit
  StPicoBEmcSmdEHit* bemcSmdEHit(Int_t i) { return (StPicoBEmcSmdEHit*)picoArrays[StPicoArrays::BEmcSmdEHit]->UncheckedAt(i); }
  /// Return pointer to i-th BEMC SMD phi hit
  StPicoBEmcSmdPHit* bemcSmdPHit(Int_t i) { return (StPicoBEmcSmdPHit*)picoArrays[StPicoArrays::BEmcSmdPHit]->UncheckedAt(i); }
  /// Return pointer to i-th etof hit
  StPicoETofHit* etofHit(Int_t i) { return (StPicoETofHit*)picoArrays[StPicoArrays::ETofHit]->UncheckedAt(i); }
  /// Return pointer to i-th etof pidTraits
  StPicoETofPidTraits* etofPidTraits(Int_t i) { return (StPicoETofPidTraits*)picoArrays[StPicoArrays::ETofPidTraits]->UncheckedAt(i); }
  /// Return pointer to i-th MC vertex
  StPicoMcVertex* mcVertex(Int_t i) { return (StPicoMcVertex*)picoArrays[StPicoArrays::McVertex]->UncheckedAt(i); }
  /// Return pointer to i-th MC track
  StPicoMcTrack* mcTrack(Int_t i) { return (StPicoMcTrack*)picoArrays[StPicoArrays::McTrack]->UncheckedAt(i); }
  /// Return number of tracks
  UInt_t numberOfTracks() { return picoArrays[StPicoArrays::Track]->GetEntriesFast(); }
  /// Return number of Emc triggers
  UInt_t numberOfEmcTriggers() { return picoArrays[StPicoArrays::EmcTrigger]->GetEntriesFast(); }
  /// Return number of MTD triggers
  UInt_t numberOfMtdTriggers() { return picoArrays[StPicoArrays::MtdTrigger]->GetEntriesFast(); }
  /// Return number of BTow hits
  UInt_t numberOfBTowHits() { return picoArrays[StPicoArrays::BTowHit]->GetEntriesFast(); }
  /// Return number of BTof hits
  UInt_t numberOfBTofHits() { return picoArrays[StPicoArrays::BTofHit]->GetEntriesFast(); }
  /// Return number of MTD hits
  UInt_t numberOfMtdHits() { return picoArrays[StPicoArrays::MtdHit]->GetEntriesFast(); }
  /// Return number of BBC hits
  UInt_t numberOfBbcHits() { return picoArrays[StPicoArrays::BbcHit]->GetEntriesFast(); }
  /// Return number of EPD hits
  UInt_t numberOfEpdHits() { return picoArrays[StPicoArrays::EpdHit]->GetEntriesFast(); }
  /// Return number of FMS hits
  UInt_t numberOfFmsHits() { return picoArrays[StPicoArrays::FmsHit]->GetEntriesFast(); }
  /// Return number of BEMC PID traits
  UInt_t numberOfBEmcPidTraits() { return picoArrays[StPicoArrays::BEmcPidTraits]->GetEntriesFast(); }
  /// Return number of BTof PID traits
  UInt_t numberOfBTofPidTraits() { return picoArrays[StPicoArrays::BTofPidTraits]->GetEntriesFast(); }
  /// Return number of MTD traits
  UInt_t numberOfMtdPidTraits() { return picoArrays[StPicoArrays::MtdPidTraits]->GetEntriesFast(); }
  /// Return number of track covariance matrices
  UInt_t numberOfTrackCovMatrices() { return picoArrays[StPicoArrays::TrackCovMatrix]->GetEntriesFast(); }
  /// Return number of BEMC SMD eta hits
  UInt_t numberOfBEmcSmdEHits() { return picoArrays[StPicoArrays::BEmcSmdEHit]->GetEntriesFast(); }
  /// Return number of BEMC SMD phi hits
  UInt_t numberOfBEmcSmdPHits() { return picoArrays[StPicoArrays::BEmcSmdPHit]->GetEntriesFast(); }
  /// Return number of ETof hits
  UInt_t numberOfETofHits() { return picoArrays[StPicoArrays::ETofHit]->GetEntriesFast(); }
  /// Return number of ETOF PID traits
  UInt_t numberOfETofPidTraits() { return picoArrays[StPicoArrays::ETofPidTraits]->GetEntriesFast(); }
  /// Return number of MC vertices
  UInt_t numberOfMcVertices() { return picoArrays[StPicoArrays::McVertex]->GetEntriesFast(); }
  /// Return number of MC tracks
  UInt_t numberOfMcTracks() { return picoArrays[StPicoArrays::McTrack]->GetEntriesFast(); }

  /// Print information
  void print() const;
  /// Print track info
  void printTracks();
  /// Print trigger
  void printTriggers();
  /// Print BTOW hit info
  void printBTowHits();
  /// Print BTOF hit info
  void printBTofHits();
  /// Print MTD hit info
  void printMtdHits();
  /// Print FMS hit info
  void printFmsHits();
  /// Print BEMC PID trait info
  void printBEmcPidTraits();
  /// Print BTOF PID trait info
  void printBTofPidTraits();
  /// Print MTD PID trait info
  void printMtdPidTraits();
  /// Print track covariance matrix info
  void printTrackCovMatrices();
  /// Print BEMC SMD eta info
  void printBEmcSmdEHits();
  /// Print BEMC SMD phi info
  void printBEmcSmdPHits();
  /// Print ETOF hit info
  void printETofHits();
  /// Print ETOF PID trait info
  void printETofPidTraits();
  /// Print MC vertex info
  void printMcVertices();
  /// Print MC track info
  void printMcTracks();

#if defined (__TFG__VERSION__)
  static StPicoDst *instance() {return fgPicoDst;}
#endif /* __TFG__VERSION__ */

 private:

  /// Array of TClonesArrays
  TClonesArray** picoArrays;

#if defined (__TFG__VERSION__)
  static StPicoDst *fgPicoDst; //!
#endif /* __TFG__VERSION__ */
};

#endif
