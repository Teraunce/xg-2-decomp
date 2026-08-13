#include "ultra64.h"

/*
 * gbiCmdDispatch — printf-style format character dispatch for vsprintfCore.
 *
 * PERMANENTLY NONMATCHING — two reasons:
 *
 * 1. Non-standard ABI: $s0 is an implicit context pointer provided by the
 *    caller directly in $s0 (a callee-saved register).  The prologue saves
 *    $ra and $a1 but does NOT save/restore $s0, then writes immediately
 *    through it (clears six words at s0+0xC..s0+0x20).
 *
 * 2. Dispatches via jr through jtbl_8004CFFC (52 entries, index = a1−0x45;
 *    secondary range for a1 < 0x26 is handled inline).
 *
 * Context struct fields accessed (s0):
 *   s0->0x00 : hi-word of 64-bit value / sign extension / double hi
 *   s0->0x04 : lo-word of 64-bit value / main value
 *   s0->0x08 : pointer to current output position in text buffer
 *   s0->0x0C : output byte offset (index into a3_buf)
 *   s0->0x10..0x20 : zeroed by prologue
 *   s0->0x24 : max-count threshold (for 't' cmd)
 *   s0->0x2C : accumulated char count written (for 'o'/'n' cmd)
 *   s0->0x30 : format flags (0x1=space, 0x2=force-sign, 0x8=hex-prefix)
 *   s0->0x34 : length modifier (0x68='h'=short, 0x6C='l'=long, 0x4C='L'=long-long)
 *
 * Arguments (re-ABI'd for readability):
 *   s0_ctx   : format context (arrived in $s0, not $a0)
 *   cmd      : format character (ASCII, masked to 8 bits)
 *   stream   : pointer to stream read pointer — **stream advances as data consumed
 *   buf      : output text buffer base
 *
 * Called-out helpers:
 *   func_8008FBF8 — integer/decimal formatter (a0=ctx, a1=cmd)
 *   func_80090598 — floating-point formatter  (a0=ctx, a1=cmd)
 *   func_8008EEC4 — string length / write helper (a0=ptr)
 */

void func_8008FBF8(Unk *ctx, u8 cmd);
void func_80090598(Unk *ctx, u8 cmd);
s32  func_8008EEC4(Unk *ptr);

/*
 * stream_read_u32_aligned — read a 4-byte aligned u32 from stream.
 * Advances *stream past the consumed value.
 */
static u32 stream_read_u32_aligned(Unk **stream) {
    u32 cur = (u32)(uintptr_t)*stream;
    u32 aligned = (cur + 3) & ~3u;
    *stream = (Unk *)(uintptr_t)(aligned + 4);
    return *(u32 *)(uintptr_t)aligned;
}

/*
 * stream_read_u64_aligned — read an 8-byte aligned u64 from stream.
 * Respects alignment-hint bits in the raw pointer value (SN64 varargs ABI):
 *   ptr & 1: misaligned hint → advance by 7 (skip to next 8-byte boundary −
 *            then ldc1 reads from (ptr+7)−8 = ptr−1, net −15 offset; this
 *            matches SN64's "odd frame offset" slot convention)
 *   ptr & 2: 2-byte aligned hint → advance by 10 (ldc1 from ptr+10−8=ptr+2)
 *   else:    8-byte aligned → advance by 8
 * Returns pointer to where to call ldc1 -8(ret).
 */
static Unk *stream_advance_f64(Unk **stream) {
    u32 cur = (u32)(uintptr_t)*stream;
    u32 next;
    if (cur & 1) {
        next = cur + 7;
        *stream = (Unk *)(uintptr_t)next;
        return (Unk *)(uintptr_t)(next - 22); /* matches SN64 odd-slot ldc1 */
    } else if (cur & 2) {
        next = cur + 10;
        *stream = (Unk *)(uintptr_t)next;
        return (Unk *)(uintptr_t)(next - 40); /* addiu -0x28 = -40 */
    } else {
        u32 aligned = (cur + 7) & ~7u;
        next = aligned + 8;
        *stream = (Unk *)(uintptr_t)next;
        return (Unk *)(uintptr_t)next;
    }
}

