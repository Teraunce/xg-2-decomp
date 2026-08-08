#include "ultra64.h"
s32 heap_alloc_default(s32);                               /* extern */
void __osTimerInsert(Unk*, void**);                       /* extern */
extern s32 gSfxBufPool;
extern Unk gSfxBufList;
extern s32 audioDmaBufAlloc;

char *audioDmaBufInit(void **arg0) {
    Unk *var_s0;
    s32 var_s2;
    char *var_s1;

    if (gSfxBufList.unk0 == 0) {
        gSfxBufList.unk8 = &gSfxBufPool;
        var_s2 = 0;
        var_s0 = &gSfxBufPool;
        var_s1 = &gSfxBufPool + 0x14;
        do {
            __osTimerInsert(var_s1, var_s0);
            var_s0->unk10 = heap_alloc_default(0x300);
            var_s0 += 0x14;
            var_s2 += 1;
            var_s1 += 0x14;
        } while (var_s2 < 0x5F);
        gSfxBufList.unk0 = 1U;
    }
    *arg0 = &gSfxBufList;
    return &audioDmaBufAlloc;
}
