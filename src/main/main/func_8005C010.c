#include "ultra64.h"
void __osTimerUnlink(Unk*);                            /* extern */
void __osTimerInsert(Unk*, void**);                    /* extern */
extern u32 gAudioFrameCount;
extern Unk gSfxBufList;

void audioBufRecycle(void) {
    char *temp_s1;
    Unk *var_s0;

    var_s0 = gSfxBufList.unk4;
    if (var_s0 != NULL) {
        do {
            temp_s1 = var_s0->unk0;
            if ((u32) (var_s0->unkC + 2) < (u32) gAudioFrameCount) {
                if ((Unk *)gSfxBufList.unk4 == var_s0) {
                    gSfxBufList.unk4 = temp_s1;
                }
                __osTimerUnlink(var_s0);
                if (gSfxBufList.unk8 == 0) {
                    gSfxBufList.unk8 = var_s0;
                    var_s0->unk0 = 0;
                    var_s0->unk4 = 0;
                    goto block_10;
                }
                __osTimerInsert(var_s0, gSfxBufList.unk8);
                var_s0 = temp_s1;
            } else {
block_10:
                var_s0 = temp_s1;
            }
        } while (var_s0 != NULL);
    }
}
