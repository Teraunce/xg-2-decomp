#!/usr/bin/env bash
# XG2 Decomp - first-time setup
set -e

echo "=== XG2 Decomp Setup ==="

# Python tools
echo "[1/3] Installing Python tools..."
pip install splat64 spimdisasm m2c --break-system-packages -q

# MIPS binutils
echo "[2/3] Installing MIPS binutils..."
if ! which mips-linux-gnu-as &>/dev/null; then
    sudo apt-get install -y binutils-mips-linux-gnu
fi

# IDO (optional, for byte-matching C compilation)
echo "[3/3] IDO 7.1 (optional, for byte-matching C decompilation):"
echo "   https://github.com/decompals/ido-static-recomp"
echo "   Download and put ido/cc, ido/as in tools/ido/"

echo ""
echo "Setup done! Run: make split && make && make verify"
