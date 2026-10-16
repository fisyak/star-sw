#ifndef StMuFcsUtil_h
#define StMuFcsUtil_h
#include "TObject.h"

#include <map>
#include <vector>
#include <utility>

class StMuFcsCollection;
class StFcsCollection;
class StTriggerData;
class StMuDst;
class StFcsHit;
class StFcsCluster;
class StFcsPoint;
class StMuDst;
class StMuMcTrack;
class StMuFcsHit;
class StMuFcsCluster;
class TClonesArray;

class StMuFcsUtil : public TObject
{
public:
  StMuFcsUtil();
  ~StMuFcsUtil();
  StMuFcsCollection* getMuFcs(StFcsCollection*);
  StFcsCollection*   getFcs(StMuFcsCollection*);
  void               fillMuFcs(StMuFcsCollection*,StFcsCollection*);
  void               fillFcs(StFcsCollection*,StMuFcsCollection*);
  
  std::map< const StFcsCluster*, StMuFcsCluster* > & getClusterMap() {return mMapClusters; }

  // StMuMcTrack, StMuFcsHit and StMuFcsCluster accessors
  static const StMuMcTrack* getParentMcTrack(const StMuFcsHit* h, const TClonesArray* mcTracks, float& fraction, int& ntrk, unsigned int order = 0);
  static const StMuMcTrack* getParentMcTrack(const StMuFcsCluster* c, const TClonesArray* mcTracks, float& fraction, int& ntrk, unsigned int order = 0);
  static const StMuMcTrack* getPrimaryMcTrack(const StMuFcsHit* h, const TClonesArray* mcTracks, const TClonesArray* mcVertices, float& fraction, int& ntrk, unsigned int order = 0);
  static const StMuMcTrack* getPrimaryMcTrack(const StMuFcsCluster* c, const TClonesArray* mcTracks, const TClonesArray* mcVertices, float& fraction, int& ntrk, unsigned int order = 0);
  static const StMuMcTrack* getMcTrack(const StMuFcsHit* h, const TClonesArray* mcTracks, const TClonesArray* mcVertices, float& fraction, int& ntrk, unsigned int order = 0, int mode = 0);
  static const StMuMcTrack* getMcTrack(const StMuFcsCluster* c, const TClonesArray* mcTracks, const TClonesArray* mcVertices, float& fraction, int& ntrk, unsigned int order = 0, int mode = 0);
  static const StMuMcTrack* getParentMcTrack(const StMuFcsHit* h, const StMuDst* mu, float& fraction, int& ntrk, unsigned int order = 0);
  static const StMuMcTrack* getParentMcTrack(const StMuFcsCluster* c, const StMuDst* mu, float& fraction, int& ntrk, unsigned int order = 0);
  static const StMuMcTrack* getPrimaryMcTrack(const StMuFcsHit* h, const StMuDst* mu, float& fraction, int& ntrk, unsigned int order = 0);
  static const StMuMcTrack* getPrimaryMcTrack(const StMuFcsCluster* c, const StMuDst* mu, float& fraction, int& ntrk, unsigned int order = 0);

  
private:

  /** Create StMuFcsHits from StFcsHits and fill StMuFcsCollection */
  void fillMuFcsHits(StMuFcsCollection*, StFcsCollection*);
  /** Create StMuFcsClusters from StFcsClusters and fill StMuFcsCollection */
  void fillMuFcsClusters(StMuFcsCollection*, StFcsCollection*);
  /** Create StMuFcsPoints from StFcsPoints and fill StMuFcsCollection */
  void fillMuFcsPoints(StMuFcsCollection*, StFcsCollection*);
  /** Create StMuFcsInfo from reconstruction flag and det indices */
  void fillMuFcsInfo(StMuFcsCollection*, StFcsCollection*);
  /** Set the relationships in StMu */
  void rebuildRelationships(StFcsCollection*, StMuFcsCollection*);
  /** fill the StFcsHits from MuDst */
  void fillFcsHits(StFcsCollection*, StMuFcsCollection*);

  static const StMuMcTrack*  getMcTrackFromTracks(const std::vector<std::pair<unsigned int, float>>& rawTracks,
                                           const TClonesArray* mcTracks,
                                           const TClonesArray* mcVertices,
                                           float& fraction, int& ntrk,
                                           unsigned int order, int mode);


  /** holds relation between StEvent and StMuDst types (in memory)**/
  std::map< const StFcsHit*, StMuFcsHit* > mMapHits;
  std::map< const StFcsCluster*, StMuFcsCluster* > mMapClusters;
  std::map< const StFcsPoint*, StMuFcsPoint* > mMapPoints;

  ClassDef(StMuFcsUtil,1)
};

#endif
