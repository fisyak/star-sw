# FST raw-hit MuDst read-back tests

Developer tests for the `fstMuRawHit` write path and for
`StFstRawHitMaker::setMuDstInput()` / `readMuDst()`, which let FST be re-clustered
from a production MuDst.

The macros load each other and their input by relative path, so **run them from a
working directory that holds the MuDst**, with these files copied or symlinked in --
not from the repository top.

| macro | what it checks |
|---|---|
| `runFstRawHitTest.sh` | BFC production run with `fstMuRawHit` in the chain; produces the MuDst the rest use |
| `checkFstRawHit.C` | the written branch itself, leaf-based, so it does not depend on the classes that wrote it |
| `testFstReadBack.C` | `StMuFstUtil::getFstEvt` round trip: MuDst -> StEvent, counts and ids |
| `cmpFstClusters.C` + `runCmpFst.C` | clusters rebuilt from the MuDst vs. the ones production wrote into it |
| `testFstRecluster.C` | earlier, under-instrumented version of the cluster check; superseded by `cmpFstClusters.C` |

`cmpFstClusters.C` is compiled with ACLiC (`.C+`) on purpose: CINT recovers from
errors silently, which hid an earlier failure of this check entirely.
