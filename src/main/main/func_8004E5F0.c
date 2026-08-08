#include "ultra64.h"
s32 *overlayDecompress(void *);                            /* extern */
extern s32 D_8004B7B0;
extern s32 D_8004B8A0;
extern s32 D_80173C70;

void overlayLoadEntry(s32 arg0, Unk *arg1) {
    s32 temp_v0;

    if ((arg0 >= 0xD) && (D_80173C70 == 0)) {
        D_80173C70 = *overlayDecompress(&D_8004B8A0);
    }
    temp_v0 = *overlayDecompress((arg0 * 0x10) + &D_8004B7B0);
    arg1->unk64C = 0;
    arg1->unkC = temp_v0;
}
