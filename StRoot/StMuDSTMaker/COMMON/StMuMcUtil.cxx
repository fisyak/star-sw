#include "StMuMcUtil.h"
#include "StMuDst.h"
#include "StMuMcTrack.h"
#include "StMuMcVertex.h"
#include "StMuArrays.h"
#include "TClonesArray.h"

//_____________________________________________________________________________
const StMuMcTrack* StMuMcUtil::findTrack(unsigned int id, const TClonesArray* mcTracks) {
  if (!mcTracks || id == 0) return nullptr;
  const int n = mcTracks->GetEntriesFast();
  const int idx = static_cast<int>(id) - 1;
  if (idx >= 0 && idx < n) {
    const auto* t = static_cast<const StMuMcTrack*>(mcTracks->UncheckedAt(idx));
    if (t && static_cast<unsigned int>(t->Id()) == id) return t;
  }
  return nullptr;
}
const StMuMcTrack* StMuMcUtil::findTrack(unsigned int id, const StMuDst* muDst) {
  return muDst ? findTrack(id, muDst->mcArray(MCTrack)) : nullptr;
}
//_____________________________________________________________________________
const StMuMcVertex* StMuMcUtil::findVertex(unsigned int id, const TClonesArray* mcVertices) {
  if (!mcVertices || id == 0) return nullptr;
  const int n = mcVertices->GetEntriesFast();
  const int idx = static_cast<int>(id) - 1;
  if (idx >= 0 && idx < n) {
    const auto* v = static_cast<const StMuMcVertex*>(mcVertices->UncheckedAt(idx));
    if (v && static_cast<unsigned int>(v->Id()) == id) return v;
  }
  return nullptr;
}
const StMuMcVertex* StMuMcUtil::findVertex(unsigned int id, const StMuDst* muDst) {
  return muDst ? findVertex(id, muDst->mcArray(MCVertex)) : nullptr;
}
//_____________________________________________________________________________
unsigned int StMuMcUtil::backTraceMcTrack(unsigned int id,
                                             const TClonesArray* mcTracks,
                                             const TClonesArray* mcVertices) {
  if (!mcTracks || id == 0) return id;
  const StMuMcTrack* trk = findTrack(id, mcTracks);
  if (!trk) return id;

  while (trk && trk->IdVx() > 1 && mcVertices) {
    const StMuMcVertex* vtx = findVertex(trk->IdVx(), mcVertices);
    if (!vtx) break;

    const int parId = vtx->IdParTrk();
    if (parId <= 0) break; // Reached primary vertex with no parent track

    const StMuMcTrack* parent = findTrack(parId, mcTracks);
    if (!parent) break;

    trk = parent;
  }

  return trk ? static_cast<unsigned int>(trk->Id()) : id;
}
unsigned int StMuMcUtil::backTraceMcTrack(unsigned int id, const StMuDst* muDst) {
  return muDst ? backTraceMcTrack(id, muDst->mcArray(MCTrack), muDst->mcArray(MCVertex)) : id;
}
//_____________________________________________________________________________
const StMuMcTrack* StMuMcUtil::getPrimaryTrack(unsigned int id,
                                             const TClonesArray* mcTracks,
                                             const TClonesArray* mcVertices) {
  const unsigned int primId = backTraceMcTrack(id, mcTracks, mcVertices);
  return findTrack(primId, mcTracks);
}

const StMuMcTrack* StMuMcUtil::getPrimaryTrack(unsigned int id, const StMuDst* muDst) {
  return muDst ? getPrimaryTrack(id, muDst->mcArray(MCTrack), muDst->mcArray(MCVertex)) : nullptr;
}