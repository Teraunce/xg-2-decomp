#include "ultra64.h"
s32 audioLoadBank(s32);                               /* extern */
s32 audioLoadWavetable(s32);                               /* extern */
void audioDecodeHufh(s32, u8*, u32);                     /* extern */
void sfxUpdateChannels();                                  /* extern */
void osWritebackInvalDCache(u32, s32);                          /* extern */
void osInvalICache(u32, s32);                          /* extern */
void __osInvalICache_full();                                  /* extern */
s32 func_8009F528(s32);                                 /* extern */
s32 func_800AE1C8();                                  /* extern */
s32 func_800AE368(s32);                                 /* extern */
extern s32 D_31880;
extern s32 gAudioHufTableRom;
extern s32 gAudioHufDst;
extern s8 gRenderStateA;
extern Unk gAudioTrackBuf;
extern s8 gRenderStateB;
extern Unk gAudioTrackBuf2;

void audioBootDecode(void) {
    s32 *var_a1;
    s32 *var_v1;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_a0;
    s32 var_a0_2;
    s8 *temp_v0;
    s8 *temp_v1;

    __osInvalICache_full();
    osWritebackInvalDCache(&gAudioHufDst, &D_31880);
    osInvalICache(&gAudioHufDst, &D_31880);
    audioDecodeHufh(gAudioHufTableRom + 0x18, &gAudioHufDst, &D_31880);
    __osInvalICache_full();
    osWritebackInvalDCache(&gAudioHufDst, &D_31880);
    osInvalICache(&gAudioHufDst, &D_31880);
    func_8009F528(0x13);
    func_800AE1C8();
    var_a0 = 0;
    var_a1 = &gAudioTrackBuf2;
    var_v1 = &gAudioTrackBuf;
    do {
        *var_v1 = 0;
        *var_a1 = 0;
        var_a1 += 4;
        var_a0 += 1;
        var_v1 += 4;
    } while (var_a0 < 0x1A);
    var_a0_2 = 0;
    do {
        temp_v1 = &(&gRenderStateB)[var_a0_2];
        temp_v0 = &(&gRenderStateA)[var_a0_2];
        var_a0_2 += 1;
        *temp_v0 = 0;
        *temp_v1 = 0;
    } while (var_a0_2 < 0xD);
    temp_v0_2 = audioLoadBank(0);
    gAudioTrackBuf2.unk0 = temp_v0_2;
    gAudioTrackBuf.unk0 = temp_v0_2;
    temp_v0_3 = audioLoadWavetable(0);
    gAudioTrackBuf.unk34 = temp_v0_3;
    gAudioTrackBuf2.unk34 = temp_v0_3;
    func_800AE368(0);
    gRenderStateA = 1;
    gRenderStateB = 1;
    sfxUpdateChannels();
}
