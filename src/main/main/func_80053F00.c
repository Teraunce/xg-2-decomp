#include "ultra64.h"
s32 sfxQueueCmd(s32, s32, s32, s32, s32);                   /* extern */
extern s32 gGameFlags;
extern s32 gInitStateFlags;
extern s32 gSfxInputMask;
extern s32 gSfxInputTable2;
extern s32 gTrackReady;
extern s32 gInputResetFlag;
extern s32 gInputToggle;
extern s32 gSceneReady;
extern s32 gInputLevel;
extern s32 gTrackTiltDir;
extern s32 gTrackTilt;
extern s32 gSfxInputTable;
extern s32 gInputInitDone;

void sfxProcessInput(s32 arg0) {
    s32 var_a0;
    s32 var_a2;
    s32 temp_a0;
    s32 var_v0;
    s32 var_v0_2;
    s8 temp_v1;
    u16 temp_v1_2;

    var_v0 = *((arg0 * 4) + &gSfxInputTable2);
    if (var_v0 < 0) {
        var_v0 = -var_v0;
    }
    if (var_v0 < 0x19) {
        temp_v1 = ((Unk*)((char*)&gSfxInputTable + (arg0 * 6)))->unk3;
        if (temp_v1 >= 0x19) {
            if (gTrackTilt > 0) {
                sfxQueueCmd(0x18, 0x3F800000, 0x10000, 0x40, 0);
                var_v0_2 = gTrackTilt - 0xFF;
                goto block_9;
            }
        } else if ((temp_v1 < -0x18) && (gTrackTilt < 0xFF)) {
            sfxQueueCmd(0x18, 0x3F800000, 0x10000, 0x40, 0);
            var_v0_2 = gTrackTilt + 0xFF;
block_9:
            gTrackTilt = var_v0_2;
        }
    }
    temp_v1_2 = *((arg0 * 6) + &gSfxInputTable);
    temp_a0 = temp_v1_2 & ~*((arg0 * 4) + &gSfxInputMask);
    if ((((temp_a0 & 0x20) && (temp_v1_2 & 0x10)) || ((temp_a0 & 0x10) && (temp_v1_2 & 0x20))) && (gGameFlags & 0x4000)) {
        sfxQueueCmd(0x19, 0x3F800000, 0x10000, 0x40, 0x20);
        gInputToggle = gInputToggle == 0;
        return;
    }
    if (*((arg0 * 6) + &gSfxInputTable) & ~*((arg0 * 4) + &gSfxInputMask) & 0x9000) {
        if (gInputLevel < 0x80) {
            var_a0 = 0xF;
            if (gTrackTilt < 0x80) {
                var_a2 = 0xC350;
                gTrackTiltDir = 0;
                goto block_27;
            }
            var_a0 = 0x19;
            var_a2 = 0x10000;
            gTrackReady = 0;
            gInputResetFlag = 0;
            gInputLevel = 0xFF;
            gTrackTilt = 0xFF;
        } else if (gTrackTilt < 0x80) {
            if (gInputInitDone == 0) {
                gInputInitDone = 1;
                if (gTrackReady == 0) {
                    gSceneReady = 1;
                }
            }
            var_a0 = 0x19;
            var_a2 = 0x10000;
            gInitStateFlags = 0;
        } else {
            var_a0 = 0xF;
            var_a2 = 0xC350;
            gTrackTiltDir = 0;
            gTrackReady = 0;
block_27:
            gInitStateFlags = 0;
        }
        sfxQueueCmd(var_a0, 0x3F800000, var_a2, 0x40, 0);
    }
}
