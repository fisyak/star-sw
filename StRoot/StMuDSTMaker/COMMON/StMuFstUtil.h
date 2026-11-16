#ifndef StMuFstUtil_h
#define StMuFstUtil_h

#include <TObject.h>
#include <map>

class StMuFstCollection;
class StFstHitCollection;
class StFstEvtCollection;
class StMuDst;
class StFstHit;
class StFstRawHit;


class StMuFstUtil : public TObject
{
public:
    StMuFstUtil();
    ~StMuFstUtil();
    StMuFstCollection* getMuFst(StFstHitCollection*,StFstEvtCollection*);
    StFstHitCollection*   getFst(StMuFstCollection*);
    /** Rebuild the StEvent raw-hit collection from the MuDst.
     *  Counterpart of getMuFst()'s raw-hit half, which had no reverse until now:
     *  fillFst() restored only the hits, so FST raw hits written with the
     *  fstMuRawHit option could never be read back. Mirrors StMuFttUtil, where the
     *  equivalent has always existed (fillFttRawHits) and is what lets the FTT
     *  chain re-run from a MuDst. */
    StFstEvtCollection*   getFstEvt(StMuFstCollection*);
    void               fillMuFst(StMuFstCollection*,StFstHitCollection*,StFstEvtCollection*);
    void               fillFst(StFstHitCollection*,StMuFstCollection*);
    void               fillFstEvt(StFstEvtCollection*,StMuFstCollection*);


private:

    /** Create StMuFstHits from StFstHits and fill StMuFstCollection */
    void fillMuFstHits(StMuFstCollection*, StFstHitCollection*, StFstEvtCollection*);

    /** fill the StFstHits from MuDst */
    void fillFstHits(StFstHitCollection*, StMuFstCollection*);

    /** fill the StFstRawHits from MuDst */
    void fillFstRawHits(StFstEvtCollection*, StMuFstCollection*);

    ClassDef(StMuFstUtil,1)
};

#endif
