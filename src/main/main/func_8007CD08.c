#include "ultra64.h"
s32 func_8007C484(void *);                            /* extern */
s32 func_8007C5CC(void *);                          /* extern */
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
void func_8007D0E8(Unk*);                               /* extern */
extern Unk *__osRunningThread;

s32 func_8007CD08(Unk *arg0, s32 *arg1, s32 arg2) {
    s32 temp_s0;

    temp_s0 = osDisableInt();
    if (arg0->unk8 == 0) {
loop_1:
        if (arg2 == 0) {
            osRestoreInt(temp_s0);
            return -1;
        }
        __osRunningThread->unk10 = 8;
        func_8007C484(arg0);
        if (arg0->unk8 != 0) {
            goto block_4;
        }
        goto loop_1;
    }
block_4:
    if (arg1 != NULL) {
        *arg1 = *(s32*)((s32)arg0->unk14 + (arg0->unkC * 4));
    }
    arg0->unkC = (s32) ((s32) (arg0->unkC + 1) % (s32) arg0->unk10);
    arg0->unk8 = (s32) (arg0->unk8 - 1);
    if (((Unk*)(s32)arg0->unk0)->unk4 != 0) {
        func_8007D0E8(func_8007C5CC(arg0 + 4));
    }
    osRestoreInt(temp_s0);
    return 0;
}
