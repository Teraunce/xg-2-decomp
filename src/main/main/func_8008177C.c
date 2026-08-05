#include "ultra64.h"

/*
 * func_8008177C — MIDI-style byte-stream event decoder.
 *
 * Reads one event from the stream pointed to by arg0 and fills in the event
 * descriptor pointed to by arg1.
 *
 * arg0 (stream context):
 *   unk8  (s32 / u8 *) — current read position in byte stream
 *   unkC  (s32)        — accumulated time (incremented by delta each call)
 *   unk1A (u8  / s16)  — running-status byte (last seen status byte)
 *
 * arg1 (output event):
 *   unk0  — event type  (1 = note/ctrl, 3 = meta 0x51, 4 = meta 0x2F)
 *   unk4  — delta time
 *   unk8  — status/type byte
 *   unk9  — first data byte
 *   unkA  — second data byte (or 0 for channel-pressure / prog-change)
 *   unkB–unkD — additional bytes for meta events
 *
 * The jal delay-slot ABI: before calling streamReadVarInt, a2=a0 and a3=a1
 * are set in the two instructions straddling the jal. m2c did not track
 * these and emitted M2C_ERROR for every $a2/$a3 reference after the call.
 * Fixed: all 43 M2C_ERROR occurrences replaced with arg0 / arg1.
 */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x01 */ s32 unk1;
} UnkStruct_temp_v1;

u8 streamReadVarInt(Unk*);                            /* extern */

void func_8008177C(Unk *arg0, Unk *arg1) {
    s32 temp_t9;
    s32 temp_v0;
    s8 temp_a1;
    u8 *temp_v1_2;
    u8 *temp_v1_3;
    u8 *temp_v1_4;
    u8 *temp_v1_5;
    u8 *temp_v1_6;
    u8 *temp_v1_7;
    u8 *temp_v1_8;
    u8 temp_a0;
    u8 temp_v0_2;
    char *temp_t8;
    UnkStruct_temp_v1 *temp_v1;

    temp_v0 = streamReadVarInt(arg0);
    temp_v1 = (UnkStruct_temp_v1 *)(s32) arg0->unk8;
    arg0->unkC = (s32) (arg0->unkC + temp_v0);
    temp_a0 = temp_v1->unk0;
    temp_t8 = (char *) temp_v1 + 1;
    arg0->unk8 = (s32) temp_t8;
    temp_a1 = temp_a0 & 0xFF;
    if (temp_a0 == 0xFF) {
        temp_v0_2 = temp_v1->unk1;
        arg0->unk8 = (s32) (temp_t8 + 1);
        if (temp_v0_2 == 0x51) {
            *(s32 *)(s32) arg1 = 3;
            arg1->unk4 = temp_v0;
            arg1->unk8 = temp_a1;
            arg1->unk9 = temp_v0_2;
            temp_v1_2 = (u8 *)(s32) arg0->unk8;
            arg0->unk8 = (s32) (temp_v1_2 + 1);
            arg1->unkA = (u8) *temp_v1_2;
            temp_v1_3 = (u8 *)(s32) arg0->unk8;
            arg0->unk8 = (s32) (temp_v1_3 + 1);
            arg1->unkB = (u8) *temp_v1_3;
            temp_v1_4 = (u8 *)(s32) arg0->unk8;
            arg0->unk8 = (s32) (temp_v1_4 + 1);
            arg1->unkC = (u8) *temp_v1_4;
            temp_v1_5 = (u8 *)(s32) arg0->unk8;
            arg0->unk8 = (s32) (temp_v1_5 + 1);
            arg1->unkD = (u8) *temp_v1_5;
        } else if (temp_v0_2 == 0x2F) {
            *(s32 *)(s32) arg1 = 4;
            arg1->unk4 = temp_v0;
            arg1->unk8 = temp_a1;
            arg1->unk9 = temp_v0_2;
            temp_v1_6 = (u8 *)(s32) arg0->unk8;
            arg0->unk8 = (s32) (temp_v1_6 + 1);
            arg1->unkA = (u8) *temp_v1_6;
        }
        arg0->unk1A = 0;
        return;
    }
    *(s32 *)(s32) arg1 = 1;
    arg1->unk4 = temp_v0;
    if (temp_a0 & 0x80) {
        arg1->unk8 = temp_a1;
        temp_v1_7 = (u8 *)(s32) arg0->unk8;
        arg0->unk8 = (s32) (temp_v1_7 + 1);
        arg1->unk9 = (u8) *temp_v1_7;
        arg0->unk1A = (s16) temp_a1;
    } else {
        arg1->unk9 = temp_a0;
        arg1->unk8 = (s8) arg0->unk1A;
    }
    temp_t9 = arg1->unk8 & 0xF0;
    if ((temp_t9 != 0xC0) && (temp_t9 != 0xD0)) {
        temp_v1_8 = (u8 *)(s32) arg0->unk8;
        arg0->unk8 = (s32) (temp_v1_8 + 1);
        arg1->unkA = (u8) *temp_v1_8;
        return;
    }
    arg1->unkA = 0;
}
