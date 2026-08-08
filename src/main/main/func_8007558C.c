#include "ultra64.h"
s32 __osPiRawReadIo(s32*);                               /* extern */
void piReadBytes(s32, s8*, u32);                     /* extern */
void piCopyBytes(s32, s32, u32);                     /* extern */
void piWriteBytes(s32, u8*, u32);                     /* extern */
void piSetBytes(s32, s32, u32);                       /* extern */
void piMoveBytes(s32, s32, s32);                     /* extern */
extern u32 gSramBlockTable;
extern s32 gSramBlockMap;
extern s32 gSramPhysBase;

void sramBlockRead(s32 arg0) {
    s32 temp_a0;
    s32 temp_v1;
    s32 var_a0;
    s32 var_v1;
    u32 var_a0_2;
    u32 var_a1;
    u32 var_s0;
    u32 var_s1;
    u32 var_s2;
    u32 var_s3;

    var_s2 = 0xB1FE0000;
    var_s1 = __osPiRawReadIo(0xB1FFFFF4);
    var_s3 = __osPiRawReadIo(0xB1FFFFF8);
    if (var_s1 > 0xEFFFFFFFU) {
        var_s1 = (u32) (var_s1 + &gSramPhysBase);
    }
    if (var_s3 != 0) {
        do {
            var_a0 = 0;
            if ((u32) gSramBlockTable < var_s1) {
                var_v1 = 0;
                do {
                    var_v1 += 8;
                    var_a0 += 1;
                } while ((u32) *(&gSramBlockTable + var_v1) < var_s1);
            }
            temp_a0 = var_a0 * 8;
            var_s0 = *(&gSramBlockTable + temp_a0) - (var_s1 - 1);
            if (var_s3 < var_s0) {
                var_s0 = var_s3;
            }
            temp_v1 = *(&gSramBlockMap + temp_a0);
            if (temp_v1 & arg0) {
                if (temp_v1 & 4) {
                    var_a0_2 = var_s1;
                    if (arg0 == 1) {
                        var_a0_2 = var_s2;
                        var_a1 = var_s1;
                    } else {
                        var_a1 = var_s2;
                    }
                    piMoveBytes(var_a0_2, var_a1, var_s0);
                    var_s2 += var_s0;
                } else if (arg0 == 1) {
                    piWriteBytes(var_s2, var_s1, var_s0);
                    var_s2 += var_s0;
                } else if (temp_v1 & 8) {
                    piCopyBytes(var_s2, var_s1, var_s0);
                    var_s2 += var_s0;
                } else {
                    piReadBytes(var_s2, var_s1, var_s0);
                    goto block_23;
                }
            } else if (arg0 == 1) {
                piSetBytes(var_s2, 0, var_s0);
                var_s2 += var_s0;
            } else {
block_23:
                var_s2 += var_s0;
            }
            var_s3 -= var_s0;
            var_s1 += var_s0;
        } while (var_s3 != 0);
    }
}
