#include "ultra64.h"
typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
} UnkStruct_arg0;

void __osTimerSetCompare(s32, u32);                          /* extern */
u32 __osTimerEnqueue(UnkStruct_arg0*);                          /* extern */
extern s32 *gOSMsgQueuePtr;

s32 osSetTimerImpl(UnkStruct_arg0 *arg0, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    u32 sp1C;
    s32 sp18;
    s32 temp_ret;

    arg0->unk0 = 0;
    arg0->unk4 = 0;
    arg0->unkC = arg5;
    arg0->unk8 = arg4;
    if ((arg2 != 0) || (arg3 != 0)) {
        arg0->unk10 = arg2;
        arg0->unk14 = arg3;
    } else {
        arg0->unk10 = arg4;
        arg0->unk14 = arg5;
    }
    arg0->unk18 = arg6;
    arg0->unk1C = arg7;
    temp_ret = __osTimerEnqueue(arg0);
    sp18 = temp_ret;
    sp1C = (u32) (u64) temp_ret;
    if ((void*)(s32)*gOSMsgQueuePtr == (void*)arg0) {
        __osTimerSetCompare(sp18, sp1C);
    }
    return 0;
}
