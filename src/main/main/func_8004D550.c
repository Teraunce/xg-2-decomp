#include "ultra64.h"
void gfxSpTaskWait(s32, s32, s32);                    /* extern */
s32 heap_alloc_default(s32);                             /* extern */
void func_8005BDD0(void);                              /* extern */
extern s32 D_80192880;

s32 func_8004D550(s32 arg0) {
    s32 temp_s1;
    s32 temp_v0;

    gfxSpTaskWait(arg0, &D_80192880, 0x10);
    temp_s1 = D_80192880;
    temp_v0 = heap_alloc_default(temp_s1);
    func_8005BDD0();
    return temp_v0;
}
