#include "ultra64.h"
void osInvalICache(u32, s32);                              /* extern */
void osWritebackDCache(u32, s32);                              /* extern */
s32 osEPiRawReadIo(s32, s32 *);                        /* extern */
s32 osEPiRawWriteIo(s32, s32);                          /* extern */
void osEPiRawReadIoCart(s32, u32 *);                          /* extern */
void bzero(s32, s32);                            /* extern */
u32 __udivdi3(s32, u32, s32, s32);                  /* extern */
s32 __muldi3(u32, s32, s32, s32);                  /* extern */
s32 __osGetSR();                                /* static */
s32 __osGetFpcsr(s32);                               /* static */
void __osSetSR(s32);                            /* static */
void __osInitTLB();                               /* static */
extern s32 D_80000000;
extern s32 osMemSize;
extern s32 osResetType;
extern s32 osVersion;
extern u32 gCpuClockHi;
extern s32 gCpuClock;
extern s32 gAiClock;
extern s32 D_80189828;
extern Unk __osException;

void osInitialize(void) {
    s32 sp34;
    u32 sp30;
    u32 sp24;
    s32 sp20;
    s32 temp_ret;
    u32 temp_ret_2;
    u32 temp_t9;

    sp30 = 0;
    D_80189828 = 1;
    __osSetSR(__osGetSR() | 0x20000000);
    __osGetFpcsr(0x01000800);
    if (osEPiRawReadIo(0x1FC007FC, &sp34) != 0) {
        do {

        } while (osEPiRawReadIo(0x1FC007FC, &sp34) != 0);
    }
    if (osEPiRawWriteIo(0x1FC007FC, sp34 | 8) != 0) {
        do {

        } while (osEPiRawWriteIo(0x1FC007FC, sp34 | 8) != 0);
    }
    D_80000000 = __osException.unk0;
    D_80000000 = __osException.unk4;
    D_80000000 = __osException.unk8;
    D_80000000 = __osException.unkC;
    (( Unk*)0x80000080)->unk0 = (s32) __osException.unk0;
    (( Unk*)0x80000080)->unk4 = (s32) __osException.unk4;
    (( Unk*)0x80000080)->unk8 = (s32) __osException.unk8;
    (( Unk*)0x80000080)->unkC = (s32) __osException.unkC;
    (( Unk*)0x80000100)->unk0 = (s32) __osException.unk0;
    (( Unk*)0x80000100)->unk4 = (s32) __osException.unk4;
    (( Unk*)0x80000100)->unk8 = (s32) __osException.unk8;
    (( Unk*)0x80000100)->unkC = (s32) __osException.unkC;
    (( Unk*)0x80000180)->unk0 = (s32) __osException.unk0;
    (( Unk*)0x80000180)->unk4 = (s32) __osException.unk4;
    (( Unk*)0x80000180)->unk8 = (s32) __osException.unk8;
    (( Unk*)0x80000180)->unkC = (s32) __osException.unkC;
    osWritebackDCache(0x80000000, 0x190);
    osInvalICache(0x80000000, 0x190);
    __osInitTLB();
    osEPiRawReadIoCart(4, &sp30);
    temp_t9 = sp30 & ~0xF;
    sp30 = temp_t9;
    if (temp_t9 != 0) {
        gCpuClockHi = 0;
        gCpuClockHi = temp_t9;
    }
    temp_ret = __muldi3(gCpuClockHi, gCpuClock, 0, 3);
    sp20 = temp_ret;
    sp24 = (u32) (u64) temp_ret;
    temp_ret_2 = __udivdi3(sp20, sp24, 0, 4);
    gCpuClockHi = temp_ret_2;
    gCpuClockHi = (u32) (u64) temp_ret_2;
    if (osResetType == 0) {
        bzero(&osVersion, 0x40);
    }
    if (osMemSize == 0) {
        gAiClock = 0x02F5B2D2;
        return;
    }
    if (osMemSize == 2) {
        gAiClock = 0x02E6025C;
        return;
    }
    gAiClock = 0x02E6D354;
}

/* __osGetSR — read COP0 Status register (mfc0 $v0, $12) */
s32 __osGetSR(void) {
    return 0; /* mfc0 $v0, $12 */
}

/* __osGetFpcsr — read FPU control register (cfc1 $v0, $31) */
s32 __osGetFpcsr(s32 arg0) {
    return 0; /* cfc1 $v0, $31 */
}

/* __osSetSR — write COP0 Status register (mtc0 $a0, $12) */
void __osSetSR(s32 arg0) {
    /* mtc0 $a0, $12 — write COP0 Status */
}

/* __osInitTLB — write TLB entry (COP0 TLB setup + tlbwi) */
void __osInitTLB(void) {
    /* mtc0 $t1, $0   — write COP0 Index    */
    /* mtc0 $zero, $5 — write COP0 PageMask */
    /* mtc0 $t1, $10  — write COP0 EntryHi  */
    /* mtc0 $t3, $2   — write COP0 EntryLo0 */
    /* mtc0 $t1, $3   — write COP0 EntryLo1 */
    /* tlbwi          — TLB write indexed   */
    /* mtc0 $t0, $10  — restore EntryHi     */
}
