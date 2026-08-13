#include "ultra64.h"

/* -------------------------------------------------------------------------
 * audioGeomNodeInit — 3D mesh initialiser (0x43C bytes, nonmatching).
 *
 * Initialises a mesh/vertex object (arg0 = dest Unk*) from a source
 * descriptor (arg1 = Unk*) and a render context (arg2 = void *).
 *
 * The selector byte at arg1->unk1C (1-6) picks a geometry data table:
 *   1 → gMidiSampleTblA   2 → gMidiSampleTblB   3 → gMidiSampleTblC
 *   4 → gMidiSampleTblD   5 → gMidiSampleTblE   6 → *(s32*)(arg1->unk20)
 *   default → gMidiSampleTblF
 *
 * After selection, iterates over the table entries converting integer
 * geometry data to floats and building vertex/strip arrays via
 * audioHeapAlloc, audioFillDecayTable.  Uses double-precision FPU for scale.
 *
 * Jump table: jtbl_8004CEB8 (6 entries, selector-1 = 0-5).
 * -------------------------------------------------------------------------
 */

void audioNodeInit(void *arg0, void *arg1, void *arg2, s32 arg3);
char *audioHeapAlloc(s32 arg0, s32 arg1, Unk *arg2, u8 arg3, s32 arg4);
void audioFillDecayTable(Unk *arg0);

extern s32 gMidiSampleTblA[];   /* geometry table: selector 1 */
extern s32 gMidiSampleTblB[];   /* geometry table: selector 2 */
extern s32 gMidiSampleTblC[];   /* geometry table: selector 3 */
extern s32 gMidiSampleTblD[];   /* geometry table: selector 4 */
extern s32 gMidiSampleTblE[];   /* geometry table: selector 5 */
extern s32 gMidiSampleTblF[];   /* geometry table: default */
extern f64 gGeomScaleConst;     /* double constant (scale factor, ldc1 in asm) */

/* audioNodeSetValue — mesh element setter (nonmatching, in geomBufWrite.c) */
s32 audioNodeSetValue(s32 *arg0, s32 arg1, s32 arg2);
/* audioGeomNodeCmd, geomBufWriteGetter — installed as callbacks into dest->unk4/unk28 */
extern void audioGeomNodeCmd(void);
extern void geomBufWriteGetter(void);

void audioGeomNodeInit(Unk *arg0, Unk *arg1, void *arg2) {
    /* nonmatching: FPU vertex loop — see asm/main/main/audioGeomNodeInit.s */
    s32 *tbl;
    u8 sel;

    /* Install callbacks and init dest object */
    arg0->unk4  = (s32)audioGeomNodeCmd;
    arg0->unk28 = (s32)geomBufWriteGetter;
    audioNodeInit(arg0, (void *)0, (void *)audioNodeSetValue, 5);

    /* Select geometry data table from arg1->unk1C (1-6) */
    sel = *(u8 *)((char *)arg1 + 0x1C);
    switch ((u32)(sel - 1)) {
    case 0:  tbl = gMidiSampleTblA;                               break;
    case 1:  tbl = gMidiSampleTblB;                               break;
    case 2:  tbl = gMidiSampleTblC;                               break;
    case 3:  tbl = gMidiSampleTblD;                               break;
    case 4:  tbl = gMidiSampleTblE;                               break;
    case 5:  tbl = *(s32 **)((char *)arg1 + 0x20);          break;
    default: tbl = gMidiSampleTblF;                               break;
    }

    /* nonmatching: FPU vertex/strip loop over tbl[].
     * Reads count from tbl[0], converts geometry to floats,
     * calls audioHeapAlloc / audioFillDecayTable per strip.
     * See asm stub for full implementation. */
    (void)tbl;
    (void)arg2;
}
