#include "ultra64.h"

/*
 * func_8007F5C4 — per-frame node update dispatcher (nonmatching).
 *
 * Outer switch: index = u16(obj+0x38), 24 entries via jtbl_8004CB5C.
 * Case 0 has a nested inner switch using jtbl_8004CBBC (20 entries);
 *   the sub-index comes from func_8007DD7C writing to stk58 (sp+0x58).
 *
 * Epilogue: result = osStopTimer(obj+0x48, &obj->0x38).
 *   obj->0x28 = result always; if 0 loop; else obj->0x1C += result.
 *
 * Register map:
 *   s2  = obj
 *   s5  = obj + 0x48   (pkt base; a0 for osStopTimer)
 *   sp+0x50 = &obj->0x38  (a1 for osStopTimer)
 *
 * jtbl_8004CB5C active entries (24 total):
 *   [0]=0x8007F628  [2,15]=0x8007F958  [5]=0x8007F714  [6]=0x8007F760
 *   [7]=0x8007F974  [9]=0x8007F6F4   [A]=0x8007F994   [C]=0x8007FB24
 *   [D]=0x8007FB40  [E]=0x8007FB74   [F]=0x8007F9F8   [10]=0x8007FA1C
 *   [11]=0x8007FA88 [16]=0x8007F7C4  [17]=0x8007F8D0  rest→default
 *
 * jtbl_8004CBBC active entries (20 total):
 *   [0]=0x8007F664  [2]=0x8007F68C  [3]=0x8007F6B8
 *   [17,18,19]=0x8007F6E4  rest→default
 *
 * PERMANENTLY NONMATCHING: sub-case 0 and cases 2/0x15 invoke
 *   func_8007ED94 via $t0 (non-standard ABI), not representable in C.
 */

void  func_8007DD7C(void *a, s16 *b);
void  func_8007ED94(void);      /* nonmatching: reads $t0, not $a0/$a1 */
void  func_8007EB18(void *a);
void func_8007EBC4(void *);
void func_8007EB88(void *);                           /* extern */
void  func_8007E618(void *a, s32 b);
s32   func_8007FF5C(void *a, void *b);
s32   func_8007FF38(void *a, void *b);
void func_8007FE7C(Unk*, Unk*);                   /* extern */
s32   func_80080110(void *a, void *b, s32 c);
void  func_8007FFE4(void *a, void *b, s32 c);
void  func_800801B8(void *a, void *b);
void  func_800813E8(void *a, void *b);
void  osSetTimer(void *a, void *b, s32 c);
s32   osStopTimer(void *a, void *b);
void  func_80086188(void *a, void *b);
void  func_800860D8(void *a, void *b);
void  func_80086418(void *a, void *b, s32 c, s32 d);
void  func_80086388(void *a, void *b, f32 c);

extern f32 D_8004CC0C;

