#!/usr/bin/env bash
# sn64_diagnose.sh — test a single function and report each step
# Usage: bash tools/sn64_diagnose.sh [func_name]
# Run from inside xg2-decomp/

set -uo pipefail
cd "$(dirname "$0")/.."

TOOLS_DIR="$(cd .. && pwd)/tools"
GCC="$TOOLS_DIR/sn64/gcc"
AS="$TOOLS_DIR/mips-binutils/bin/mips-linux-gnu-as"
OC="$TOOLS_DIR/mips-binutils/bin/mips-linux-gnu-objcopy"
TRIM="tools/trim_ido.py"
export LD_LIBRARY_PATH="$TOOLS_DIR/mips-binutils/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"

FUNC="${1:-func_8004D4B0}"
WORK="/tmp/sn64_diag_$$"
mkdir -p "$WORK"
trap 'rm -rf "$WORK"' EXIT

echo "=== Diagnosing: $FUNC ==="
echo "TOOLS_DIR: $TOOLS_DIR"
echo ""

C_SRC="src/main/main/$FUNC.c"
ASM_SRC="asm/main/main/$FUNC.s"

echo "--- C source ---"
cat "$C_SRC"
echo ""

# Copy to /tmp to avoid WSL2 EOVERFLOW (32-bit cpp can't stat /mnt/c/ paths)
cp -r include/ "$WORK/include/"
cp "$C_SRC" "$WORK/$FUNC.c"

echo "--- Step 1a: SN64 compile to assembly (-S) ---"
"$GCC" -B "$TOOLS_DIR/sn64/" -S -O2 -mips2 -G0 -fno-exceptions -w -I "$WORK/include" \
    "$WORK/$FUNC.c" -o "$WORK/$FUNC.s" 2>&1
echo "Exit: $?"
echo ""
if [ -f "$WORK/$FUNC.s" ]; then
    echo "--- Generated SN64 assembly ---"
    cat "$WORK/$FUNC.s"
    echo ""
fi

echo "--- Step 1b: Assemble with mips-linux-gnu-as ---"
"$AS" -march=vr4300 -mabi=32 -G0 -EB -no-pad-sections \
    -o "$WORK/padded.o" "$WORK/$FUNC.s" 2>&1
echo "Exit: $?"
[ -f "$WORK/padded.o" ] && echo "Output: $(wc -c < "$WORK/padded.o") bytes" || echo "NOT PRODUCED"
echo ""

echo "--- Step 2: trim_ido.py ---"
python3 "$TRIM" "$WORK/padded.o" "$WORK/trimmed.o" "$ASM_SRC" 2>&1
echo "Exit: $?"
"$OC" -O binary -j .text "$WORK/trimmed.o" "$WORK/trimmed.text" 2>/dev/null || true
[ -f "$WORK/trimmed.text" ] && echo "trimmed .text: $(wc -c < "$WORK/trimmed.text") bytes" || echo "N/A"
echo ""

echo "--- Step 3: assemble reference asm ---"
"$AS" -march=vr4300 -mabi=32 -G0 -EB -no-pad-sections \
    -I include -o "$WORK/ref.o" "$ASM_SRC" 2>&1
"$OC" -O binary -j .text "$WORK/ref.o" "$WORK/ref.text" 2>/dev/null || true
[ -f "$WORK/ref.text" ] && echo "ref .text: $(wc -c < "$WORK/ref.text") bytes" || echo "N/A"
echo ""

echo "--- Step 4: compare ---"
if [ -s "$WORK/trimmed.text" ] && [ -s "$WORK/ref.text" ]; then
    if cmp -s "$WORK/trimmed.text" "$WORK/ref.text"; then
        echo "✓ MATCH"
    else
        echo "✗ MISMATCH"
        diff <(xxd "$WORK/trimmed.text") <(xxd "$WORK/ref.text") | head -40
    fi
else
    echo "One or both .text files missing/empty"
fi
