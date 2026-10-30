#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

// Main PicoDst classes
#pragma link C++ class StPicoTrack+;
#pragma link C++ class StPicoMcVertex+;
#pragma link C++ class StPicoMcTrack+;
#pragma link C++ class StPicoMtdTrigger+;
#pragma link C++ class StPicoMtdPidTraits+;
#pragma link C++ class StPicoMtdHit+;
#pragma link C++ class StPicoFmsHit+;
#pragma link C++ class StPicoEvent+;
#pragma link C++ class StPicoEpdHit+;
#pragma link C++ class StPicoEmcTrigger+;
#pragma link C++ class StPicoBTowHit+;
#pragma link C++ class StPicoBTofPidTraits+;
#pragma link C++ class StPicoBTofHit+;
#pragma link C++ class StPicoBEmcPidTraits+;
#pragma link C++ class StPicoBbcHit+;
#pragma link C++ class StPicoTrackCovMatrix+;
#pragma link C++ class StPicoBEmcSmdEHit+;
#pragma link C++ class StPicoBEmcSmdPHit+;
#pragma link C++ class StPicoDstReader+;
#pragma link C++ class StPicoETofHit+;
#pragma link C++ class StPicoETofPidTraits+;
#pragma link C++ class StPicoFwdTrack+;
#pragma link C++ class StPicoFcsHit+;
#pragma link C++ class StPicoFcsCluster+;
#pragma link C++ class StPicoDst+;

// StarClassLibrary adopted classes
#pragma link C++ class StPicoHelix+;
#pragma link C++ class StPicoPhysicalHelix+;

// Schema evolution for the mVtxIndex repacking. Version 1 packed 6 bits of vertex
// index + 2 bits of track type; version 2 packs 5 + 3, because the track type
// outgrew two bits. Without this rule an old picoDst decodes wrongly and
// silently -- a Global track with an odd vertex index reads as BLCVertexConstrained.
//
// An old 6-bit index of 32-63 has nowhere to go in 5 bits, so it is pinned to 31
// rather than masked: masking would alias it onto a real, wrong vertex, reading 32
// back as vertex 0. Reco never writes 31 -- forward vertices come a handful per
// event -- so a 31 reads as "index was out of range on disk". An unset genfit
// vertex id (-1, which pack6and2 masked to 63) lands on 31 too, as it did before.
// StFwdTrack's rule for the same byte, on fwd-schema-stevent-tracktypes, is
// identical except for the class and the version it matches.
//
// MUST STAY ON ONE LINE: rootcint in ROOT 5.34 aborts with std::out_of_range if
// the pragma is split across continuation lines.
#pragma read sourceClass="StPicoFwdTrack" version="[1]" source="UChar_t mVtxIndex" targetClass="StPicoFwdTrack" target="mVtxIndex" code="{ unsigned int oldIdx = (onfile.mVtxIndex >> 2) & 0x3F; if (oldIdx > 31) oldIdx = 31; mVtxIndex = (UChar_t)((oldIdx << 3) | (onfile.mVtxIndex & 0x03)); }"

#endif
