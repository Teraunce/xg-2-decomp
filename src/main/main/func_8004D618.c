#include "ultra64.h"
void func_8004D138(s32, s32, s32);                    /* extern */
void func_8005BDB4(void);                              /* extern */

void func_8004D618(s32 arg0, s32 *arg1) {
    func_8004D138(arg0, arg1, 0x10);
    func_8005BDB4();
}
