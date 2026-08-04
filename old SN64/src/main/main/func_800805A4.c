#include "ultra64.h"

/*
 * func_800805A4 — GBI audio command dispatcher (nonmatching).
 *
 * PERMANENTLY NONMATCHING: dispatches via jtbl_8004CC18 using jr at prologue.
 *
 * Signature: (Unk *cmd, Unk *node)
 *   cmd:  a0 — 3-byte command buffer; bytes cmd[8], cmd[9], cmd[0xA]
 *   node: a1/s1 — audio node (implicit; s-registers not saved in prologue)
 *
 * Outer dispatch on (cmd[8] & 0xF0) via jtbl_8004CC18 (97 entries):
 *   high nibble 0x80 -> 0x8008093C (shared with 0x90 when cmd[0xA]==0)
 *   high nibble 0x90 -> 0x800805E8 (voice setup, most complex)
 *   high nibble 0xA0 -> 0x80080994 (set note length/offset)
 *   high nibble 0xB0 -> 0x80080A74 (sub-dispatch via jtbl_8004CD9C)
 *   high nibble 0xC0 -> 0x80080CE0 (array-indexed call)
 *   high nibble 0xD0 -> 0x800809FC (linked-list pitch update)
 *   high nibble 0xE0 -> 0x80080D14 (pitch compute + volume update)
 *   others           -> return
 *
 * Inner dispatch for 0xB0 via jtbl_8004CD9C (21 entries, index = cmd_b - 7):
 *   [0]  cmd_b==0x07 -> 0x80080B38 : write s4@[ch*16+9]; list func_8007FF5C+func_80086418
 *   [3]  cmd_b==0x0A -> 0x80080ADC : write s4@[ch*16+7]; list func_8008037C+func_80086558
 *   [9]  cmd_b==0x10 -> 0x80080BCC : write s4@[ch*16+8]; return
 *   others -> return
 *   cmd_b==0x40 (direct): write s4@[ch*16+0xB]; gate state machine
 *   cmd_b==0x5B (direct): write s4@[ch*16+0xA]; list func_800864B8
 *   cmd_b==0x5D (direct): return
 */

extern void *func_800804A8(void *node, u8 b, u8 c, u8 d);
extern void *func_80080438(void *node, u8 b, u8 c, u8 d);
extern void *func_800803C4(void *node, u8 b, u8 c);
extern void  func_80090AE8(void *a0, void *a1, void *stk);
extern f32   func_80086698(s16 cents);
extern void  func_8007E734(void *a, void *cmd_stk, s32 c);
extern s32   func_8007FF5C(void *node, void *ctx);
extern void  func_8007FFE4(void *a, void *b, s32 c);
extern void  func_80086418(void *a, void *b, s32 c, s32 d);
extern void  func_80086558(void *a, void *b, u8 c);
extern void  func_80086388(void *a, void *b, f32 c);
extern void  func_800864B8(void *a, void *b, u8 c);
extern void  func_8008037C(void *node, void *ctx);
extern void  func_80086298(void *a0, void *a1, s32 a2, f32 a3,
                           s32 sp10, u8 sp14, u8 sp18, s32 sp1c);
extern void  func_8007FDA8(void *node, void *a1, u8 a2);

