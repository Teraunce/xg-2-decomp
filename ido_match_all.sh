#!/usr/bin/env bash
# ido_match_all.sh — compile all C files with IDO, compare against asm stubs
# Run from the "old SN64" repo root:
#   bash ../../ido_match_all.sh
# Results: ido_matches.txt, ido_mismatches.txt, ido_errors.txt, ido_summary.txt

set -euo pipefail
REPO=$(cd "$(dirname "$0")" && pwd)

# Allow running from inside the old SN64 folder too
if [ -f "$REPO/Makefile" ] && grep -q "xg2" "$REPO/Makefile" 2>/dev/null; then
  OLD_SN64="$REPO"
  TOOLS_DIR=$(cd "$REPO/.." && pwd)/tools
else
  OLD_SN64="$REPO/old SN64"
  TOOLS_DIR="$REPO/tools"
fi

export LD_LIBRARY_PATH="$TOOLS_DIR/mips-binutils/lib:${LD_LIBRARY_PATH:-}"
CC="$TOOLS_DIR/ido/cc"
CFLAGS="-O2 -mips2 -G0 -Wab,-r4300_mul -non_shared -Xcpluscomm -woff 649,838,712 -signed -I include"
TRIM="$TOOLS_DIR/trim_ido.py"
OBJCOPY="$TOOLS_DIR/mips-binutils/bin/mips-linux-gnu-objcopy"
AS="$TOOLS_DIR/mips-binutils/bin/mips-linux-gnu-as"
ASFLAGS="-march=vr4300 -mabi=32"

TMPDIR=/tmp/ido_match_$$
mkdir -p "$TMPDIR"

cd "$OLD_SN64"
BUILD="build/main"
mkdir -p "$BUILD/src/main/main" "$BUILD/asm/main/main"

errors=(); matches=(); mismatches=()
total=$(ls src/main/main/func_*.c 2>/dev/null | wc -l)
count=0

for csrc in src/main/main/func_*.c; do
  func=$(basename "$csrc" .c)
  stub="asm/main/main/$func.s"
  count=$((count+1))
  printf "\r[%d/%d] %-40s" "$count" "$total" "$func"

  [ -f "$stub" ] || { errors+=("$func: no stub"); continue; }

  cobj="$BUILD/src/main/main/$func.c.o"

  # Compile with IDO if not already done
  if [ ! -f "$cobj" ]; then
    if ! "$CC" $CFLAGS -c -o "$cobj.padded" "$csrc" 2>/dev/null; then
      errors+=("$func: compile error")
      continue
    fi
    if ! python3 "$TRIM" "$cobj.padded" "$cobj" "$stub" 2>/dev/null; then
      errors+=("$func: trim error")
      rm -f "$cobj.padded"
      continue
    fi
    rm -f "$cobj.padded"
  fi

  # Assemble stub if needed
  sobj="$BUILD/asm/main/main/$func.s.o"
  if [ ! -f "$sobj" ]; then
    if ! "$AS" $ASFLAGS -I include -o "$sobj" "$stub" 2>/dev/null; then
      errors+=("$func: assemble error")
      continue
    fi
  fi

  # Extract .text and compare
  "$OBJCOPY" -O binary -j .text "$cobj" "$TMPDIR/$func.c.text" 2>/dev/null || { errors+=("$func: objcopy-c"); continue; }
  "$OBJCOPY" -O binary -j .text "$sobj" "$TMPDIR/$func.s.text" 2>/dev/null || { errors+=("$func: objcopy-s"); continue; }

  if cmp -s "$TMPDIR/$func.c.text" "$TMPDIR/$func.s.text"; then
    matches+=("$func")
  else
    # Record size delta too
    csz=$(wc -c < "$TMPDIR/$func.c.text")
    ssz=$(wc -c < "$TMPDIR/$func.s.text")
    mismatches+=("$func c=$csz s=$ssz")
  fi
done

echo ""
echo "=============================="
echo "IDO match results"
echo "=============================="
echo "MATCH:    ${#matches[@]}"
echo "MISMATCH: ${#mismatches[@]}"
echo "ERRORS:   ${#errors[@]}"

printf "%s\n" "${matches[@]}"    > ido_matches.txt
printf "%s\n" "${mismatches[@]}" > ido_mismatches.txt
printf "%s\n" "${errors[@]}"     > ido_errors.txt

{
  echo "MATCH:    ${#matches[@]}"
  echo "MISMATCH: ${#mismatches[@]}"
  echo "ERRORS:   ${#errors[@]}"
} > ido_summary.txt

echo ""
echo "Results saved to ido_matches.txt / ido_mismatches.txt / ido_errors.txt"
rm -rf "$TMPDIR"
