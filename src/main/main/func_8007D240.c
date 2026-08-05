#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of func_8007D304 (initial). */

extern Unk *D_800952C0;
extern s32 D_80189A8C;
extern s32 D_80189A90;
extern s32 D_80189A94;

void func_8007D240(void **arg1, char *arg2, char *arg3) {
    char *var_a2;
    char *var_a3;

    var_a2 = arg2;
    var_a3 = arg3;
    if (var_a3 != NULL) {
loop_1:
        if ((void*)var_a3 == (void*)arg1) {
            *var_a2 = *arg1;
            return;
        }
        var_a2 = var_a3;
        var_a3 = *var_a2;
        if (var_a3 == NULL) {

        } else {
            goto loop_1;
        }
    }
}

void func_8007D278(void) {
    D_80189A8C = 0;
    D_80189A8C = 0;
    D_80189A90 = 0;
    D_80189A94 = 0;
    D_800952C0->unk4 = (void *) D_800952C0;
    D_800952C0->unk0 = (void *) D_800952C0->unk4;
    D_800952C0->unk10 = 0;
    D_800952C0->unk14 = 0;
    D_800952C0->unk8 = (s32) D_800952C0->unk10;
    D_800952C0->unkC = (s32) D_800952C0->unk14;
    D_800952C0->unk18 = 0;
    D_800952C0->unk1C = 0;
}

void func_8007D304(void) {

}
