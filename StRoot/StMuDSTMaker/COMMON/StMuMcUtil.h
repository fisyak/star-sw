#ifndef StMuMcUtil_h
#define StMuMcUtil_h

class StMuDst;
class StMuMcTrack;
class StMuMcVertex;
class TClonesArray;

class StMuMcUtil {
public:
  StMuMcUtil() = delete;

  /// Find an MC track by its primary key
  static const StMuMcTrack* findTrack(unsigned int id, const TClonesArray* mcTracks);
  static const StMuMcTrack* findTrack(unsigned int id, const StMuDst* muDst);

  /// Find an MC vertex by its primary key
  static const StMuMcVertex* findVertex(unsigned int id, const TClonesArray* mcVertices);
  static const StMuMcVertex* findVertex(unsigned int id, const StMuDst* muDst);

  /// Back-trace a track ID through interaction vertices to find the primary particle ID
  static unsigned int backTraceMcTrack(unsigned int id,
                                           const TClonesArray* mcTracks,
                                           const TClonesArray* mcVertices);
  static unsigned int backTraceMcTrack(unsigned int id, const StMuDst* muDst);

  /// Back-trace and give the track pointer
  static const StMuMcTrack* getPrimaryTrack(unsigned int id,
                                           const TClonesArray* mcTracks,
                                           const TClonesArray* mcVertices);
  static const StMuMcTrack* getPrimaryTrack(unsigned int id, const StMuDst* muDst);
};

#endif // StMuMcUtil_h