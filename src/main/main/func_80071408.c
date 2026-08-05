#include "ultra64.h"
void func_80061A9C(s8*, s8, s32);                        /* extern */
s32 memcmp(u8 *, u8 *, s32);                   /* extern */
s32 contPakAllocNote(Unk*, u16, s32, u8*, u8*, s32, s32*); /* extern */
s32 contPakLoadSave(Unk*, u16, s32, s32, s32);       /* extern */
s32 contPakWriteNote(Unk*, s32, u8, s32, s32, char*);    /* extern */
s32 contPakReadNote(void *, u16, s32, s32, s32, s32*); /* extern */
extern u16 gContPakNoteCode;
extern s32 gGameID;
extern s8 D_80093EC8;
extern s32 D_80093ECC;
extern s32 D_8018894C;

s32 func_80071408(s32 arg0) {
    s32 sp68;
    s8 sp60;
    u8 sp40;
    u8 sp20;
    s32 temp_s5;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_s0;
    s32 var_s5;
    s32 var_v0;
    u8 *temp_v1;
    u8 *var_v0_2;
    u8 *var_v0_3;
    u8 temp_v0_3;
    u8 temp_v1_2;
    char *temp_s0;
    char *temp_s0_2;
    char *temp_s1;

    func_80061A9C(&sp60, 0, 4);
    temp_s1 = (arg0 * 0x68) + &D_8018894C;
    sp60 = 0x33;
    temp_v0 = contPakAllocNote(temp_s1, gContPakNoteCode, gGameID, &D_80093ECC, &sp60, 0x100, &sp68);
    if (temp_v0 < 9) {
        if (temp_v0 < 7) {
            var_s0 = arg0 * 2;
            if (temp_v0 != 0) {
                return 0;
            }
            goto block_8;
        }
        var_v0 = 1;
        if (contPakReadNote(temp_s1, gContPakNoteCode, gGameID, &D_80093ECC, &D_80093EC8, &sp68) == 0) {
            temp_v0_2 = contPakWriteNote(temp_s1, sp68, 0, 0, 0x20, &sp20);
            var_v0 = 1;
            if (temp_v0_2 != 6) {
                var_v0 = 0;
                if (temp_v0_2 == 0) {
                    var_s5 = 1;
                    var_a0 = 0;
                    var_v0_2 = &sp20;
                    do {
                        temp_v1 = &(&sp40)[var_a0];
                        temp_v0_3 = *var_v0_2 + var_a0;
                        var_a0 += 1;
                        *temp_v1 = temp_v0_3;
                        var_v0_2 = &(&sp20)[var_a0];
                    } while (var_a0 < 0x20);
                    temp_s0 = (arg0 * 0x68) + &D_8018894C;
                    if (contPakWriteNote(temp_s0, sp68, 1, 0, 0x20, &sp40) != 0) {
                        var_s5 = 0;
                    }
                    if (contPakWriteNote(temp_s0, sp68, 0, 0, 0x20, &sp40) != 0) {
                        var_s5 = 0;
                    }
                    if (contPakWriteNote(temp_s0, sp68, 1, 0, 0x20, &sp20) != 0) {
                        var_s5 = 0;
                    }
                    var_a0_2 = 0;
                    var_v0_3 = &sp20;
                    do {
                        temp_v1_2 = *var_v0_3 + var_a0_2;
                        var_a0_2 += 1;
                        *var_v0_3 = temp_v1_2;
                        var_v0_3 = &(&sp20)[var_a0_2];
                    } while (var_a0_2 < 0x20);
                    if (memcmp(&sp20, &sp40, 0x20) != 0) {
                        var_s5 = 0;
                    }
                    var_v0 = var_s5;
                }
            }
        }
        return var_v0;
    }
    if (temp_v0 != 9) {
        return 0;
    }
    var_s0 = arg0 * 2;
block_8:
    temp_s0_2 = ((((var_s0 + arg0) * 4) + arg0) * 8) + &D_8018894C;
    temp_s5 = contPakReadNote(temp_s0_2, gContPakNoteCode, gGameID, &D_80093ECC, &sp60, &sp68);
    contPakLoadSave(temp_s0_2, gContPakNoteCode, gGameID, &D_80093ECC, &sp60);
    return temp_s5 == 0;
}
