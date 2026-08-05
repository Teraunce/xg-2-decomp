#include "ultra64.h"
s32 func_8007C484(void **);                           /* extern */
s32 func_8007C584(s32, void *);                       /* extern */
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
void func_8007D238(Unk *);                            /* extern */
extern Unk *__osRunQueue;
extern Unk *__osRunningThread;

void func_8007D008(Unk *arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = osDisableInt();
    if (arg0 == NULL) {
        arg0 = __osRunningThread;
    }
    if (arg0->unk4 != arg1) {
        arg0->unk4 = arg1;
        if ((arg0 != __osRunningThread) && (arg0->unk10 != 1)) {
            func_8007D238(arg0->unk8);
            func_8007C584(arg0->unk8, arg0);
        }
        if (__osRunningThread->unk4 < __osRunQueue->unk4) {
            __osRunningThread->unk10 = 2;
            func_8007C484(&__osRunQueue);
        }
    }
    osRestoreInt(temp_s0);
}
