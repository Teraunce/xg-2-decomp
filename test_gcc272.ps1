# test_gcc272.ps1
# Run: powershell -ExecutionPolicy Bypass -File test_gcc272.ps1

$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Path
$gccWin    = $scriptDir + "\xg2-decomp\tools\gcc272\gcc"
$srcWin    = $scriptDir + "\xg2_test.c"
$outWin    = $scriptDir + "\xg2_test.s"

if (-not (Test-Path $gccWin)) {
    Write-Host "ERROR: GCC not found at $gccWin" -ForegroundColor Red
    exit 1
}

# Convert C:\foo\bar -> /mnt/c/foo/bar
function wslpath($p) {
    $drive = $p.Substring(0,1).ToLower()
    $rest  = $p.Substring(2).Replace('\','/')
    return "/mnt/$drive$rest"
}

$gccWsl = wslpath $gccWin
$srcWsl = wslpath $srcWin
$outWsl = wslpath $outWin

# Write the test C file
$c = 'typedef int s32; typedef unsigned int u32;
typedef struct { s32 unk0; int pad[1]; s32 unk8; int pad2[1]; s32 unk10; } S;
s32 func_80081730(S*,s32*,S*,s32);
s32 func_80081B58(S *a0, s32 *a1) {
    s32 v = a0->unk8;
    if ((u32)v >= (u32)(a0->unk0 + a0->unk10)) return 0;
    *a1 = func_80081730(a0, a1, a0, v);
    a0->unk8 = v;
    return 1;
}'
Set-Content -Path $srcWin -Value $c -Encoding ASCII

Write-Host "Compiling with GCC 2.7.2..." -ForegroundColor Cyan

$gccDir = wslpath ($scriptDir + "\xg2-decomp\tools\gcc272")
$base = "chmod +x '$gccWsl' 2>/dev/null; '$gccWsl' -B'$gccDir/'"
$common = "-mips2 -mabi=32 -G0 -fno-pic -mno-abicalls -S '$srcWsl' -o '$outWsl'"
$bash = "$base $common"
$variants = @(
    @{ label = "-O2 (baseline)";       opt = "-O2" },
    @{ label = "-O1";                  opt = "-O1" },
    @{ label = "-O2 -fno-caller-saves"; opt = "-O2 -fno-caller-saves" }
)

foreach ($v in $variants) {
    Write-Host ""
    Write-Host ("--- " + $v.label + " ---") -ForegroundColor Yellow
    $cmd = "$base " + $v.opt + " $common"
    wsl bash -c $cmd
    if (Test-Path $outWin) {
        Get-Content $outWin | Where-Object {
            $_ -match 'subu|addiu|^func_|sw|move|jal|^\s+j ' -and
            $_ -notmatch "^#" -and $_.Trim() -ne ""
        }
    } else {
        Write-Host "  (no output)" -ForegroundColor Red
    }
}

Write-Host ""
Write-Host "=== Reference ===" -ForegroundColor Cyan
Write-Host "  subu/addiu sp, -24  (frame=0x18)  <- want this"
Write-Host "  sw ra, 20(sp)"
Write-Host "  NO sw s0/s1/s2 saves"
Write-Host "  t0 used across jal without save"