/* nonmatching: jtbl_8004CB5C/CBBC switch + func_8007ED94 non-std ABI */
void func_8007F5C4(Unk *obj) {
    /* Permanent */
    Unk  *s5   = (Unk *)((u8 *)obj + 0x48);
    void *sp50 = (void *)((u8 *)obj + 0x38); /* stored ptr; a1 for E858 */

    /* Loop/dispatch */
    u16   type;
    s32   result;
    s16   inner_idx;

    /* Shared temporaries — all at function scope for C89 */
    Unk  *s0, *s1, *s4;
    s32   s3i;          /* obj->0x40 as integer (case 6) */
    s32   t6, t8, t9;
    s32   v0a, v0b;
    s32   fn_ret;       /* v0 from jalr calls */
    f32   ft0, ft1, ft2, ft3;
    void *inner_s0;

    /* Stack packet scalars */
    s16   stk58;        /* sp+0x58: func_8007DD7C out-param / sub-cmd */
    f32   stk78;        /* sp+0x78: fn-ptr f32 out-param */
    s16   stk8C;        /* sp+0x8C: packet command */
    void *stk90;        /* sp+0x90 */
    void *stk94;        /* sp+0x94 */
    u8    stk98;        /* sp+0x98 */

lbl_loop:
    type = *(u16 *)((u8 *)obj + 0x38);
    if ((u32)type >= 0x18u) goto lbl_default;

    switch ((s32)type) {

    /* ------------------------------------------------------------------ */
    /* Case 0: inner dispatch via func_8007DD7C + jtbl_8004CBBC.         */
    /*   obj->0x18 must be non-NULL; inner index = stk58 - 1, [0..19].  */
    /* ------------------------------------------------------------------ */
    case 0:
        if (*(void **)((u8 *)obj + 0x18) == NULL) goto lbl_epilogue;
        func_8007DD7C(*(void **)((u8 *)obj + 0x18), &stk58);
        inner_idx = (s16)((s32)stk58 - 1);
        if ((u32)(s32)inner_idx >= 20u) goto lbl_default;
        switch ((s32)inner_idx) {

        /* Sub-case 0: func_8007ED94 ($t0=&stk58, non-std) + EB18 */
        case 0:
            func_8007ED94(); /* nonmatching: $t0 = &stk58 */
            func_8007EB18(obj);
            goto lbl_epilogue;

        /* Sub-case 2: func_8007EBC4(obj) + func_8007EB18 */
        case 2:
            func_8007EBC4(obj);
            func_8007EB18(obj);
            goto lbl_epilogue;

        /* Sub-case 3: obj->0x2C=2; send cmd=0x10 with 0x7FFFFFFF */
        case 3:
            *(s32 *)((u8 *)obj + 0x2C) = 2;
            stk58 = 0x10;
            osSetTimer(s5, &stk58, 0x7FFFFFFF);
            goto lbl_epilogue;

        /* Sub-cases 17/18/19: func_8007EB18(obj) */
        case 17:
        case 18:
        case 19:
            func_8007EB18(obj);
            goto lbl_epilogue;

        default:
            goto lbl_default;
        }
        /* NOTREACHED */

    /* ------------------------------------------------------------------ */
    /* Cases 2 / 0x15: func_8007ED94 ($t0=sp50=&obj->0x38, non-std)    */
    /* ------------------------------------------------------------------ */
    case 2:
    case 0x15:
        func_8007ED94(); /* nonmatching: $t0 = &obj->0x38 */
        goto lbl_default;

    /* ------------------------------------------------------------------ */
    /* Case 5: teardown: 80086188 + 800860D8; cond 800813E8; 800801B8   */
    /* ------------------------------------------------------------------ */
    case 5:
        s0 = *(Unk **)((u8 *)obj + 0x3C);
        func_80086188(*(void **)((u8 *)obj + 0x14), s0);
        func_800860D8(*(void **)((u8 *)obj + 0x14), s0);
        s1 = *(Unk **)((u8 *)s0 + 0x10);
        if (*(u8 *)((u8 *)s1 + 0x37) != 0) func_800813E8(obj, s1);
        func_800801B8(obj, s0);
        goto lbl_epilogue;

    /* ------------------------------------------------------------------ */
    /* Case 6: arm s1->0x34; update s1->0x24/s1->0x30;                  */
    /*   func_8007FF5C → func_80086418                                    */
    /* ------------------------------------------------------------------ */
    case 6:
        s0  = *(Unk **)((u8 *)obj + 0x3C);
        s1  = *(Unk **)((u8 *)s0 + 0x10);
        s3i = *(s32 *)((u8 *)obj + 0x40);
        if (*(u8 *)((u8 *)s1 + 0x34) == 0) *(u8 *)((u8 *)s1 + 0x34) = 1;
        *(s32 *)((u8 *)s1 + 0x24) = *(s32 *)((u8 *)obj + 0x1C) + s3i;
        *(u8 *)((u8 *)s1 + 0x30) = *(u8 *)((u8 *)obj + 0x44);
        v0a = (s16)func_8007FF5C(s1, obj);
        func_80086418(*(void **)((u8 *)obj + 0x14), s0, v0a, s3i);
        goto lbl_epilogue;

    /* ------------------------------------------------------------------ */
    /* Case 7: func_8007EBC4(obj, &obj->0x38) → default                  */
    /* ------------------------------------------------------------------ */
    case 7:
        func_8007EBC4(obj);
        goto lbl_default;

    /* ------------------------------------------------------------------ */
    /* Case 9: send packet cmd=9, param=obj->0x5C                        */
    /* ------------------------------------------------------------------ */
    case 9:
        stk8C = 9;
        osSetTimer(s5, &stk8C, *(s32 *)((u8 *)obj + 0x5C));
        goto lbl_epilogue;

    /* ------------------------------------------------------------------ */
    /* Case 0xA: linked-list traversal; func_8007FF5C + func_80086418.  */
    /*   Head = obj->0x64; next = *(void**)s1 each iteration.            */
    /* ------------------------------------------------------------------ */
    case 0xA:
        s1 = *(Unk **)((u8 *)obj + 0x64);
        t6 = *(s16 *)((u8 *)obj + 0x3C);
        if (s1 == NULL) goto lbl_default;
        *(s16 *)((u8 *)obj + 0x32) = (s16)t6;
        do {
            v0a = (s16)func_8007FF5C(s1, obj);
            v0b = func_8007FF38(s1, *(void **)((u8 *)obj + 0x1C));
            func_80086418(*(void **)((u8 *)obj + 0x14),
                          (u8 *)s1 + 4, v0a, v0b);
            s1 = *(Unk **)s1;
        } while (s1 != NULL);
        goto lbl_epilogue;

    /* ------------------------------------------------------------------ */
    /* Case 0xC: byte write into table at obj->0x60 + (u8→0x3C)*16 + 8 */
    /* ------------------------------------------------------------------ */
    case 0xC:
        t6 = *(u8 *)((u8 *)obj + 0x3C);
        t9 = *(s32 *)((u8 *)obj + 0x60);
        t8 = *(u8 *)((u8 *)obj + 0x3D);
        *(u8 *)((u8 *)(uintptr_t)t9 + (t6 << 4) + 8) = (u8)t8;
        goto lbl_default;

    /* ------------------------------------------------------------------ */
    /* Case 0xD: obj->0x18 = obj->0x3C; func_8007EB88;                  */
    /*   if obj->0x20 != NULL: func_8007FE7C                              */
    /* ------------------------------------------------------------------ */
    case 0xD:
        *(s32 *)((u8 *)obj + 0x18) = *(s32 *)((u8 *)obj + 0x3C);
        func_8007EB88(obj);
        if (*(void **)((u8 *)obj + 0x20) == NULL) goto lbl_epilogue;
        func_8007FE7C(obj, *(void **)((u8 *)obj + 0x20));
        goto lbl_epilogue;

    /* ------------------------------------------------------------------ */
    /* Case 0xE: obj->0x20 = obj->0x3C; func_8007FE7C                   */
    /* ------------------------------------------------------------------ */
    case 0xE:
        *(s32 *)((u8 *)obj + 0x20) = *(s32 *)((u8 *)obj + 0x3C);
        func_8007FE7C(obj, *(void **)((u8 *)obj + 0x3C));
        goto lbl_epilogue;

    /* ------------------------------------------------------------------ */
    /* Case 0xF: if obj->0x2C != 1: set 1, call func_8007EB18           */
    /* ------------------------------------------------------------------ */
    case 0xF:
        if (*(s32 *)((u8 *)obj + 0x2C) == 1) goto lbl_default;
        *(s32 *)((u8 *)obj + 0x2C) = 1;
        func_8007EB18(obj);
        goto lbl_epilogue;

    /* ------------------------------------------------------------------ */
    /* Case 0x10: if obj->0x2C==2: drain obj->0x64 list.                */
    /*   Re-reads obj->0x64 each iteration (not linked-list next ptr).   */
    /* ------------------------------------------------------------------ */
    case 0x10:
        if (*(s32 *)((u8 *)obj + 0x2C) != 2) goto lbl_epilogue;
        s1 = *(Unk **)((u8 *)obj + 0x64);
        if (s1 != NULL) {
            inner_s0 = (u8 *)s1 + 4;
            do {
                func_80086188(*(void **)((u8 *)obj + 0x14), inner_s0);
                func_800860D8(*(void **)((u8 *)obj + 0x14), inner_s0);
                if (*(u8 *)((u8 *)s1 + 0x37) != 0) func_800813E8(obj, s1);
                func_800801B8(obj, inner_s0);
                s1 = *(Unk **)((u8 *)obj + 0x64); /* re-read */
                inner_s0 = (u8 *)s1 + 4;
            } while (s1 != NULL);
        }
        *(s32 *)((u8 *)obj + 0x2C) = 0;
        goto lbl_default;

    /* ------------------------------------------------------------------ */
    /* Case 0x11: if obj->0x2C==1: E618×3; linked-list loop;            */
    /*   set obj->0x2C=2; send cmd=0x10 packet.                          */
    /* ------------------------------------------------------------------ */
    case 0x11:
        if (*(s32 *)((u8 *)obj + 0x2C) != 1) goto lbl_epilogue;
        func_8007E618(s5, 0);
        func_8007E618(s5, 0x15);
        func_8007E618(s5, 2);
        s1 = *(Unk **)((u8 *)obj + 0x64);
        if (s1 != NULL) {
            inner_s0 = (u8 *)s1 + 4;
            do {
                if (func_80080110(obj, inner_s0, 0xC350) != 0)
                    func_8007FFE4(obj, inner_s0, 0xC350);
                s1 = *(Unk **)s1;  /* linked-list next */
                inner_s0 = (u8 *)s1 + 4;
            } while (s1 != NULL);
        }
        *(s32 *)((u8 *)obj + 0x2C) = 2;
        stk8C = 0x10;
        osSetTimer(s5, &stk8C, 0x7FFFFFFF);
        goto lbl_epilogue;

    /* ------------------------------------------------------------------ */
    /* Case 0x16: jalr obj->0x74(s4, &stk78); saturate f32→s32;         */
    /*   store at s1->0x36; func_8007FF5C, FF38, 80086418, E734.        */
    /* ------------------------------------------------------------------ */
    case 0x16:
        s4  = *(Unk **)((u8 *)obj + 0x40);
        s1  = *(Unk **)((u8 *)obj + 0x3C);
        {
            s32 (*fn)(void *, void *) = *(s32 (**)(void*, void*))((u8*)obj + 0x74);
            fn_ret = fn(s4, &stk78);
        }
        ft0 = stk78;
        /*
         * Saturating f32→s32 (asm: cvt.w.s with FP-exception guard):
         *   [0, 2^31)      → (s32)ft0
         *   [2^31, 2^32)   → (s32)(u32)ft0
         *   NaN/Inf/neg    → -1
         */
        if (ft0 >= 0.0f && ft0 < 2147483648.0f)
            t6 = (s32)ft0;
        else if (ft0 >= 2147483648.0f && ft0 < 4294967296.0f)
            t6 = (s32)((u32)ft0);
        else
            t6 = -1;
        if (t6 < 0) t6 = -1;
        *(u8 *)((u8 *)s1 + 0x36) = (u8)t6;
        v0a = (s16)func_8007FF5C(s1, obj);
        v0b = func_8007FF38(s1, *(void **)((u8 *)obj + 0x1C));
        func_80086418(*(void **)((u8 *)obj + 0x14),
                      (u8 *)s1 + 4, v0a, v0b);
        stk8C = 0x16;
        stk90 = s1;
        stk94 = s4;
        osSetTimer(s5, &stk8C, fn_ret);
        goto lbl_epilogue;

    /* ------------------------------------------------------------------ */
    /* Case 0x17: jalr obj->0x74(s4, &stk78); f32 multiply chain;       */
    /*   func_80086388, osSetTimer.                                    */
    /* ------------------------------------------------------------------ */
    case 0x17:
        s4    = *(Unk **)((u8 *)obj + 0x40);
        s1    = *(Unk **)((u8 *)obj + 0x3C);
        stk98 = *(u8 *)((u8 *)obj + 0x44);
        {
            s32 (*fn)(void *, void *) = *(s32 (**)(void*, void*))((u8*)obj + 0x74);
            fn_ret = fn(s4, &stk78);
        }
        ft2 = stk78;
        ft0 = *(f32 *)((u8 *)s1 + 0x28);
        *(f32 *)((u8 *)s1 + 0x2C) = ft2;
        ft1 = *(f32 *)((u8 *)s1 + 0x2C);   /* reload from store */
        ft2 = ft0 * ft1;                    /* s1->0x28 * s1->0x2C */
        {
            u8 *tbl = (u8 *)*(void **)((u8 *)obj + 0x60);
            ft3 = *(f32 *)(tbl + ((s32)stk98 << 4) + 0xC);
        }
        ft0 = ft3 * ft2;
        func_80086388(*(void **)((u8 *)obj + 0x14), (u8 *)s1 + 4, ft0);
        stk8C = 0x17;
        stk90 = s1;
        stk94 = s4;
        stk98 = *(u8 *)((u8 *)obj + 0x44);
        osSetTimer(s5, &stk8C, fn_ret);
        goto lbl_epilogue;

    default:
        break;
    }

lbl_default:
lbl_epilogue:
    result = osStopTimer(s5, sp50);
    *(s32 *)((u8 *)obj + 0x28) = result;  /* delay slot: stored unconditionally */
    if (result == 0) goto lbl_loop;
    *(s32 *)((u8 *)obj + 0x1C) += result;
}
