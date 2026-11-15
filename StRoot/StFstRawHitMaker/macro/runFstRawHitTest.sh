#!/bin/bash
# Production test for the fstMuRawHit option: write a MuDst WITH FST raw hits from a real
# DAQ file, so the branch that has never been exercised gets exercised and the round trip
# can be validated before a full production commits to it.
#
# Run from this directory so the locally built StMuDSTMaker -- which carries the new
# fillFstRawHits() read-back -- is picked up ahead of $STAR.
#   pp2022a      the real 2022 pp production chain
#   fst          fstRawHit,fstCluster,fstHit
#   CMuDST       write the MuDst
#   fstMuRawHit  pulls in fstEvtRawHit -> fstRawHit
# bash, not csh: csh mangles the nested quotes root4star needs.
# Keep nEvents small -- pp2022a runs full TPC tracking, which dominates the time.
#
# Usage:
#   ./runFstRawHitTest.sh [nEvents] [daqFile] [workDir]
#
#   nEvents   events to reconstruct                      (default 200)
#   daqFile   DAQ file to read                           (default: the 2022 pp
#             file below, which is known to contain FST data)
#   workDir   directory to run in, i.e. the top of the   (default: the top of
#             checkout whose StMuDSTMaker should win      the checkout holding
#             over $STAR                                  this script)
#
# Examples:
#   ./runFstRawHitTest.sh
#   ./runFstRawHitTest.sh 500
#   ./runFstRawHitTest.sh 500 /star/data01/daq/2022/063/23063032/st_physics_23063032_raw_1000009.daq

NEV=${1:-200}
DAQ=${2:-/star/data01/daq/2022/063/23063032/st_physics_23063032_raw_1000009.daq}
# default: two levels up from this script is StRoot/..., four is the checkout top
WORKDIR=${3:-$( cd "$( dirname "${BASH_SOURCE[0]}" )/../../.." && pwd )}

[ -d "$WORKDIR" ] || { echo "work directory not found: $WORKDIR"; exit 1; }
cd "$WORKDIR" || exit 1
[ -e "$DAQ" ] || { echo "DAQ file not found: $DAQ"; exit 1; }
echo "=== workdir $WORKDIR ==="
echo "=== writing a MuDst with fstMuRawHit from $DAQ ($NEV events) ==="
root4star -l -b -q "bfc.C($NEV,\"pp2022a fst CMuDST fstMuRawHit\",\"$DAQ\")" > fstrawhit_test.log 2>&1
echo "root4star exit=$?"
ls -la *.MuDst.root 2>/dev/null || echo "(no MuDst produced)"
tr -d '\000' < fstrawhit_test.log | grep -iE "fstMuRawHit|fstEvtRawHit|Fatal|not found|Error in <" | head -8
