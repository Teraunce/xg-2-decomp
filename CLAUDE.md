# Extreme-G 2 (XG2) Decompilation — Project Guide

## Goal

Decompile all ~500+ functions in Extreme-G 2 (N64, 1997) from MIPS assembly to
byte-matching C source, using the original SN Systems SN64 compiler.  The build
produces a ROM identical to `baserom.z64` (SHA1 `ed0a50086ef9a89f5b445c20ab6f365165959630`).

## Current Status (as of 2026-07-27)

| Metric | Count |
|---|---|
| C source files | 453 |
| Byte-matching functions (C → .c.o in xg2_main.ld) | **20** |
| Files with compiled-but-nonmatching C | ~433 |
| Files with parse errors or empty stubs | 0 |
| ROM byte-exact match | ✅ yes (IDO build) |

The 20 matched functions: `func_8004EF5C`, `func_800502B8`, `func_800502D4`,
`func_8005BDB4`, `func_8007A8E0`, `func_8007AC38`, `func_8007B7D8`,
`func_8007E5E8`, `func_8007EAE8`, `func_80082818`, `func_80082E98`,
`func_80082EDC`, `func_80082F30`, `func_800843AC`, `func_80086D28`,
`func_80087D28`, `func_80087DBC`, `func_8008E458`, `func_8008E4EC`,
`func_8008EE18`.

---

## Compiler

The game was compiled with **SN Systems SN64 (GCC 2.7.2 Cygnus SN64.X)**.

Evidence: `jr $ra` with `addiu $sp` in delay slot; `$ra` saved at frame−8 for
single-ra functions (tight packing); `andi` directly into result register.

The SN64 binary lives at `tools/sn64/gcc` and requires **32-bit x86 support**:
```bash
# Ubuntu/Debian/WSL2 — enable 32-bit once:
sudo dpkg --add-architecture i386
sudo apt-get install -y libc6:i386
```

**IDO 7.1** (`tools/ido/cc`) is the default build compiler but does **not**
produce byte-matching output.  It is used only so `make` always succeeds for
syntax checking.  IDO 5.3 (`tools/ido53/cc`) is also available; also non-matching.

---

## Build

```bash
# Full ROM build (IDO 7.1 fallback — always byte-exact because nonmatching
# functions still use .s.o asm stubs, not .c.o C output)
make

# Verify ROM matches baserom.z64
make verify          # runs sha1sum + cmp

# Test a single function for byte-match with SN64
make CC_VER=sn64 match_check FUNC=func_8004D138

# Run SN64 against ALL C files, patch xg2_main.ld with new matches
bash tools/sn64_match_all.sh

# Main-block only link + verify (faster than full ROM)
make verify_main
```

Output: `build/xg2.z64`  
ELF map: `build/xg2.map`

---

## Linker Scripts

**`xg2.ld`** — full ROM build (boot + main block + assets).

**`xg2_main.ld`** — main decompressed block only (0x8004BA20–0x8009xxxx).
- Non-matched functions: `build/main/asm/main/main/func_XXXX.s.o(.text)`
- Byte-matched functions: `build/main/src/main/main/func_XXXX.c.o(.text)`

To promote a function from nonmatching to matched, `sn64_match_all.sh`
automatically patches this file.  Manual edit: change `.s.o` → `.c.o` for all
four section entries (.text, .data, .rodata, .bss).

---

## File Layout

