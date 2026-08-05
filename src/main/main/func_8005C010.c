#include "ultra64.h"
void __osTimerUnlink(Unk*);                            /* extern */
void __osTimerInsert(Unk*, void**);                    /* extern */
extern u32 D_801816A8;
extern Unk D_80181E30;

void func_8005C010(void) {
    char *temp_s1;
    Unk *var_s0;

    var_s0 = D_80181E30.unk4;
    if (var_s0 != NULL) {
        do {
            temp_s1 = var_s0->unk0;
            if ((u32) (var_s0->unkC + 2) < (u32) D_801816A8) {
                if ((Unk *)D_80181E30.unk4 == var_s0) {
                    D_80181E30.unk4 = temp_s1;
                }
                __osTimerUnlink(var_s0);
                if (D_80181E30.unk8 == 0) {
                    D_80181E30.unk8 = var_s0;
                    var_s0->unk0 = 0;
                    var_s0->unk4 = 0;
                    goto block_10;
                }
                __osTimerInsert(var_s0, D_80181E30.unk8);
                var_s0 = temp_s1;
            } else {
block_10:
                var_s0 = temp_s1;
            }
        } while (var_s0 != NULL);
    }
}
