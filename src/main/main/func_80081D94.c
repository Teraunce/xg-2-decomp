#include "ultra64.h"

/*
 * func_80081D94 — per-frame update dispatcher for an audio/animation node.
 *   Loops calling osStopTimer until it returns nonzero.
 *   Dispatches on s16 type field (obj+0x28) via jtbl_8004CE70 (9 entries).
 *   type==5 is caught before table lookup; type>=9 skips osStopTimer.
 *
 * Jump table: jtbl_8004CE70
 *   [0]=0x80081E30  [1]=0x80081F98  [2]=0x80082064  [3]=0x80082148
 *   [4]=0x800820CC  [5]=epilogue    [6]=0x800821AC
 *   [7]=0x80082258  [8]=0x80082120
 *
 * Object offsets used:
 *   +0x14 s7 = sub-ptr A (a0 for osStopTimer / osSetTimer)
 *   +0x28 s4 = s16 type / also base for s4 sub-pointer
 *   +0x2C s5 = sub-object pointer
 *   +0x38    = sub-ptr B (a0 for engine helpers)
 *   +0x48    = param word (type==5)
 *   +0x4C    = result accumulator
 *   +0x50    = running total
 *
 * s5 offsets: +0x1C s1=node ptr; +0x20 s16; +0x24 f32 rate; +0x28 state;
 *             +0x2C s16 vol; +0x2E u8 pan; +0x2F u8 pitch-fine
 * s1 node: *s1+0=s32 root; +4=s32 valA (-1=invalid); +8=s32 valB;
 *           +C=u8 vol-mul; +D=u8 pitch-mul
 *
 * D_8004CE68: f64 constant loaded into $fs0 at entry; used in c.lt.d
 * D_8004CE98: f64 lower-bound clamp for rate
 * D_8004CEA0: f32 substitute rate when rate < lower bound
 */

void  func_80090AE8(void *a, void *b, void *c);
void func_80086208(void *a, void *b, s32 c);
void  sfxPlayPanAtEntity(void *a, void *b, s32 vol);
void  sfxPlayAtEntity(void *a, void *b, s32 pitch, s32 c);
void  sfxPlayLoopAtEntity(void *a, void *b, f32 rate);
void  sfxPlayAbsAtEntity(void *a, void *b, s32 fine);
void  osSetTimer(void *node, void *pkt, s32 param);
void  sfxPlayNoteAtEntity(void *a, void *b);
void  sfxStopAtEntity(void *a, void *b);
void  func_80081D08(void);
s32   osStopTimer(void *a, void *b);

extern f64 D_8004CE68;
extern f64 D_8004CE98;
extern f32 D_8004CEA0;

