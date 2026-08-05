#include "ultra64.h"
s32 func_8007DD1C();                                /* extern */

void func_8007E074(Unk *arg0, char *arg1) {
    f32 var_ft2;
    s32 temp_t7;
    s32 temp_v0;
    s32 var_s2;
    s32 var_t5;
    Unk *var_s1;
    Unk *var_t4;

    arg0->unk0 = arg1;
    arg0->unk4 = 0;
    arg0->unk10 = 0;
    arg0->unkC = 0;
    arg0->unk14 = 1;
    var_s1 = arg0;
    var_s2 = 0;
    var_t5 = 0;
    var_t4 = arg0;
    do {
        var_s1->unkA8 = 0;
        var_t4->unk58 = 0;
        var_s1->unk98 = 0;
        temp_v0 = *((char*)(s32)arg0->unk0 + var_s2);
        if (temp_v0 != 0) {
            arg0->unk4 = (s32) (arg0->unk4 | (1 << var_t5));
            var_t4->unk18 = (s32) (arg1 + temp_v0);
            var_t4 /* loop feedback: previous var_t4 value in $t4 */->unkB8 = func_8007DD1C();
        } else {
            var_t4->unk18 = 0;
        }
        var_t5 = (s32)var_t5 /* loop feedback: previous var_t5 value in $t5 */ + 1;
        var_s1 += 1;
        var_s2 += 4;
        var_t4 = (s32)var_t4 /* loop feedback: previous var_t4 value in $t4 */ + 4;
    } while (var_t5 != 0x10);
    temp_t7 = ((Unk *)arg0->unk0)->unk40;
    var_ft2 = (f32) temp_t7;
    if (temp_t7 < 0) {
        var_ft2 += 4294967296.0f;
    }
    arg0->unk8 = (f32) (1.0 / (f64) var_ft2);
}
