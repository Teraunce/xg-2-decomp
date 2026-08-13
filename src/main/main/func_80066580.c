#include "ultra64.h"

/* External functions */
void rdpDrawString(s32, s32, u16 *);                  /* func_80066400 */
void func_80065BDC(s32, s32, s32);
void func_8006541C(s32);                              /* GETTER_NOJR -> func_80065424 */
void func_80063E2C(u32);
void func_80063E4C(u32);
void func_80063ED0(s8);
void func_80063EE4(u32);
void func_80063EF4(s32);
void func_80065694(Unk *, s32);
void func_80065764(Unk *, s32);
void func_800657A8(Unk *, u32);
void func_80065838(Unk *, s32, s32, s32);             /* GETTER_NOJR -> rdpFormatFloat */

/* Globals */
extern Unk gSceneState;         /* scene state struct */
extern u16 gSceneLoopCount;         /* scene loop iteration counter */
extern s16 gTextColorA;         /* text/color param A (also mirrors to gTextColorACopy) */
extern s16 gTextColorB;         /* text/color param B (also mirrors to gTextColorBCopy) */
extern s16 gTextColorC;
extern s16 gTextColorD;
extern s16 gTextColorACopy;
extern s16 gTextColorBCopy;
extern u8  gTextModeByte;         /* text mode byte */
extern s32 gSceneEntityId;         /* current scene entity id */
extern s32 gTextFillFlag;         /* text fill flag: '/' sets, '\\' clears */
extern s32 gClearColor;         /* current clear color (0xFF00FF = uninitialized) */
extern s32 gTextColorRGBA;         /* current RGBA draw color */

/*
 * sceneObjectDispatch — scene command interpreter.
 *
 * Interprets a null-terminated command byte string, dispatching each byte
 * to one of ~20 graphics/text handlers.  After each command, advances cmd
 * by 1, periodically flushes via func_80065BDC, and loops until null.
 *
 * data0/data1: 32-bit data words from the caller argument area.  Commands
 * that consume data read them sequentially from stream[].
 *
 * Returns the delta in gTextColorA from entry to exit.
 *
 * Nonmatching: uses local stream[] instead of asm's sp+0x148 pointer walk.
 * Function size: 0x474 bytes.
 */
