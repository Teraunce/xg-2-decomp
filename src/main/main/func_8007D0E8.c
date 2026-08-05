#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8007D238 (initial). */

s32 func_8007C484(void **);                           /* extern */
s32 func_8007C584(void **, void *);                   /* extern */
char *func_8007C5CC(void **);                       /* extern */
s32 func_8007C5DC();                                  /* extern */
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
extern Unk *__osRunQueue;
extern Unk *__osRunningThread;

void func_8007D0E8(Unk *arg0) {
    s32 temp_s0;
    u16 temp_s1;
    void **temp_t0;

    temp_s0 = osDisableInt();
    temp_s1 = arg0->unk10;
    if (temp_s1 != 1) {
        if (temp_s1 == 8) {
            arg0->unk10 = 2U;
            func_8007C584(&__osRunQueue, arg0);
        }
    } else {
        temp_t0 = arg0->unk8;
        if ((temp_t0 == NULL) || ((void*)temp_t0 == (void*)&__osRunQueue)) {
            arg0->unk10 = 2U;
            func_8007C584(&__osRunQueue, arg0);
        } else {
            arg0->unk10 = 8U;
            func_8007C584(arg0->unk8, arg0);
            func_8007C584(&__osRunQueue, func_8007C5CC(arg0->unk8));
        }
    }
    if (__osRunningThread == NULL) {
        func_8007C5DC();
    } else if (__osRunningThread->unk4 < __osRunQueue->unk4) {
        __osRunningThread->unk10 = 2;
        func_8007C484(&__osRunQueue);
    }
    osRestoreInt(temp_s0);
}

void func_8007D238(Unk *arg0) {

}
