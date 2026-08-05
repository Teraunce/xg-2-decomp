#include "ultra64.h"
s32 frameAlloc(s32, s32 *);                        /* extern */
extern s32 gRSPTaskB;

void heap_alloc(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    s32 *var_a3;
    s32 temp_a0;
    s32 var_a2;

    var_a2 = arg2;
    var_a3 = arg3;
    if (arg1 != 0) {
        var_a3 = &gRSPTaskB;
        var_a2 = gRSPTaskB;
        if (var_a2 >= arg0) {
            temp_a0 = (arg0 + 0xF) & ~0xF;
            /* implicit $t0 (heap header ptr from caller)->unkD00 = arg1 + temp_a0 (nonmatching) */
        ((Unk*)0)->unkD00 = (s32) (arg1 + temp_a0);
            gRSPTaskB = var_a2 - temp_a0;
            return;
        }
    }
    frameAlloc(var_a2, var_a3);
}