s32 sceneObjectDispatch(Unk *entity, u8 *cmd, s32 data0, s32 data1) {
    u16 textBuf[64];   /* $s4 = sp+0x10: text glyph output buffer */
    s32 stream[4];     /* data word stream: {data0, data1, 0, 0} */
    s16 savedE74;      /* sp+0x110: initial gTextColorA (for return delta) */
    s32 si;            /* stream read index */
    u8 byte;
    s32 wordA, wordB;
    u8 *bstr;
    s32 count;

    stream[0] = data0;
    stream[1] = data1;
    stream[2] = 0;
    stream[3] = 0;
    si = 0;

    gSceneLoopCount = 0;
    savedE74 = gTextColorA;

    byte = *cmd;
    if (byte == 0) {
        func_80065BDC((s32)entity, (s32)&gSceneState, 0);
        return (s32)gTextColorA - (s32)savedE74;
    }

    do {
        u32 idx = (u32)((u8)(byte - 0x0A));
        if (idx < 0x71u) {
            switch (byte) {

            case '\n': /* 0x0A: output newline glyph */
                textBuf[0] = 0x000A;
                textBuf[1] = 0;
                rdpDrawString((s32)entity, (s32)&gSceneState, textBuf);
                break;

            case '#': /* 0x23: format integer (month-day style) and draw */
            case '$': /* 0x24: same handler */
                wordA = stream[si++];
                func_800657A8((Unk *)textBuf, (u32)wordA);
                rdpDrawString((s32)entity, (s32)&gSceneState, textBuf);
                break;

            case '/': /* 0x2F: enable text fill */
                gTextFillFlag = 1;
                break;

            case 'C': /* 0x43: set RGB components of draw color (keep alpha) */
                wordA = stream[si++];
                gTextColorRGBA = (gTextColorRGBA & (s32)0xFF000000) | (wordA & 0xFFFFFF);
                break;

            case '\\': /* 0x5C: disable text fill */
                gTextFillFlag = 0;
                break;

            case 'a': /* 0x61: draw ASCII string widened to u16 array */
                bstr = (u8 *)(s32)stream[si++];
                count = 0;
                while (*bstr != 0) {
                    textBuf[count++] = (u16)*bstr++;
                }
                textBuf[count] = 0;
                rdpDrawString((s32)entity, (s32)&gSceneState, textBuf);
                break;

            case 'b': /* 0x62: draw single wide character */
                textBuf[0] = (u16)(stream[si++] & 0xFFFF);
                textBuf[1] = 0;
                rdpDrawString((s32)entity, (s32)&gSceneState, textBuf);
                break;

            case 'c': /* 0x63: set clear color; flush if color changed */
                if (gClearColor != (s32)0xFF00FF) {
                    func_80065BDC((s32)entity, (s32)&gSceneState, 0);
                    func_8006541C((s32)entity);
                }
                func_80063EF4(stream[si++]);
                break;

            case 'd': /* 0x64: format signed decimal integer and draw */
                wordA = stream[si++];
                func_80065694((Unk *)textBuf, wordA);
                rdpDrawString((s32)entity, (s32)&gSceneState, textBuf);
                break;

            case 'f': /* 0x66: format fixed-point float and draw */
                wordA = stream[si++];
                wordB = stream[si++];
                func_80065838((Unk *)textBuf, 0, wordA, wordB);
                rdpDrawString((s32)entity, (s32)&gSceneState, textBuf);
                break;

            case 'g': /* 0x67: reset scene state and set clear color */
                func_80065BDC((s32)entity, (s32)&gSceneState, 0);
                func_8006541C((s32)entity);
                gClearColor = stream[si++];
                break;

            case 'h': /* 0x68: set glyph height (u8) */
                func_80063EE4((u32)(stream[si++] & 0xFF));
                break;

            case 'i': /* 0x69: format unsigned decimal integer and draw */
                wordA = stream[si++];
                func_80065764((Unk *)textBuf, wordA);
                rdpDrawString((s32)entity, (s32)&gSceneState, textBuf);
                break;

            case 'l': /* 0x6C: set alpha byte of draw color (keep RGB) */
                wordA = stream[si++];
                gTextColorRGBA = (gTextColorRGBA & 0xFFFFFF) | (wordA << 24);
                break;

            case 'm': /* 0x6D: flush and set text mode byte */
                func_80065BDC((s32)entity, (s32)&gSceneState, 0);
                gTextModeByte = (u8)(stream[si++] & 0xFF);
                break;

            case 'p': /* 0x70: set character advance (signed) */
                func_80063ED0((s8)(stream[si++] & 0xFF));
                break;

            case 'r': /* 0x72: flush and set full color param set (4 x s16) */
                func_80065BDC((s32)entity, (s32)&gSceneState, 0);
                gTextColorA = gTextColorACopy = (s16)(stream[si++] & 0xFFFF);
                gTextColorB = gTextColorBCopy = (s16)(stream[si++] & 0xFFFF);
                gTextColorD = (s16)(stream[si++] & 0xFFFF);
                gTextColorC = (s16)(stream[si++] & 0xFFFF);
                break;

            case 's': /* 0x73: draw pre-built u16 string at pointer */
                wordA = stream[si++];
                rdpDrawString((s32)entity, (s32)&gSceneState, (u16 *)wordA);
                break;

            case 't': /* 0x74: set text font id (u8) */
                func_80063E2C((u32)(stream[si++] & 0xFF));
                break;

            case 'x': /* 0x78: flush and set color param X (s16) */
                func_80065BDC((s32)entity, (s32)&gSceneState, 0);
                gTextColorA = (s16)(stream[si++] & 0xFFFF);
                break;

            case 'y': /* 0x79: flush and set color param Y (s16) */
                func_80065BDC((s32)entity, (s32)&gSceneState, 0);
                gTextColorB = (s16)(stream[si++] & 0xFFFF);
                break;

            case 'z': /* 0x7A: set entity slot; flush if slot changed */
                wordA = stream[si++];
                if (gTextFillFlag != 0 && wordA != gSceneEntityId) {
                    func_80065BDC((s32)entity, (s32)&gSceneState, 0);
                    func_8006541C((s32)entity);
                }
                func_80063E4C((u32)(wordA & 0xFF));
                break;

            default:
                break;
            }
        }

        cmd++;
        if ((u32)gSceneLoopCount >= 0x79u) {
            func_80065BDC((s32)entity, (s32)&gSceneState, 0);
        }
        byte = *cmd;
    } while (byte != 0);

    func_80065BDC((s32)entity, (s32)&gSceneState, 0);
    return (s32)gTextColorA - (s32)savedE74;
}

