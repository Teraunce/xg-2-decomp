#include "ultra64.h"
s32 func_8006216C(void *);                             /* extern */
void func_80070BCC(s32, s32);                        /* extern */
extern s32 gHandlerTable;

void func_80070C88(s32 arg0, s32 arg1) {
    if (func_8006216C(&gHandlerTable) == 0) {
        func_80070BCC(2, arg1);
    }
}