```
baserom.z64             — reference ROM (12 MB)
xg2.ld                  — full ROM linker script
xg2_main.ld             — main block linker script (edit to promote matches)
Makefile
NOTES.md                — low-level technical notes

include/
  ultra64.h             — N64 SDK types + BREAK/M2C macros
  types.h / unk.h       — Unk struct, s8/u8/s32/f32 typedefs
  os.h                  — OSThread context block (from exception handler analysis)
  n64_hardware.h        — RDP/RSP MMIO addresses
  audio.h / video.h     — subsystem headers

src/main/main/          — 453 C source files (one per .s file)
  entry.c               — empty; all data defined in asm/main/main/entry.s
  func_XXXXXXXX.c       — each contains one or more functions

asm/main/main/          — 453+ .s stub files (spimdisasm output)
  func_XXXXXXXX.s       — MIPS assembly; nonmatching/alabel/glabel directives

tools/
  sn64/gcc              — SN64 compiler (32-bit x86)
  ido/cc                — IDO 7.1 (fallback, non-matching)
  ido53/cc              — IDO 5.3 (also non-matching)
  mips-binutils/        — mips-linux-gnu-{as,ld,objcopy,objdump}
  sn64_match_all.sh     — batch match + patch xg2_main.ld
  trim_ido.py           — strips IDO .text padding after compile
  verify_boot.py        — verifies boot block byte-match
  verify_decomp.py      — verifies main block byte-match
```

---

## Decompilation Workflow

### 1. Run m2c on a function

```bash
python3 tools/m2c.py asm/main/main/func_XXXXXXXX.s \
    --target mips --asm-function func_XXXXXXXX \
    --structs --pointer-style-left > /tmp/out.c
```

Paste the output into `src/main/main/func_XXXXXXXX.c`.

### 2. Fix common m2c failures

| Error | Cause | Fix |
|---|---|---|
| `Found jr instruction` | Jump table (`jr $reg`) | Write `switch` using jtbl entries from `entry.s` |
| `Cannot find branch target funcXXXX` | Branch back to own glabel | Translate as `do { ... } while (cond)` |
| `Cannot find branch target .LXXXXXXXX` | Cross-function backward branch | Handwritten MIPS; write empty stub |
| `Last instruction missing delay slot` | 4-byte fragment | `if (cond) return;` or similar |
| `Unable to determine jump table` | Same as Found jr | Write switch |
| `Label refers to a delay slot` | m2c can't express construct | Write stub, keep as nonmatching |
| `Failed to parse instruction` | Bogus instruction (bltz to OS) | Write stub for whole function |
| `Function D_XXXX contains no instructions` | Rodata label, not a function | Remove failure comment; symbol lives in entry.s |

### 3. Test with SN64

```bash
make CC_VER=sn64 match_check FUNC=func_XXXXXXXX
```

This compiles `src/main/main/func_XXXXXXXX.c` with SN64, assembles the .s stub,
and diffs the `.text` sections.  Output is ✓ MATCH or a hex diff.

### 4. Promote on match

`sn64_match_all.sh` handles this automatically.  Manual: edit `xg2_main.ld`,
replace all four `.s.o` entries for the function with `.c.o`.

---

## Key Technical Patterns

### GETTER_NOJR (8-byte functions, permanently nonmatching)

Functions that load a global into a register and fall through to the next
function (no `jr $ra`).  SN64 fall-through optimization — cannot be expressed in
standard C.  Kept as asm stubs.  Identified by `lui + lw/lwc1` with no `jr $ra`
in the 8 bytes.

Example: `func_80087D78` (loads `D_80096370` into `$t6` for `func_80087D80`).

### Branch-back-to-self (do-while loops)

m2c fails when a `bnez`/`beqz` targets the function's own glabel.  Translate as
`do { ... } while (condition)` where the entire body from the glabel is the loop.

```c
void func_80061AD0(s32 *arg0, s32 arg1, s32 arg2) {
    do { *arg0++ = arg1; } while (arg2-- != 0);
}
```

### Jump tables in entry.s

All `jtbl_8004Cxxx` tables are defined as `dlabel` entries in
`asm/main/main/entry.s`, NOT inline with the function.  When m2c reports
"Found jr instruction", grep entry.s for the table name to get the address array.

```bash
grep -A 12 "dlabel jtbl_8004CF38" asm/main/main/entry.s
```

Each entry is a target address.  Index 0 = case 0, etc.  Then trace what each
target address does in the .s file to write the switch cases.

### Handwritten MIPS (stays as asm forever)

