#include "ultra64.h"
void sfxSetPitch(s32);                                 /* extern */
void sfxSetFreq(s32);                                 /* extern */
void sfxSetFilter(s32);                                 /* extern */
void sfxSetState(s32);                                 /* extern */
extern s32 gTexColorKey;
extern s32 gTexAddrKey;
extern s32 gTexCacheSlot;
extern s16 gTextTexU;
extern s16 gTextGlyphIdx;
extern s16 gTextTexV;
extern s16 gTextCurX;
extern s16 gTextCurY;
extern s32 gRdpSyncDone;
extern s32 gTextWrap;
extern s32 gTextFontId;
extern s16 gTextClipH;
extern s16 gTextLayoutW;
extern s16 gTextLayoutX;
extern s16 gTextClipY;
extern s8 gTextAlignFlags;

void rdpStateInit(void) {
    sfxSetPitch(0);
    sfxSetFreq(8);
    sfxSetFilter(0);
    sfxSetState(1);
    gTextWrap = 0;
    gTextCurY = 0;
    gTextCurX = 0;
    gTextLayoutX = 0;
    gTextClipY = 0;
    gTextLayoutW = 0x140;
    gTextClipH = 0xF0;
    gTextAlignFlags = 2;
    gTextFontId = 0;
    gRdpSyncDone = 0;
    gTexColorKey = 0xFF00FF;
    gTexAddrKey = 0xFF00FF;
    gTexCacheSlot = -1;
    gTextTexU = 1;
    gTextTexV = 0;
    gTextGlyphIdx = 0;
}