void func_800805A4(Unk *cmd, Unk *node) {
    u8  cmd_a;
    u8  cmd_b;
    u8  cmd_c;
    u8  cmd_high;
    u8  cmd_low;
    s32 dist;
    s32 clamped;

    cmd_a    = *(u8 *)((u8 *)cmd + 8);
    cmd_b    = *(u8 *)((u8 *)cmd + 9);
    cmd_c    = *(u8 *)((u8 *)cmd + 0xA);
    cmd_high = cmd_a & 0xF0;
    cmd_low  = cmd_a & 0xF;

    if ((u32)(cmd_high - 0x80u) >= 0x61u)
        return;

    switch (cmd_high) {

    /* 0x90: voice setup */
    case 0x90: {
        void  *s7;
        void  *s5;
        void  *tbl_base;
        void  *tbl_slot;
        void  *s2_raw;
        s32  (*fn)(s32 *, f32 *, u8, u8, u8, u8);
        s32    jalr_ret;
        s32    stk84;
        f32    stk8C;
        s16    stk9C;
        s16    stk_cmd;
        void  *stk_ptr;
        s32    stk_val;
        u8     stk_ch;
        f32    ft0, ft1, fs0;
        s32    t7_cvt;
        s32    pitch_arg;

        if (cmd_c == 0) goto lbl_case80;

        if (*(s32 *)((u8 *)node + 0x2C) != 1) return;

        s7 = func_800804A8(node, cmd_b, cmd_c, cmd_low);
        if (s7 == NULL) return;

        tbl_base = *(void **)((u8 *)node + 0x60);
        tbl_slot = (u8 *)tbl_base + ((s32)cmd_low << 4);
        stk9C    = (s16)*(u8 *)((u8 *)tbl_slot + 8);

        /* note: func_80080438 receives stk9C/stk9E/stk9F on stack */
        {
            void *s0;
            void *snd_entry;
            u8    base_note;
            s8    fine_cents;
            void *s7_0;
            void *inner;
            void *tbl2;
            u8    s2_a;
            f32   tbl_c;
            f32   s0_28;
            f32   s0_2c;
            f32   fs0_v;
            s32   v0_ff5c;
            s32   s4_v;
            void *inner0;

            s0 = func_80080438(node, cmd_b, cmd_c, cmd_low);
            if (s0 == NULL) return;

            func_80090AE8(*(void **)((u8 *)node + 0x14),
                          (u8 *)s0 + 4, &stk9C);

            *(void **)((u8 *)s0 + 0x20) = s7;
            *(u8     *)((u8 *)s0 + 0x34) = 0;

            if (*(u8 *)((u8 *)tbl_slot + 0xB) < 0x40)
                *(u8 *)((u8 *)s0 + 0x35) = 0;
            else
                *(u8 *)((u8 *)s0 + 0x35) = 2;

            /* pitch: (cmd_b - base_note)*100 + fine_cents */
            snd_entry  = *(void **)((u8 *)s7 + 4);
            base_note  = *(u8 *)((u8 *)snd_entry + 4);
            fine_cents = *(s8  *)((u8 *)snd_entry + 5);
            pitch_arg  = (s16)(((s32)(cmd_b - base_note)) * 100 + fine_cents);
            *(f32 *)((u8 *)s0 + 0x28) = func_80086698((s16)pitch_arg);

            s7_0  = *(void **)((u8 *)s7 + 0);
            inner = *(void **)s7_0;
            *(u8  *)((u8 *)s0 + 0x30) = *(u8  *)((u8 *)inner + 0xC);
            *(s32 *)((u8 *)s0 + 0x24) = *(s32 *)((u8 *)node  + 0x1C)
                                       + *(s32 *)inner;
            *(u8 *)((u8 *)s0 + 0x37) = 0;

            s2_raw = *(void **)tbl_slot;
            s5     = (u8 *)node + 0x48;
            fn     = *(s32 (**)(s32 *, f32 *, u8, u8, u8, u8))((u8 *)node + 0x70);
            stk8C  = 127.0f;

            /* sub-packet 0x16 */
            if (*(u8 *)((u8 *)s2_raw + 4) != 0 && fn != NULL) {
                stk84    = 0;
                jalr_ret = fn(&stk84, &stk8C,
                             *(u8 *)((u8 *)s2_raw + 5),
                             *(u8 *)((u8 *)s2_raw + 6),
                             *(u8 *)((u8 *)s2_raw + 7), 0);
                if (jalr_ret != 0) {
                    stk_cmd = 0x16;
                    stk_ptr = s0;
                    stk_val = stk84;
                    func_8007E734(s5, &stk_cmd, jalr_ret);
                    *(u8 *)((u8 *)s0 + 0x37) |= 1;
                }
            }

            /* IDO saturating f32->u8 (FCSR-based): converts stk8C (127.0f) */
            ft1 = stk8C;
            if (ft1 >= 0.0f && ft1 < 2147483648.0f)
                t7_cvt = (s32)ft1;
            else if (ft1 >= 2147483648.0f && ft1 < 4294967296.0f)
                t7_cvt = (s32)(u32)ft1;
            else
                t7_cvt = -1;
            if (t7_cvt < 0) t7_cvt = -1;
            *(u8 *)((u8 *)s0 + 0x36) = (u8)t7_cvt;

            stk8C = 1.0f;

            /* sub-packet 0x17 */
            if (*(u8 *)((u8 *)s2_raw + 8) != 0 && fn != NULL) {
                stk84    = 0;
                jalr_ret = fn(&stk84, &stk8C,
                             *(u8 *)((u8 *)s2_raw + 9),
                             *(u8 *)((u8 *)s2_raw + 10),
                             *(u8 *)((u8 *)s2_raw + 11), 0);
                if (jalr_ret != 0) {
                    stk_cmd = 0x17;
                    stk_ptr = s0;
                    stk_ch  = cmd_low;
                    stk_val = stk84;
                    func_8007E734(s5, &stk_cmd, jalr_ret);
                    *(u8 *)((u8 *)s0 + 0x37) |= 2;
                }
            }

            /* final volume computation and emit via cmd 6 */
            ft0 = stk8C;
            *(f32 *)((u8 *)s0 + 0x2C) = ft0;
            s0_28  = *(f32 *)((u8 *)s0 + 0x28);
            s0_2c  = *(f32 *)((u8 *)s0 + 0x2C);
            tbl2   = (u8 *)*(void **)((u8 *)node + 0x60) + ((s32)cmd_low << 4);
            tbl_c  = *(f32 *)((u8 *)tbl2 + 0xC);
            s2_a   = *(u8  *)((u8 *)tbl2 + 0xA);
            fs0_v  = tbl_c * s0_28 * s0_2c;

            func_8008037C(s0, node);
            s4_v    = *(s32 *)s0 & 0xFF;   /* v0 & 0xFF */

            v0_ff5c = func_8007FF5C(s0, node);

            inner0 = *(void **)*(void **)((u8 *)s7);
            func_80086298(*(void **)((u8 *)node + 0x14),
                          (u8 *)s0 + 4,
                          *(s32 *)((u8 *)s7 + 8),
                          fs0_v,
                          v0_ff5c,
                          (u8)s4_v,
                          s2_a,
                          *(s32 *)inner0);

            stk_cmd = 0x6;
            stk_ptr = (u8 *)s0 + 4;
            stk_ch  = *(u8  *)((u8 *)inner0 + 0xD);
            stk_val = *(s32 *)((u8 *)inner0 + 4);
            func_8007E734(s5, &stk_cmd, *(s32 *)inner0);
        }
        return;
    }

    /* 0x80: voice state-machine update */
    case 0x80:
    lbl_case80: {
        void *s0_80;
        u8    state;
        void *owner;
        void *owner0;

        s0_80 = func_800803C4(node, cmd_b, cmd_low);
        if (s0_80 == NULL) return;

        state = *(u8 *)((u8 *)s0_80 + 0x35);
        if (state == 2) {
            *(u8 *)((u8 *)s0_80 + 0x35) = 4;
            return;
        }
        *(u8 *)((u8 *)s0_80 + 0x35) = 3;
        owner  = *(void **)((u8 *)s0_80 + 0x20);
        owner0 = *(void **)owner;
        func_8007FFE4(node, (u8 *)s0_80 + 4, *(s32 *)((u8 *)owner0 + 8));
        return;
    }

    /* 0xA0: set note length with offset */
    case 0xA0: {
        void *s0_a0;
        s32   v0_ff5c;

        s0_a0 = func_800803C4(node, cmd_b, cmd_low);
        if (s0_a0 == NULL) return;

        *(u8 *)((u8 *)s0_a0 + 0x33) = cmd_c;
        v0_ff5c = func_8007FF5C(s0_a0, node);
        dist    = *(s32 *)((u8 *)s0_a0 + 0x24) - *(s32 *)((u8 *)node + 0x1C);
        clamped = (dist >= 0) ? dist : 0x3E8;
        func_80086418(*(void **)((u8 *)node + 0x14),
                      (u8 *)s0_a0 + 4, (s16)v0_ff5c, clamped);
        return;
    }

    /* 0xD0: linked-list pitch update */
    case 0xD0: {
        void *s0_d0;
        u8    t6;
        s32   v0_ff5c;

        s0_d0 = *(void **)((u8 *)node + 0x64);
        if (s0_d0 == NULL) return;

        t6 = *(u8 *)((u8 *)s0_d0 + 0x31);
        while (1) {
            if (cmd_low == t6) {
                *(u8 *)((u8 *)s0_d0 + 0x33) = cmd_b;
                v0_ff5c = func_8007FF5C(s0_d0, node);
                dist    = *(s32 *)((u8 *)s0_d0 + 0x24) - *(s32 *)((u8 *)node + 0x1C);
                clamped = (dist >= 0) ? dist : 0x3E8;
                func_80086418(*(void **)((u8 *)node + 0x14),
                              (u8 *)s0_d0 + 4, (s16)v0_ff5c, clamped);
                s0_d0 = *(void **)s0_d0;
            } else {
                s0_d0 = *(void **)s0_d0;
            }
            if (s0_d0 == NULL) break;
            t6 = *(u8 *)((u8 *)s0_d0 + 0x31);
        }
        return;
    }

    /* 0xB0: sub-dispatch on cmd_b */
    case 0xB0: {
        void  *tbl_base_b;
        u8    *tbl_slot_b;
        s32    t9_b;

        if (cmd_b >= 0x41) {
            if (cmd_b == 0x5B) goto lbl_B_5B;
            if (cmd_b == 0x5D) return;
            return;
        }

        if (cmd_b >= 0x1C) {
            if (cmd_b == 0x40) {
                tbl_base_b = *(void **)((u8 *)node + 0x60);
                goto lbl_B_40;
            }
            return;
        }

        t9_b = (s32)cmd_b - 7;
        if ((u32)t9_b >= 21u) return;

        tbl_base_b = *(void **)((u8 *)node + 0x60);
        tbl_slot_b = (u8 *)tbl_base_b + ((s32)cmd_low << 4);

        switch (t9_b) {

        /* cmd_b==0x07: velocity byte; list -> func_8007FF5C + func_80086418 */
        case 0: {
            void *s0_b0;
            u8    t9_filt;
            s32   v0_ff5c;

            *(u8 *)(tbl_slot_b + 9) = cmd_c;
            s0_b0   = *(void **)((u8 *)node + 0x64);
            if (s0_b0 == NULL) return;
            t9_filt = *(u8 *)((u8 *)s0_b0 + 0x31);

            while (1) {
                if (cmd_low == t9_filt) {
                    if (*(u8 *)((u8 *)s0_b0 + 0x34) != 3) {
                        v0_ff5c = func_8007FF5C(s0_b0, node);
                        dist    = *(s32 *)((u8 *)s0_b0 + 0x24) - *(s32 *)((u8 *)node + 0x1C);
                        clamped = (dist >= 0) ? dist : 0x3E8;
                        func_80086418(*(void **)((u8 *)node + 0x14),
                                      (u8 *)s0_b0 + 4, (s16)v0_ff5c, clamped);
                    }
                }
                s0_b0 = *(void **)s0_b0;
                if (s0_b0 == NULL) break;
                t9_filt = *(u8 *)((u8 *)s0_b0 + 0x31);
            }
            return;
        }

        /* cmd_b==0x0A: pan byte; list -> func_8008037C + func_80086558 */
        case 3: {
            void *s0_b3;
            u8    t9_filt3;
            s32   pan_v0;

            *(u8 *)(tbl_slot_b + 7) = cmd_c;
            s0_b3    = *(void **)((u8 *)node + 0x64);
            if (s0_b3 == NULL) return;
            t9_filt3 = *(u8 *)((u8 *)s0_b3 + 0x31);

            while (1) {
                if (cmd_low == t9_filt3) {
                    func_8008037C(s0_b3, node);
                    pan_v0 = 0; /* v0 from func_8008037C; represented as s32 */
                    func_80086558(*(void **)((u8 *)node + 0x14),
                                  (u8 *)s0_b3 + 4, (u8)pan_v0);
                }
                s0_b3 = *(void **)s0_b3;
                if (s0_b3 == NULL) break;
                t9_filt3 = *(u8 *)((u8 *)s0_b3 + 0x31);
            }
            return;
        }

        /* cmd_b==0x10: write byte at offset 8; return */
        case 9:
            *(u8 *)((u8 *)*(void **)((u8 *)node + 0x60) + ((s32)cmd_low << 4) + 8) = cmd_c;
            return;

        default:
            return;
        }

    lbl_B_40: {
        /* cmd_b==0x40: gate/pedal state machine */
        void *s0_40;
        u8    t8_filt;
        u8    state40;

        *(u8 *)((u8 *)tbl_base_b + ((s32)cmd_low << 4) + 0xB) = cmd_c;
        s0_40   = *(void **)((u8 *)node + 0x64);
        if (s0_40 == NULL) return;
        t8_filt = *(u8 *)((u8 *)s0_40 + 0x31);

        while (1) {
            if ((u8)cmd_low == t8_filt) {
                state40 = *(u8 *)((u8 *)s0_40 + 0x35);
                if (state40 != 3) {
                    if (cmd_c < 0x40) {
                        /* gate closed */
                        if (state40 == 2) {
                            *(u8 *)((u8 *)s0_40 + 0x35) = 0;
                        } else if (state40 == 4) {
                            void *ow   = *(void **)((u8 *)s0_40 + 0x20);
                            void *ow0  = *(void **)ow;
                            *(u8 *)((u8 *)s0_40 + 0x35) = 3;
                            func_8007FFE4(node, (u8 *)s0_40 + 4,
                                         *(s32 *)((u8 *)ow0 + 8));
                        }
                    } else {
                        /* gate open */
                        if (state40 == 0) {
                            *(u8 *)((u8 *)s0_40 + 0x35) = 2;
                        } else if (state40 == 4) {
                            void *ow   = *(void **)((u8 *)s0_40 + 0x20);
                            void *ow0  = *(void **)ow;
                            *(u8 *)((u8 *)s0_40 + 0x35) = 3;
                            func_8007FFE4(node, (u8 *)s0_40 + 4,
                                         *(s32 *)((u8 *)ow0 + 8));
                        }
                    }
                }
            }
            s0_40 = *(void **)s0_40;
            if (s0_40 == NULL) break;
            t8_filt = *(u8 *)((u8 *)s0_40 + 0x31);
        }
        return;
    }

    lbl_B_5B: {
        /* cmd_b==0x5B: set byte at offset 0xA; list -> func_800864B8 */
        void *s0_5b;
        u8    t9_5b;

        *(u8 *)((u8 *)*(void **)((u8 *)node + 0x60)
                + ((s32)cmd_low << 4) + 0xA) = cmd_c;
        s0_5b = *(void **)((u8 *)node + 0x64);
        if (s0_5b == NULL) return;
        t9_5b = *(u8 *)((u8 *)s0_5b + 0x31);

        while (1) {
            if (cmd_low == t9_5b) {
                func_800864B8(*(void **)((u8 *)node + 0x14),
                              (u8 *)s0_5b + 4, (u8)cmd_c);
            }
            s0_5b = *(void **)s0_5b;
            if (s0_5b == NULL) break;
            t9_5b = *(u8 *)((u8 *)s0_5b + 0x31);
        }
        return;
    }
    } /* case 0xB0 */

    /* 0xC0: array-indexed function call */
    case 0xC0: {
        void *arr;
        s16   count;
        void *entry;

        arr   = *(void **)((u8 *)node + 0x20);
        count = *(s16 *)arr;
        if ((s32)cmd_b >= (s32)count) return;

        entry = (u8 *)arr + (s32)cmd_b * 4;
        func_8007FDA8(node, *(void **)((u8 *)entry + 0xC), cmd_low);
        return;
    }

    /* 0xE0: pitch compute (cents->freq) and linked-list volume update */
    case 0xE0: {
        void *tbl_e;
        void *tbl_slot_e;
        s16   fine_s;
        s32   raw;
        s32   product;
        s32   rounded;
        f32   fs0_e;
        void *s0_e;
        u8    t6_e;

        tbl_e      = *(void **)((u8 *)node + 0x60);
        tbl_slot_e = (u8 *)tbl_e + ((s32)cmd_low << 4);
        fine_s     = *(s16 *)((u8 *)tbl_slot_e + 4);
        raw        = ((s32)cmd_c << 7) + (s32)cmd_b - 0x2000;
        product    = (s32)fine_s * raw;
        rounded    = (product >= 0) ? (product >> 13) : ((product + 0x1FFF) >> 13);

        fs0_e = func_80086698((s16)rounded);
        *(f32 *)((u8 *)tbl_slot_e + 0xC) = fs0_e;

        s0_e = *(void **)((u8 *)node + 0x64);
        if (s0_e == NULL) return;
        t6_e = *(u8 *)((u8 *)s0_e + 0x31);

        while (1) {
            if (cmd_low == t6_e) {
                f32 ft1_e = *(f32 *)((u8 *)s0_e + 0x28);
                f32 ft3_e = *(f32 *)((u8 *)s0_e + 0x2C);
                func_80086388(*(void **)((u8 *)node + 0x14),
                              (u8 *)s0_e + 4,
                              ft1_e * fs0_e * ft3_e);
            }
            s0_e = *(void **)s0_e;
            if (s0_e == NULL) break;
            t6_e = *(u8 *)((u8 *)s0_e + 0x31);
        }
        return;
    }

    default:
        return;
    }
}