Functions using `mtc0`/`mfc0`, `sd`/`ld` (64-bit), `$k0`/`$k1` (kernel regs),
or cross-function backward branches cannot be expressed in C.  Write an empty
stub and keep the `nonmatching` directive in the .s file:

```c
static void func_80076000(void) {
    /* handwritten: exception vector — mtc0/$k0/jr — see asm stub */
}
```

### Delay-slot fragments (4-byte functions)

Functions that are only 4 bytes (one instruction; delay slot is in the following
function).  m2c reports "Last instruction missing delay slot."  Write the minimal
C equivalent:

```c
void func_80056EA8(s32 arg0, s32 arg1, s32 arg2) {
    if (arg0 == arg2) { return; }
}
```

### M2C helper macros (defined in ultra64.h)

```c
#define M2C_BREAK(n)              BREAK(n)
#define M2C_MEMCPY_ALIGNED(d,s,n) memcpy((void*)(d),(const void*)(s),(n))
#define M2C_ERROR(x)              ((Unk *)0)   /* define locally per-file */
```

`M2C_ERROR` wraps m2c's "Read from unset register" or unknown-instruction
placeholders.  It's defined locally in files that need it, not in ultra64.h.

---

## Common Compiler Quirks (SN64 vs IDO)

- **`jr $ra` in delay slot of `addiu $sp, $sp, N`** — SN64 style.  IDO uses a
  separate `jr $ra` then `addiu` in the delay slot.

- **`$ra` at frame offset -8** — for 2-save-reg functions, SN64 packs `$ra` at
  the top of the frame (sp + frame_size - 8), not at a fixed offset.

- **`andi` directly into destination** — SN64 emits `andi $v0, $a0, 0xFF`
  without a temp.  IDO goes via an intermediate.

- **`MULTU_HI` / `DIVU` patterns** — SN64 emits `mult`/`multu` + `mfhi`/`mflo`
  inline.  m2c generates `MULTU_HI(a, b)` macros for the high-word result.

- **Float args beyond $a3** — go on the stack at `sp+0x10+` in o32 ABI.

- **Non-standard register passing** — some functions receive args in `$t6` or
  other temp registers (SN64 optimizer inlining artifact).  These functions are
  permanently nonmatching in C.

---

## ROM Structure

```
0x000000 – 0x000040   N64 header (ipl3 + entry vector)
0x000040 – 0x001000   IPL3 boot code
0x001000 – 0x005000   Boot block (boot.s + init.s)
0x005000 – 0x054B20   Compressed main block (LZSS)
0x054B20 – end        Assets / overlays
```

The compressed main block decompresses to ~305 KB at 0x8004BA20–0x800977FF.
`assets/boot/compressed_main.bin` is the original compressed blob used for
linking; `assets/boot/decompressed_main.bin` is the reference uncompressed image.

---

## Splat Config

`.splat/xg2.yaml` — controls how the ROM is split into .s stub files.
Regenerate stubs (destructive): `python3 tools/splat.py .splat/xg2.yaml`

`asm/main/main/` has one .s file per function, named by address.  Each contains
`nonmatching funcXXXX, <size>` + `glabel funcXXXX` + the MIPS instructions.

---

## Session History (summarised)

1. ROM analysed, splat config created, build system set up — ROM byte-matches.
2. 581 undefined symbols resolved (D_ data + func_ addresses in symbol_addrs.txt).
3. 6 cross-function .L label references fixed.
4. xg2_main.elf linked and verified.
5. IDO toolchain confirmed; first batch of leaf functions decompiled.
6. 135 `sw $ra, 0x14($sp)` pattern functions decompiled to C.
7. SN64 confirmed as the true matching compiler.
8. ~46% of C files had compile errors — fixed.
9. Remaining asm-only functions decompiled.
10. `include/os.h` written from exception handler analysis.
11. SFX subsystem decompiled.
12. **41 parse-error C files fixed** (every file now has at least one compilable
    function; all 453 C files compile with zero errors under both GCC and IDO).
