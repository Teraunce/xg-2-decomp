#!/usr/bin/env bash
# sn64_match_all.sh — byte-match all decompiled C files using SN64 and patch xg2_main.ld
# Usage: bash tools/sn64_match_all.sh

set -euo pipefail
cd "$(dirname "$0")/.."

TOOLS_DIR="$(cd .. && pwd)/tools"
GCC="$TOOLS_DIR/sn64/gcc"
AS="$TOOLS_DIR/mips-binutils/bin/mips-linux-gnu-as"
OC="$TOOLS_DIR/mips-binutils/bin/mips-linux-gnu-objcopy"
TRIM="tools/trim_ido.py"
LD_SCRIPT="xg2_main.ld"
export LD_LIBRARY_PATH="$TOOLS_DIR/mips-binutils/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"

echo "=== SN64 match-all ==="
echo "TOOLS_DIR: $TOOLS_DIR"
echo ""

[ -f "$GCC" ] || { echo "ERROR: $GCC not found"; exit 1; }
[ -f "$AS"  ] || { echo "ERROR: $AS not found"; exit 1; }

if ! "$GCC" -B "$TOOLS_DIR/sn64/" --version &>/dev/null; then
    echo "ERROR: Cannot execute $GCC (need 32-bit support)"
    echo "  Ubuntu/Debian/WSL2: sudo dpkg --add-architecture i386 && sudo apt-get install -y libc6:i386"
    exit 1
fi

echo "Compiler : $("$GCC" --version 2>&1 | head -1)"
echo "Assembler: $("$AS"  --version 2>&1 | head -1)"
echo ""

# ── temp workspace: use /tmp to avoid WSL2 EOVERFLOW on /mnt/c/ paths ──────
WORK="/tmp/xg2_sn64_$$"
mkdir -p "$WORK"
trap 'rm -rf "$WORK"' EXIT

# Copy include/ to /tmp once — all compilations share it
cp -r include/ "$WORK/include/"

# ── collect candidates ──────────────────────────────────────────────────────
ALREADY_C=$(grep "build/main/src/main/main/" "$LD_SCRIPT" \
    | sed 's|.*src/main/main/||;s|\.c\.o.*||' | sort -u)

mapfile -t CANDIDATES < <(
    ls src/main/main/*.c | sed 's|src/main/main/||;s|\.c||' | sort |
    while read -r func; do
        echo "$ALREADY_C" | grep -qxF "$func" && continue
        [ -f "asm/main/main/$func.s" ] || continue
        echo "$func"
    done
)

TOTAL=${#CANDIDATES[@]}
echo "Candidates : $TOTAL"
echo "Already C  : $(echo "$ALREADY_C" | grep -c . || true)"
echo ""

mkdir -p build/main/asm/main/main

MATCHES=()
COUNT=0

for func in "${CANDIDATES[@]}"; do
    COUNT=$((COUNT + 1))

    ASM_SRC="asm/main/main/$func.s"
    C_PAD="$WORK/$func.padded.o"
    C_OBJ="$WORK/$func.c.o"
    S_OBJ="$WORK/$func.s.o"
    C_TXT="$WORK/$func.c.text"
    S_TXT="$WORK/$func.s.text"

    # Copy C file to /tmp to avoid EOVERFLOW on /mnt/c/
    cp "src/main/main/$func.c" "$WORK/$func.c"

    # 1a. Compile with SN64 -S to get assembly (avoids GCC invoking system 'as')
    "$GCC" -B "$TOOLS_DIR/sn64/" -S -O2 -mips2 -G0 -fno-exceptions -w -I "$WORK/include" \
        "$WORK/$func.c" -o "$WORK/$func.s" 2>/dev/null || continue

    # 1b. Assemble with mips-linux-gnu-as (64-bit, handles SGI MIPS directives)
    "$AS" -march=vr4300 -mabi=32 -G0 -EB \
        -o "$C_PAD" "$WORK/$func.s" 2>/dev/null || continue

    # 2. Trim padding
    python3 "$TRIM" "$C_PAD" "$C_OBJ" "$ASM_SRC" 2>/dev/null || continue

    # 3. Assemble reference (mips-linux-gnu-as is 64-bit, no EOVERFLOW issue)
    "$AS" -march=vr4300 -mabi=32 -G0 -EB -no-pad-sections \
          -I include -o "$S_OBJ" "$ASM_SRC" 2>/dev/null || continue

    # 4. Compare .text
    "$OC" -O binary -j .text "$C_OBJ" "$C_TXT" 2>/dev/null || continue
    "$OC" -O binary -j .text "$S_OBJ" "$S_TXT" 2>/dev/null || continue
    [ -s "$C_TXT" ] && [ -s "$S_TXT" ] || continue

    if cmp -s "$C_TXT" "$S_TXT"; then
        MATCHES+=("$func")
        printf "  ✓ %-40s  [%d/%d]\n" "$func" "$COUNT" "$TOTAL"
    fi

    (( COUNT % 50 == 0 )) && echo "  ... [$COUNT/$TOTAL, ${#MATCHES[@]} matches]"
done

echo ""
echo "════════════════════════════════════════"
echo "Results: ${#MATCHES[@]} new matches / $TOTAL checked"
echo "════════════════════════════════════════"

[ ${#MATCHES[@]} -eq 0 ] && { echo "No new matches."; exit 0; }

echo ""
echo "Patching $LD_SCRIPT ..."
cp "$LD_SCRIPT" "${LD_SCRIPT}.bak"

python3 - "$LD_SCRIPT" "${MATCHES[@]}" << 'PYEOF'
import sys
ld_path, matches = sys.argv[1], set(sys.argv[2:])
content = open(ld_path).read()
replaced = 0
for func in matches:
    for sect in (".text", ".data", ".rodata", ".bss"):
        old = f"build/main/asm/main/main/{func}.s.o({sect});"
        new = f"build/main/src/main/main/{func}.c.o({sect});"
        if old in content:
            content = content.replace(old, new)
            if sect == ".text": replaced += 1
open(ld_path, 'w').write(content)
print(f"  Switched {replaced} functions to C in linker script.")
PYEOF

echo ""
printf '  %s\n' "${MATCHES[@]}"
echo ""
echo "Backup: ${LD_SCRIPT}.bak"
echo "Verify: make main_elf && make verify"
