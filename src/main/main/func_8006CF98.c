#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of gameLoopDispatchGetter (initial). */

s32 osVirtualToPhysical(u32);                       /* extern */
extern s32 gTrackNodeCount;
extern s32 gPendingEventFlag;
extern s32 gRspCamDL;
extern s32 gTexTileCmd;
extern s32 gCamSetupDL;
extern s32 gRspDLSize;
extern s32 gRspDL;
extern s32 gRspGeomBufEnd;
extern s32 gScreenHeight;
extern Unk *gDLPtr;
extern s32 gLineVtxBase;
extern s32 gHiliteIdx;
extern s32 gGfxRenderBufBase;
extern s32 *gRenderParam;
extern s32 gRspDLCached;
extern s32 gScreenWidth;

void gfxDLFrameSetup(Unk *arg0) {
    s32 *temp_a1;
    Unk *temp_a1_3;
    Unk *temp_s0;
    Unk *temp_s0_2;
    Unk *temp_s0_3;
    Unk *temp_v1_2;
    Unk *temp_v1_3;
    Unk *temp_v1_4;
    s32 temp_a1_2;
    s32 temp_v1;

    temp_a1 = arg0 + 0x58;
    gRenderParam = temp_a1;
    temp_v1 = arg0 + 0x10DE0;
    gRspGeomBufEnd = temp_v1;
    gDLPtr = temp_a1;
    temp_a1_2 = arg0->unk1F540;
    gLineVtxBase = temp_v1;
    gHiliteIdx = 0;
    gDLPtr = arg0 + 0x60;
    arg0->unk58 = 0xDB060000;
    gDLPtr = arg0 + 0x68;
    arg0->unk5C = 0;
    arg0->unk60 = 0xDB060004;
    gRspDLCached = gRspDL;
    gRspDLSize = temp_a1_2;
    arg0->unk64 = osVirtualToPhysical(gRspCamDL);
    temp_v1_2 = gDLPtr;
    temp_s0 = gDLPtr + 8;
    temp_v1_2->unk4 = &gCamSetupDL;
    gDLPtr = temp_s0;
    gDLPtr = temp_s0 + 8;
    temp_v1_2->unk0 = 0xDE000000;
    temp_s0->unk4 = &gTexTileCmd;
    gDLPtr = temp_s0 + 0x10;
    gDLPtr->unk8 = 0xDE000000;
    temp_s0->unk8 = 0xFE000000;
    temp_s0->unkC = osVirtualToPhysical(gRspDL);
    if (gPendingEventFlag != 0) {
        temp_v1_3 = gDLPtr;
        temp_s0_2 = gDLPtr + 8;
        temp_v1_3->unk0 = 0xE7000000;
        gDLPtr = temp_s0_2;
        gDLPtr = temp_s0_2 + 8;
        temp_v1_3->unk4 = 0;
        temp_s0_2->unk4 = 0x300000;
        gDLPtr = temp_s0_2 + 0x10;
        gDLPtr->unk8 = 0xE3000A01;
        temp_s0_2->unk8 = (s32) (((gScreenWidth - 1) & 0xFFF) | 0xFF100000);
        temp_s0_2->unkC = osVirtualToPhysical(gRspDL);
        temp_v1_4 = gDLPtr;
        temp_a1_3 = gDLPtr + 8;
        temp_v1_4->unk0 = 0xF7000000;
        gDLPtr = temp_a1_3;
        gDLPtr = temp_a1_3 + 8;
        temp_v1_4->unk4 = 0xFFFCFFFC;
        temp_a1_3->unk4 = 0;
        gDLPtr->unk8 = (s32) ((((gScreenWidth - 1) & 0x3FF) << 0xE) | ((((gScreenHeight - 1) & 0x3FF) * 4) | 0xF6000000));
    }
    temp_s0_3 = gDLPtr + 8;
    gDLPtr->unk0 = 0xE7000000;
    gDLPtr->unk4 = 0;
    gDLPtr->unk8 = (s32) (((gScreenWidth - 1) & 0xFFF) | 0xFF100000);
    gDLPtr = temp_s0_3;
    gDLPtr = temp_s0_3 + 8;
    temp_s0_3->unk4 = osVirtualToPhysical(arg0->unk1F540);
}

void gameLoopDispatch(void);  /* forward: GETTER_NOJR fallthrough */
void gameLoopDispatchGetter(void) {
    gameLoopDispatch();
}
