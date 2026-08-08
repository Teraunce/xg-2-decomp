#include "ultra64.h"
/* Warning: missing "jr $ra" in last block of audioNodeCmdGetter (initial). */

char *audioNoteWriteCmd(Unk *arg0, s32 arg1, s32 arg2, s32 arg3, Unk *arg4) {
    s32 temp_v0;
    s32 var_s0;
    void **var_s1;
    Unk *temp_a0;
    Unk *temp_v0_2;
    char *var_s3;

    temp_v0 = arg2 * 2;
    arg4->unk0 = 0x02000440;
    arg4->unk4 = temp_v0;
    arg4->unk8 = 0x02000580;
    arg4->unkC = temp_v0;
    var_s0 = 0;
    var_s3 = arg4 + 0x10;
    if (arg0->unk14 > 0) {
        var_s1 = arg0->unk1C;
        do {
            temp_a0 = *var_s1;
            temp_v0_2 = ((s32(*)())(s32)temp_a0->unk4)(temp_a0, arg1, arg2, arg3, var_s3);
            temp_v0_2->unk0 = 0x08000000;
            temp_v0_2->unk4 = (s32) (temp_v0 & 0xFFFF);
            temp_v0_2->unkC = 0x06C00440;
            temp_v0_2->unk8 = 0x0C007FFF;
            temp_v0_2->unk14 = 0x08000580;
            temp_v0_2->unk10 = 0x0C007FFF;
            var_s0 += 1;
            var_s1 += 4;
            var_s3 = temp_v0_2 + 0x18;
        } while (var_s0 < arg0->unk14);
    }
    return var_s3;
}

s32 audioNodeCmd(void);  /* forward: GETTER_NOJR fallthrough */
void audioNodeCmdGetter(s32 arg1) {
    return audioNodeCmd();
}
