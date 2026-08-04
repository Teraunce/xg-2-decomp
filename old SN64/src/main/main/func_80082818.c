#include "ultra64.h"
void func_8007DA18(Unk*);                               /* extern */
void func_8007DA48(Unk*, void**);                          /* extern */

void func_80082818(s32 arg0, s32 arg1) {
    func_8007DA18(arg1);
    func_8007DA48(arg1, arg0 + 0x14);
}
