#include "ultra64.h"
s32 func_8007C484(void *);                            /* extern */
s32 func_8007C5CC(void *);                          /* extern */
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
void func_8007D0E8(Unk*);                               /* extern */
extern Unk *__osRunningThread;

s32 func_8007CE48(Unk *arg0, s32 arg1, s32 arg2) {
    s32 temp_s0;

    temp_s0 = osDisableInt();
    if (arg0->unk8 >= arg0->unk10) {
loop_1:
        if (arg2 == 1) {
            __osRunningThread->unk10 = 8;
            func_8007C484(arg0 + 4);
            if (arg0->unk8 < arg0->unk10) {
                goto block_5;
            }
            goto loop_1;
        }
        osRestoreInt(temp_s0);
        return -1;
    }
block_5:
    *(s32*)((s32)arg0->unk14 + (((s32) (arg0->unkC + arg0->unk8) % (s32) arg0->unk10) * 4)) = arg1;
    arg0->unk8 = (s32) (arg0->unk8 + 1);
    if (((Unk*)(s32)arg0->unk0)->unk0 != 0) {
        func_8007D0E8(func_8007C5CC(arg0));
    }
    osRestoreInt(temp_s0);
    return 0;
}