/* nonmatching: non-standard ABI ($s0) + jtbl_8004CFFC (permanently) */
void gbiCmdDispatch(Unk *s0, u8 cmd, Unk **stream, u8 *buf) {
    u8 cmd8 = cmd & 0xFF;

    /* Prologue: clear context scratch words */
    *(s32 *)((u8 *)s0 + 0x0C) = 0;
    *(s32 *)((u8 *)s0 + 0x10) = 0;
    *(s32 *)((u8 *)s0 + 0x14) = 0;
    *(s32 *)((u8 *)s0 + 0x18) = 0;
    *(s32 *)((u8 *)s0 + 0x1C) = 0;
    *(s32 *)((u8 *)s0 + 0x20) = 0;

    if (cmd8 < 0x26) {
        /* Low-byte commands: write literal byte (0x25 is a special escape) */
        s32 off = *(s32 *)((u8 *)s0 + 0x0C);
        if (cmd8 == 0x25) {
            buf[off] = 0x25;
        } else {
            buf[off] = cmd8;
        }
        *(s32 *)((u8 *)s0 + 0x0C) = off + 1;
        return;
    }

    {
        u32 idx = cmd8 - 0x45;
        if (idx >= 0x34) {
            /* cmd 0x26..0x44 or 0x79+: write literal byte */
            s32 off = *(s32 *)((u8 *)s0 + 0x0C);
            buf[off] = cmd8;
            *(s32 *)((u8 *)s0 + 0x0C) = off + 1;
            return;
        }

        /* Table dispatch on cmd − 0x45 */
        switch (cmd8) {

        /* ---------------------------------------------------------------- */
        /* cmd=0x64 ('d'): 4-byte aligned read → write 1 byte to output    */
        /* ---------------------------------------------------------------- */
        case 0x64: {
            u32 val  = stream_read_u32_aligned(stream);
            s32 off  = *(s32 *)((u8 *)s0 + 0x0C);
            buf[off] = (u8)val;
            *(s32 *)((u8 *)s0 + 0x0C) = off + 1;
            break;
        }

        /* ---------------------------------------------------------------- */
        /* cmd=0x65 ('e'), cmd=0x6A ('j'):                                  */
        /* Read signed integer (width per s0->0x34), write sign char,       */
        /* call func_8008FBF8 (integer formatter).                           */
        /* ---------------------------------------------------------------- */
        case 0x65:
        case 0x6A: {
            u8 lmod = *(u8 *)((u8 *)s0 + 0x34);
            s32 hi, lo;

            if (lmod == 0x6C) {
                /* 'l': 4-byte aligned read, sign-extend to 64 bits */
                u32 raw  = stream_read_u32_aligned(stream);
                hi = (s32)raw >> 31;
                lo = (s32)raw;
            } else if (lmod == 0x4C) {
                /* 'L': 8-byte aligned read (two s32 words) */
                u32 cur  = (u32)(uintptr_t)*stream;
                u32 cur7 = cur + 7;
                u32 aln  = (cur7) & ~7u;
                u32 next = aln + 8;
                *stream  = (Unk *)(uintptr_t)next;
                hi = *(s32 *)(uintptr_t)aln;
                lo = *(s32 *)(uintptr_t)(aln + 4);
            } else {
                /* default: 4-byte aligned, sign-extend */
                u32 raw  = stream_read_u32_aligned(stream);
                hi = (s32)raw >> 31;
                lo = (s32)raw;
            }

            if (lmod == 0x68) {
                /* 'h': zero-extend lower 16 bits */
                hi = 0;
                lo = lo & 0xFFFF;
            }

            *(s32 *)((u8 *)s0 + 0x00) = hi;
            *(s32 *)((u8 *)s0 + 0x04) = lo;

            /* Write sign character based on hi and format flags */
            {
                s32 off   = *(s32 *)((u8 *)s0 + 0x0C);
                s32 flags = *(s32 *)((u8 *)s0 + 0x30);
                if (hi < 0) {
                    buf[off] = '-';
                    *(s32 *)((u8 *)s0 + 0x0C) = off + 1;
                } else if (flags & 0x2) {
                    buf[off] = '+';
                    *(s32 *)((u8 *)s0 + 0x0C) = off + 1;
                } else if (flags & 0x1) {
                    buf[off] = ' ';
                    *(s32 *)((u8 *)s0 + 0x0C) = off + 1;
                }
            }

            {
                s32 off = *(s32 *)((u8 *)s0 + 0x0C);
                *(u8 **)((u8 *)s0 + 0x08) = buf + off;
                func_8008FBF8(s0, cmd8);
            }
            break;
        }

        /* ---------------------------------------------------------------- */
        /* cmd=0x59 ('Y'), cmd=0x70 ('p'), cmd=0x76 ('v'):                  */
        /* Read unsigned value (width per s0->0x34), optional hex-prefix,   */
        /* call func_8008FBF8 (integer formatter).                           */
        /* ---------------------------------------------------------------- */
        case 0x59:
        case 0x70:
        case 0x76: {
            u8 lmod = *(u8 *)((u8 *)s0 + 0x34);
            s32 hi, lo;

            if (lmod == 0x6C) {
                u32 raw  = stream_read_u32_aligned(stream);
                hi = (s32)raw >> 31;
                lo = (s32)raw;
            } else if (lmod == 0x4C) {
                /* 8-byte: words stored hi=second, lo=first (big-endian order) */
                u32 cur  = (u32)(uintptr_t)*stream;
                u32 cur7 = cur + 7;
                u32 aln  = cur7 & ~7u;
                u32 next = aln + 8;
                *stream  = (Unk *)(uintptr_t)next;
                lo = *(s32 *)(uintptr_t)aln;        /* lw t9, -4(next)  = aln */
                hi = *(s32 *)(uintptr_t)(aln + 4);  /* lw t8, -8(next+4) ... */
                /* Note: asm stores t9→0x4 and t8→0x0 */
                { s32 tmp = hi; hi = lo; lo = tmp; }
            } else {
                u32 raw  = stream_read_u32_aligned(stream);
                hi = (s32)raw >> 31;
                lo = (s32)raw;
            }

            if (lmod == 0x68) {
                hi = 0;
                lo = lo & 0xFFFF;
            } else if (lmod == 0) {
                hi = 0;
                /* lo unchanged */
            }

            *(s32 *)((u8 *)s0 + 0x00) = hi;
            *(s32 *)((u8 *)s0 + 0x04) = lo;

            /* Optional hex prefix '0x' / '0X' */
            {
                s32 flags = *(s32 *)((u8 *)s0 + 0x30);
                if (flags & 0x8) {
                    s32 off = *(s32 *)((u8 *)s0 + 0x0C);
                    buf[off] = '0';
                    *(s32 *)((u8 *)s0 + 0x0C) = off + 1;
                    /* Write 'x' only if cmd is 0x78 or 0x58 — not active here */
                    if (cmd8 == 0x78 || cmd8 == 0x58) {
                        off = *(s32 *)((u8 *)s0 + 0x0C);
                        buf[off] = cmd8;
                        *(s32 *)((u8 *)s0 + 0x0C) = off + 1;
                    }
                }
            }

            {
                s32 off = *(s32 *)((u8 *)s0 + 0x0C);
                *(u8 **)((u8 *)s0 + 0x08) = buf + off;
                func_8008FBF8(s0, cmd8);
            }
            break;
        }

        /* ---------------------------------------------------------------- */
        /* cmd=0x45 ('E'), cmd=0x47 ('G'),                                  */
        /* cmd=0x66 ('f'), cmd=0x67 ('g'), cmd=0x68 ('h'):                  */
        /* Read f64 from stream (SN64 varargs alignment), optional sign,    */
        /* call func_80090598 (float formatter).                             */
        /* ---------------------------------------------------------------- */
        case 0x45:
        case 0x47:
        case 0x66:
        case 0x67:
        case 0x68: {
            u8 lmod = *(u8 *)((u8 *)s0 + 0x34);

            if (lmod == 0x4C) {
                /* 'L': 8-byte aligned double via SN64 alignment-hint logic */
                Unk *rd = stream_advance_f64(stream);
                f64 val;
                /* ldc1 reads from rd-8 in the 0x4C path */
                val = *(f64 *)((u8 *)rd - 8);
                *(f64 *)s0 = val;
            } else {
                /* default: 8-byte aligned double (same logic, different reg) */
                Unk *rd = stream_advance_f64(stream);
                f64 val = *(f64 *)((u8 *)rd - 8);
                *(f64 *)s0 = val;
            }

            /* Check sign bit via low halfword of stored double */
            {
                u16 hi16 = *(u16 *)s0;
                s32 off  = *(s32 *)((u8 *)s0 + 0x0C);
                s32 flags;
                if (hi16 & 0x8000) {
                    buf[off] = '-';
                    *(s32 *)((u8 *)s0 + 0x0C) = off + 1;
                } else {
                    flags = *(s32 *)((u8 *)s0 + 0x30);
                    if (flags & 0x2) {
                        buf[off] = '+';
                        *(s32 *)((u8 *)s0 + 0x0C) = off + 1;
                    } else if (flags & 0x1) {
                        buf[off] = ' ';
                        *(s32 *)((u8 *)s0 + 0x0C) = off + 1;
                    }
                }
            }

            {
                s32 off = *(s32 *)((u8 *)s0 + 0x0C);
                *(u8 **)((u8 *)s0 + 0x08) = buf + off;
                func_80090598(s0, cmd8);
            }
            break;
        }

        /* ---------------------------------------------------------------- */
        /* cmd=0x6F ('o'): write s0->0x2C to a pointer-sized output arg.   */
        /* The stream contains a pointer to the caller's output variable.   */
        /* Width: 'h'→s16, 'L'→s32 with hi=0, else→s32.                   */
        /* ---------------------------------------------------------------- */
        case 0x6F: {
            u8  lmod   = *(u8 *)((u8 *)s0 + 0x34);
            s32 count  = *(s32 *)((u8 *)s0 + 0x2C);
            u32 raw    = stream_read_u32_aligned(stream);
            void *ptr  = (void *)(uintptr_t)raw;

            if (lmod == 0x68) {
                *(s16 *)ptr = (s16)count;
            } else if (lmod == 0x4C) {
                /* 64-bit output: store (0, count) */
                *(s32 *)ptr = 0;
                *(s32 *)((u8 *)ptr + 4) = count;
            } else {
                *(s32 *)ptr = count;
            }
            break;
        }

        /* ---------------------------------------------------------------- */
        /* cmd=0x71 ('q'): 4-byte aligned read, sign-extend to 64-bit,     */
        /* call func_8008FBF8 with a1=0x78 ('x') for hex formatting.       */
        /* ---------------------------------------------------------------- */
        case 0x71: {
            u32 raw = stream_read_u32_aligned(stream);
            s32 hi  = (s32)raw >> 31;
            s32 lo  = (s32)raw;
            s32 off = *(s32 *)((u8 *)s0 + 0x0C);

            *(s32 *)((u8 *)s0 + 0x04) = lo;
            *(s32 *)((u8 *)s0 + 0x00) = hi;
            *(u8 **)((u8 *)s0 + 0x08) = buf + off;
            func_8008FBF8(s0, 0x78); /* 'x': hex format */
            break;
        }

        /* ---------------------------------------------------------------- */
        /* cmd=0x74 ('t'): read pointer from stream, call func_8008EEC4,   */
        /* store result to s0->0x14, clamped to min(result, s0->0x24).     */
        /* ---------------------------------------------------------------- */
        case 0x74: {
            u32 raw  = stream_read_u32_aligned(stream);
            Unk *ptr = (Unk *)(uintptr_t)raw;
            s32 ret, thresh;

            *(Unk **)((u8 *)s0 + 0x08) = ptr;
            ret    = func_8008EEC4(ptr);
            thresh = *(s32 *)((u8 *)s0 + 0x24);

            *(s32 *)((u8 *)s0 + 0x14) = ret;
            if (thresh < 0) {
                /* no clamp */
            } else if (ret > thresh) {
                /* clamp to threshold */
                *(s32 *)((u8 *)s0 + 0x14) = thresh;
            }
            break;
        }

        default: {
            /* Write literal cmd byte to output */
            s32 off = *(s32 *)((u8 *)s0 + 0x0C);
            buf[off] = cmd8;
            *(s32 *)((u8 *)s0 + 0x0C) = off + 1;
            break;
        }

        } /* switch (cmd8) */
    }
}
