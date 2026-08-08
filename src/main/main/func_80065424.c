#include "ultra64.h"
void renderLineStrip(void**);                               /* extern */
u16 renderCurveStrip(void**, Unk*, u32, s16, s32, u32);      /* extern */
extern Unk *gTextVertBuf;
extern s16 gTextTexU;
extern Unk *gTextGlyphCoords;
extern u16 gTextGlyphIdx;
extern s32 gTextColorBuf;
extern s16 gTextTexV;

void renderTrackCurves(s32 arg0) {
    s32 temp_s0;
    s32 var_s0;
    s32 var_s1;
    u32 var_s2;
    u32 var_v0;
    Unk *temp_v0;
    Unk *temp_v1;

    if ((s32)0 /* implicit $v0 from caller */ != 0) {
        var_s2 = 0;
        if (gTextGlyphIdx != 0) {
            var_s1 = 0;
            do {
                var_v0 = *(s32 *)((char *)gTextGlyphCoords + var_s1);
                if (var_v0 != 0) {
                    var_s0 = var_v0 * 2;
                    do {
                        temp_s0 = (var_s0 + var_v0) * 2;
                        temp_v0 = (Unk *)((char *)gTextVertBuf + temp_s0);
                        temp_v1 = (Unk *)((char *)gTextGlyphCoords + var_s1);
                        renderCurveStrip(arg0, temp_v1->unk8, temp_v1->unk4, temp_v0->unk2, (s32) temp_v0->unk4, *(((temp_v0->unk0 & 0xF) * 4) + &gTextColorBuf));
                        var_v0 = (u16) *(s32 *)((char *)gTextVertBuf + temp_s0) >> 4;
                        var_s0 = var_v0 * 2;
                    } while (var_v0 != 0);
                }
                var_s2 += 1;
                var_s1 += 0xC;
            } while (var_s2 < (u16) gTextGlyphIdx);
        }
        renderLineStrip(arg0);
        gTextTexU = 1;
        gTextTexV = 0;
        gTextGlyphIdx = 0;
    }
}
