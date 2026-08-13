#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of heap_alloc_default (initial). */

void osWritebackInvalDCache(u32, s32);                         /* extern */
void __osInvalICache_full(void);                             /* extern */
s32 spTaskSubmit(Unk*, s32, s32, s32, s32, s32, s32);    /* extern */
extern char *gDLWritePtr;
extern char *gDLBase;
extern s32 gRSPTaskA;
extern s32 gRSPTaskB;
extern char *gFrameWait;
extern s32 gFrameState;
extern char *gDLSavePtr;
extern u8 gRspGeomBuf;
extern s32 gRspDmaMesgQueue;
extern s32 gDLWriteBuf;
extern s32 gDLBufEnd;

void rspReadBytes(s32 arg0, u8 *arg1, s32 arg2) {
    s32 sp38;
    s32 sp20;
    s32 temp_a1;
    s32 temp_s4;
    s32 var_s2;
    s32 var_s3;
    s32 var_v1;
    u8 *var_s1;
    u8 temp_v0;
    u8 temp_v0_2;

    var_s3 = arg0;
    var_s2 = arg2;
    var_s1 = arg1;
    temp_s4 = var_s3 & 0x3F;
    if (temp_s4 != 0) {
        osWritebackInvalDCache(&gRspGeomBuf, 0x40);
        spTaskSubmit(&sp20, 0, 0, var_s3 & ~0x3F, &gRspGeomBuf, 0x40, &gRspDmaMesgQueue);
        osRecvMesg(&gRspDmaMesgQueue, &sp38, 1);
        temp_a1 = var_s2 + temp_s4;
        var_v1 = temp_s4;
        if (temp_a1 < 0x41) {
            if (var_v1 < temp_a1) {
                do {
                    temp_v0 = (&gRspGeomBuf)[var_v1];
                    var_v1 += 1;
                    *var_s1 = temp_v0;
                    var_s1 += 1;
                } while (var_v1 < temp_a1);
            }
        } else {
            if (var_v1 < 0x40) {
                do {
                    var_s2 -= 1;
                    var_s3 += 1;
                    temp_v0_2 = (&gRspGeomBuf)[var_v1];
                    var_v1 += 1;
                    *var_s1 = temp_v0_2;
                    var_s1 += 1;
                } while (var_v1 < 0x40);
            }
            __osInvalICache_full();
            goto block_8;
        }
    } else {
block_8:
        osWritebackInvalDCache(var_s1, var_s2);
        spTaskSubmit(&sp20, 0, 0, var_s3, var_s1, var_s2, &gRspDmaMesgQueue);
        osRecvMesg(&gRspDmaMesgQueue, &sp38, 1);
    }
}

void func_8004D330(void) {
    gDLSavePtr = gDLWritePtr;
}

void func_8004D344(void) {
    gDLWritePtr = gDLSavePtr;
}

void dlResetPtr(void) {
    if (gDLBase != NULL) {
        gDLWritePtr = gDLBase;
        return;
    }
    gDLWritePtr = &gDLWriteBuf;
}

char *gfxGetWritePtr(void) {
    if (gFrameWait == NULL) {
        return gDLWritePtr;
    }
    return gFrameWait;
}

void func_8004D3A8(s32 arg0, s32 arg1) {
    s32 temp_v0_2;
    s32 var_v1;
    s8 *temp_v0;

    var_v1 = 0;
    gRSPTaskA = arg0;
    gRSPTaskB = arg1;
    if (arg1 > 0) {
        do {
            temp_v0 = gRSPTaskA + var_v1;
            var_v1 += 1;
            *temp_v0 = 0;
        } while (var_v1 < arg1);
    }
    if (gRSPTaskA & 0xF) {
        do {
            temp_v0_2 = gRSPTaskA + 1;
            gRSPTaskA = temp_v0_2;
            gRSPTaskB -= 1;
        } while (temp_v0_2 & 0xF);
    }
}

void rspResetCounters(void) {
    gRSPTaskA = 0;
    gRSPTaskB = 0;
}

char *frameAlloc(s32 arg0) {
    char *temp_a0_2;
    char *temp_v0;
    char *temp_v0_2;
    s32 temp_a0;

    temp_a0 = (arg0 + 0xF) & ~0xF;
    if ((gFrameWait != NULL) && (gFrameState >= temp_a0)) {
        temp_v0_2 = gFrameWait;
        gFrameWait = temp_v0_2 + temp_a0;
        gFrameState -= temp_a0;
        return temp_v0_2;
    }
    temp_a0_2 = gDLWritePtr + temp_a0;
    temp_v0 = gDLWritePtr;
    if ((s32) &gDLBufEnd >= (s32) temp_a0_2) {
        gDLWritePtr = temp_a0_2;
        return temp_v0;
    }
    return NULL;
}

void heap_alloc_default(void) {

}