/* D_800669F4: rodata / jtbl_8004C0F0 data — defined in .s file */

void audioSetBeatPos(Unk *arg0, s32 arg1, s32 arg2) {
    s32 var_a1;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v1;
    s8 *var_a3_2;
    Unk *var_a3;
    u8 *var_v0_6;
    u8 var_v1_2;
    Unk *temp_a3;
    Unk *temp_a3_2;
    Unk *temp_a3_3;
    Unk *temp_a3_4;
    Unk *temp_a3_5;
    Unk *var_v0_5;

    var_a3 = arg0 + 0x15;
    arg0->unk0 = 0;
    if (arg2 != 0) {
        var_v0 = arg1;
        if (arg1 < 0) {
            var_v0 = arg1 + 7;
        }
        var_v0_2 = (var_v0 >> 3) * 8;
    } else {
        var_v0_2 = (arg1 / 7) * 7;
    }
    arg0->unk8 = (s32) (arg1 - var_v0_2);
    if (arg2 != 0) {
        var_v0_3 = arg1;
        if (arg1 < 0) {
            var_v0_3 = arg1 + 3;
        }
        var_v0_4 = arg1 - ((var_v0_3 >> 2) * 4);
    } else {
        var_v0_4 = -1;
    }
    arg0->unk4 = var_v0_4;
    var_v1 = 7;
    var_v0_5 = arg0 + 7;
    do {
        var_v0_5->unkC = 0;
        var_v1 -= 1;
        var_v0_5 -= 1;
    } while (var_v1 >= 0);
    arg0->unk14 = 0;
    if (arg2 != 0) {
        arg0->unk15 = 0x50;
        temp_a3 = var_a3 + 1;
        var_a3->unk1 = 0x6C;
        temp_a3_2 = temp_a3 + 1;
        temp_a3->unk1 = 0x61;
        temp_a3_3 = temp_a3_2 + 1;
        temp_a3_2->unk1 = 0x79;
        temp_a3_4 = temp_a3_3 + 1;
        temp_a3_3->unk1 = 0x65;
        temp_a3_5 = temp_a3_4 + 1;
        temp_a3_4->unk1 = 0x72;
        var_a1 = arg1 + 1;
        var_a3_2 = temp_a3_5 + 1;
        if (var_a1 >= 0xA) {
            temp_a3_5->unk1 = (s8) (((arg1 + 1) / 10) + 0x30);
            var_a3_2 += 1;
            var_a1 = (arg1 + 1) % 10;
        }
        *var_a3_2 = var_a1 + 0x30;
        var_a3 = var_a3_2 + 1;
    } else {
        extern s32 gSceneObjFuncTable;
        var_v0_6 = *((arg1 * 4) + &gSceneObjFuncTable);
        var_v1_2 = *var_v0_6;
        if (var_v1_2 != 0) {
            do {
                var_v0_6 += 1;
                var_a3->unk0 = var_v1_2;
                var_v1_2 = *var_v0_6;
                var_a3 += 1;
            } while (var_v1_2 != 0);
        }
    }
    var_a3->unk0 = 0;
    arg0->unk28 = 0x2000;
    arg0->unk2C = 0x10;
    arg0->unk30 = 0x800;
    arg0->unk34 = 0x400;
    arg0->unk38 = 0x4000;
    arg0->unk3C = 4;
    arg0->unk40 = 0x8000;
    arg0->unk44 = 1;
    arg0->unk48 = 2;
    arg0->unk4C = 0x20;
    arg0->unk20 = 0;
    arg0->unk24 = arg2;
    arg0->unk50 = 8;
    arg0->unk58 = 0;
    {
        extern f32 gEntityFieldF;
        arg0->unk54 = (f32) gEntityFieldF;
    }
}
