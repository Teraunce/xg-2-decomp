#!/usr/bin/env bash
# sn64_match_all.sh — batch-compile all C files with SN64 and report matches
# Run from the repo root: bash sn64_match_all.sh
# Results written to sn64_matches.txt and sn64_mismatches.txt

set -e
REPO=$(cd "$(dirname "$0")" && pwd)
TOOLS_DIR="$REPO/../tools"
export LD_LIBRARY_PATH="$TOOLS_DIR/mips-binutils/lib:$LD_LIBRARY_PATH"

CC="$TOOLS_DIR/sn64/gcc"
CFLAGS="-O2 -mips2 -G0 -I include"
AS="$TOOLS_DIR/mips-binutils/bin/mips-linux-gnu-as"
ASFLAGS="-march=vr4300 -mabi=32"
OBJCOPY="$TOOLS_DIR/mips-binutils/bin/mips-linux-gnu-objcopy"
PYTHON=python3
TRIM_TOOL="$TOOLS_DIR/trim_ido.py"

BUILD_C=/tmp/sn64_match_check/c
BUILD_S=/tmp/sn64_match_check/s
mkdir -p "$BUILD_C" "$BUILD_S"

MATCHES=()
MISMATCHES=()
ERRORS=()

SRC_DIR="$REPO/src/main/main"
ASM_DIR="$REPO/asm/main/main"

total=$(ls "$SRC_DIR"/*.c 2>/dev/null | wc -l)
count=0

for csrc in "$SRC_DIR"/*.c; do
  func=$(basename "$csrc" .c)
  stub="$ASM_DIR/$func.s"
  count=$((count+1))
  printf "\r[%d/%d] %s        " "$count" "$total" "$func"

  # Skip if no matching .s stub
  [ -f "$stub" ] || { ERRORS+=("$func: no stub"); continue; }

  # Compile with SN64
  padded="$BUILD_C/$func.padded.o"
  cobj="$BUILD_C/$func.c.o"
  if ! "$CC" $CFLAGS -c -o "$padded" "$csrc" 2>/dev/null; then
    ERRORS+=("$func: compile error")
    continue
  fi
  if ! "$PYTHON" "$TRIM_TOOL" "$padded" "$cobj" "$stub" 2>/dev/null; then
    ERRORS+=("$func: trim error")
    continue
  fi

  # Assemble stub
  sobj="$BUILD_S/$func.s.o"
  if ! "$AS" $ASFLAGS -I include -o "$sobj" "$stub" 2>/dev/null; then
    ERRORS+=("$func: assemble error")
    continue
  fi

  # Extract .text and compare
  "$OBJCOPY" -O binary -j .text "$cobj" "$BUILD_C/$func.text" 2>/dev/null || { ERRORS+=("$func: objcopy c"); continue; }
  "$OBJCOPY" -O binary -j .text "$sobj" "$BUILD_S/$func.text" 2>/dev/null || { ERRORS+=("$func: objcopy s"); continue; }

  if cmp -s "$BUILD_C/$func.text" "$BUILD_S/$func.text"; then
    MATCHES+=("$func")
  else
    MISMATCHES+=("$func")
  fi
done

echo ""
echo "=============================="
echo "SN64 match results"
echo "=============================="
echo "MATCH:    ${#MATCHES[@]}"
echo "MISMATCH: ${#MISMATCHES[@]}"
echo "ERRORS:   ${#ERRORS[@]}"
echo ""

printf "%s\n" "${MATCHES[@]}"  > "$REPO/sn64_matches.txt"
printf "%s\n" "${MISMATCHES[@]}" > "$REPO/sn64_mismatches.txt"
printf "%s\n" "${ERRORS[@]}"   > "$REPO/sn64_errors.txt"

echo "Matched functions saved to sn64_matches.txt"
echo "Mismatch list saved to sn64_mismatches.txt"
