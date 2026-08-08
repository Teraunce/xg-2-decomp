#include "ultra64.h"
void audioDefaultNoteSlot(Unk*, s32);                       /* extern */

void audioNoteClearAll(Unk *arg0) {
    s32 var_s0;
    s32 var_s2;

    var_s0 = 0;
    var_s2 = 0;
    if ((s32) arg0->unk34 > 0) {
        do {
            *(Unk**)(s32)(arg0->unk60 + var_s2) = (Unk*)0;
            audioDefaultNoteSlot(arg0, var_s0);
            var_s0 += 1;
            var_s2 += 0x10;
        } while (var_s0 < (s32) arg0->unk34);
    }
}