/* nonmatching: jtbl_8004CE70 switch + bnel/beql branch-likely + FPU */
void func_80081D94(Unk *obj) {
    Unk  *s4   = (Unk *)((u8 *)obj + 0x28);
    Unk  *s7   = (Unk *)((u8 *)obj + 0x14);
    s32   fp   = 1;
    s16   type;
    Unk  *s5;
    Unk  *s1;
    s32   result;
    /* per-case locals — declared at function scope for C89 */
    s32   t6, t7, t8, t9, t0, s0, vol16, a2, raw, v1;
    f32   ft0, fv1;
    f64   fv0;
    /* two small stack-allocated parameter structs */
    s16   pkt_cmd;   /* sp+0xC0 */
    Unk  *pkt_sub;   /* sp+0xC4 */
    s16   pkt2_cmd;  /* sp+0xF4 */
    s16   stk_v0;    /* sp+0xE0 */
    s16   stk_v1;    /* sp+0xE2 */
    u8    stk_v2;    /* sp+0xE4 */
    Unk  *a3;

next_frame:
    type = *(s16 *)((u8 *)obj + 0x28);
    s5   = *(Unk **)((u8 *)obj + 0x2C);

    /* type==5: send hard-coded "5" packet */
    if (type == 5) {
        pkt2_cmd = 5;
        osSetTimer(s7, &pkt2_cmd, *(s32 *)((u8 *)obj + 0x48));
        goto lbl_epilogue;
    }

    if ((u32)(s32)type >= 9u) goto lbl_done;

    s1 = *(Unk **)((u8 *)s5 + 0x1C);

    switch (type) {

    /* ------------------------------------------------------------------ */
    /* Case 0: full init — compute vol/pan/rate, kick playback,           */
    /*         write "6" packet.                                           */
    /* ------------------------------------------------------------------ */
    case 0:
        if (*(s32 *)((u8 *)s5 + 0x28) != 0) goto lbl_epilogue;
        if (s1 == 0) goto lbl_done;

        stk_v0 = *(s16 *)((u8 *)s5 + 0x20);
        stk_v1 = 0;
        stk_v2 = 0;
        func_80090AE8(*(void **)((u8 *)obj + 0x38), s5, &stk_v0);

        a3    = *(Unk **)s1;
        t6    = *(u8  *)((u8 *)a3 + 0xC);
        t7    = *(s16 *)((u8 *)s5 + 0x2C);
        vol16 = (s32)(t6 * t7) / 0x7F;
        s0    = *(s32 *)a3;

        t6    = *(u8 *)((u8 *)s5 + 0x2E);
        t7    = *(u8 *)((u8 *)s1 + 0xC);
        v1    = (s16)((u8)(t6 + t7) - 0x40);
        t0    = (v1 <= 0) ? 0 : (v1 >= 0x7F ? 0x7F : v1);

        ft0   = *(f32 *)((u8 *)s5 + 0x24);
        func_80086208(*(void **)((u8 *)obj + 0x38), s5,
                      *(s32 *)((u8 *)s1 + 0x8));
        *(s32 *)((u8 *)s5 + 0x28) = fp;
        sfxPlayPanAtEntity(*(void **)((u8 *)obj + 0x38), s5, t0);
        sfxPlayAtEntity(*(void **)((u8 *)obj + 0x38), s5, vol16, s0);
        sfxPlayLoopAtEntity(*(void **)((u8 *)obj + 0x38), s5, ft0);
        sfxPlayAbsAtEntity(*(void **)((u8 *)obj + 0x38), s5,
                      *(u8 *)((u8 *)s5 + 0x2F));

        raw  = *(s32 *)*(void **)s1;
        fv0  = (f64)((f32)raw / ft0);
        a2   = (fv0 < D_8004CE68) ? (s32)fv0 : 0x7FFFFFFF;
        pkt_cmd = 6;
        pkt_sub = s5;
        osSetTimer(s7, &pkt_cmd, a2);
        goto lbl_epilogue;

    /* ------------------------------------------------------------------ */
    /* Case 1: check playback progress; send "7" packet or teardown.      */
    /* ------------------------------------------------------------------ */
    case 1:
        if (*(s32 *)((u8 *)s5 + 0x28) != fp) goto lbl_epilogue;
        if (s1 == 0) goto lbl_done;

        fv1  = *(f32 *)((u8 *)s5 + 0x24);
        raw  = *(s32 *)((u8 *)*(void **)s1 + 8);
        fv0  = (f64)((f32)raw / fv1);
        s0   = (fv0 < D_8004CE68) ? (s32)fv0 : 0x7FFFFFFF;

        sfxPlayAtEntity(*(void **)((u8 *)obj + 0x38), s5, 0, s0);
        if (s0 != 0) {
            pkt_cmd = 7;
            pkt_sub = s5;
            osSetTimer(s7, &pkt_cmd, s0);
            *(s32 *)((u8 *)s5 + 0x28) = 2;
            goto lbl_done;
        }
        sfxPlayNoteAtEntity(*(void **)((u8 *)obj + 0x38), s5);
        sfxStopAtEntity(*(void **)((u8 *)obj + 0x38), s5);
        func_80081D08();
        *(s32 *)((u8 *)s5 + 0x28) = 0;
        goto lbl_done;

    /* ------------------------------------------------------------------ */
    /* Case 2: update panning; call sfxPlayPanAtEntity with clamped volume.    */
    /* ------------------------------------------------------------------ */
    case 2:
        if (*(s32 *)((u8 *)s5 + 0x28) != fp) goto lbl_done;
        t6 = *(u8 *)((u8 *)s4 + 8);
        *(u8 *)((u8 *)s5 + 0x2E) = (u8)t6;
        if (s1 == 0) goto lbl_done;
        t9 = *(u8 *)((u8 *)s1 + 0xC);
        v1 = (s16)((t6 & 0xFF) + t9 - 0x40);
        t0 = (v1 <= 0) ? 0 : (v1 >= 0x7F ? 0x7F : v1);
        sfxPlayPanAtEntity(*(void **)((u8 *)obj + 0x38), s5, t0);
        goto lbl_epilogue;

    /* ------------------------------------------------------------------ */
    /* Case 3: update vol param; compute and send pitch.                   */
    /* ------------------------------------------------------------------ */
    case 3:
        if (*(s32 *)((u8 *)s5 + 0x28) != fp) goto lbl_done;
        t7 = *(s16 *)((u8 *)s4 + 8);
        *(s16 *)((u8 *)s5 + 0x2C) = (s16)t7;
        if (s1 == 0) goto lbl_epilogue;
        a3 = *(Unk **)s1;
        t6 = *(u8 *)((u8 *)a3 + 0xD);
        t8 = (s32)(t6 * t7) / 0x7F;
        sfxPlayAtEntity(*(void **)((u8 *)obj + 0x38), s5,
                      (s16)t8, 0x3E8);
        goto lbl_epilogue;

    /* ------------------------------------------------------------------ */
    /* Case 4: update playback rate; clamp below D_8004CE98; send.        */
    /* ------------------------------------------------------------------ */
    case 4:
        ft0 = *(f32 *)((u8 *)s4 + 8);
        *(f32 *)((u8 *)s5 + 0x24) = ft0;
        if ((f64)ft0 < D_8004CE98) {
            ft0 = D_8004CEA0;
            *(f32 *)((u8 *)s5 + 0x24) = ft0;
        }
        if (*(s32 *)((u8 *)s5 + 0x28) != fp) goto lbl_epilogue;
        sfxPlayLoopAtEntity(*(void **)((u8 *)obj + 0x38), s5, ft0);
        goto lbl_epilogue;

    case 5:
    default:
        goto lbl_done;

    /* ------------------------------------------------------------------ */
    /* Case 6: update pitch from node->unk4; send "fp"(=1) packet.        */
    /* ------------------------------------------------------------------ */
    case 6:
        a3 = *(Unk **)s1;
        if (*(s32 *)((u8 *)a3 + 4) == -1) goto lbl_epilogue;
        t6  = *(u8  *)((u8 *)a3 + 0xD);
        t7  = *(s16 *)((u8 *)s5 + 0x2C);
        a2  = (s16)((s32)(t6 * t7) / 0x7F);
        fv1 = *(f32 *)((u8 *)s5 + 0x24);
        raw = *(s32 *)((u8 *)a3 + 4);
        fv0 = (f64)((f32)raw / fv1);
        s0  = (fv0 < D_8004CE68) ? (s32)fv0 : 0x7FFFFFFF;
        sfxPlayAtEntity(*(void **)((u8 *)obj + 0x38), s5, a2, s0);
        pkt_cmd = (s16)fp;
        pkt_sub = s5;
        osSetTimer(s7, &pkt_cmd, s0);
        goto lbl_epilogue;

    /* ------------------------------------------------------------------ */
    /* Case 7: end-of-note teardown (same as case 1 else branch).          */
    /* ------------------------------------------------------------------ */
    case 7:
        sfxPlayNoteAtEntity(*(void **)((u8 *)obj + 0x38), s5);
        sfxStopAtEntity(*(void **)((u8 *)obj + 0x38), s5);
        func_80081D08();
        *(s32 *)((u8 *)s5 + 0x28) = 0;
        goto lbl_done;

    /* ------------------------------------------------------------------ */
    /* Case 8: update pitch-fine byte; call sfxPlayAbsAtEntity.                 */
    /* ------------------------------------------------------------------ */
    case 8:
        if (*(s32 *)((u8 *)s5 + 0x28) != fp) goto lbl_done;
        t9 = *(u8 *)((u8 *)s4 + 8);
        *(u8 *)((u8 *)s5 + 0x2F) = (u8)t9;
        sfxPlayAbsAtEntity(*(void **)((u8 *)obj + 0x38), s5, t9 & 0xFF);
        goto lbl_epilogue;

    } /* end switch */

lbl_done:
    /* a0=s7, falls through to lbl_epilogue */

lbl_epilogue:
    result = osStopTimer(s7, s4);
    if (result == 0) goto next_frame;
    *(s32 *)((u8 *)obj + 0x4C) = result;
    *(s32 *)((u8 *)obj + 0x50) += result;
}
