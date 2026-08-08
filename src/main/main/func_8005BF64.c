#include "ultra64.h"
s32 heap_alloc_default(s32);                               /* extern */
void __osTimerInsert(Unk*, void**);                       /* extern */
extern s32 D_801816B0;
extern Unk D_80181E30;
extern s32 audioDmaBufAlloc;

char *audioDmaBufInit(void **arg0) {
    Unk *var_s0;
    s32 var_s2;
    char *var_s1;

    if (D_80181E30.unk0 == 0) {
        D_80181E30.unk8 = &D_801816B0;
        var_s2 = 0;
        var_s0 = &D_801816B0;
        var_s1 = &D_801816B0 + 0x14;
        do {
            __osTimerInsert(var_s1, var_s0);
            var_s0->unk10 = heap_alloc_default(0x300);
            var_s0 += 0x14;
            var_s2 += 1;
            var_s1 += 0x14;
        } while (var_s2 < 0x5F);
        D_80181E30.unk0 = 1U;
    }
    *arg0 = &D_80181E30;
    return &audioDmaBufAlloc;
}
