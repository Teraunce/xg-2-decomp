#include "ultra64.h"
s32 sfxFreeBlock(s32);                             /* extern */
s32 sfxDispatchSample(s32, s32);                          /* extern */
extern s32 gSfxDefTable;

s32 sfxLoadSample(u32 arg0) {
    s32 temp_v0;

    if (arg0 < (u32)(s32)0 /* implicit $v0 from caller */) {
        temp_v0 = sfxFreeBlock(((Unk*)(s32)((arg0 * 0x10) + gSfxDefTable))->unk8);
        if (temp_v0 != 0) {
            sfxDispatchSample(arg0, temp_v0);
            return temp_v0;
        }
    }
    return 0;
}
