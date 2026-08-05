#include "ultra64.h"
s32 func_8007C5DC();                                  /* extern */
s32 osDisableInt();                                /* extern */
s32 osRestoreInt(s32);                               /* extern */
void func_8007D238(Unk *);                            /* extern */
extern Unk *__osAllThreadList;
extern char *__osRunningThread;

void func_8007C848(Unk *arg0) {
    s32 temp_s0;
    Unk *var_s1;
    char *var_s2;

    temp_s0 = osDisableInt();
    if (arg0 == NULL) {
        arg0 = __osRunningThread;
    } else if (arg0->unk10 != 1) {
        func_8007D238(arg0->unk8);
    }
    if (__osAllThreadList == arg0) {
        __osAllThreadList = __osAllThreadList->unkC;
    } else {
        var_s1 = __osAllThreadList;
        var_s2 = var_s1->unkC;
        if (var_s2 != NULL) {
loop_7:
            if ((void*)var_s2 == (void*)arg0) {
                var_s1->unkC = (s32) arg0->unkC;
            } else {
                var_s1 = var_s2;
                var_s2 = var_s1->unkC;
                if (var_s2 != NULL) {
                    goto loop_7;
                }
            }
        }
    }
    if ((void*)arg0 == (void*)__osRunningThread) {
        func_8007C5DC();
    }
    osRestoreInt(temp_s0);
}
