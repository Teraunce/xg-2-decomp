	.file	1 "/mnt/c/Users/Teraunce/AppData/Roaming/Claude/local-agent-mode-sessions/06f53cfa-011f-4ff0-8fd6-80a52e23784f/ac2bd788-cf8b-4f87-8759-d312ecb49aac/local_59aa4e2b-bcaa-4387-bfd3-68bc7bb752e6/outputs/xg2_test.c"

 # GNU C 2.7.2 [AL 1.1, MM 40] GNU MIPS/ELF compiled by GNU C

 # Cc1 defaults:
 # -mgas

 # Cc1 arguments (-G value = 0, Cpu = 6000, ISA = 2):
 # -mfp32 -mgp32 -G0 -quiet -dumpbase -mips2 -mabi=32 -mno-abicalls -O2
 # -fno-caller-saves -fno-pic -o

	.version	"01.01"
gcc2_compiled.:
	.text
	.align	2
	.globl	func_80081B58
	.type	 func_80081B58,@function
	.ent	func_80081B58
func_80081B58:
	.frame	$sp,32,$31		# vars= 0, regs= 4/0, args= 16, extra= 0
	.mask	0x80070000,-4
	.fmask	0x00000000,0
	subu	$sp,$sp,32
	sw	$16,16($sp)
	move	$16,$4
	sw	$31,28($sp)
	sw	$18,24($sp)
	sw	$17,20($sp)
	lw	$2,0($16)
	lw	$3,16($16)
	lw	$17,8($16)
	addu	$2,$2,$3
	sltu	$2,$17,$2
	.set	noreorder
	.set	nomacro
	beq	$2,$0,.L2
	move	$18,$5
	.set	macro
	.set	reorder

	move	$6,$16
	.set	noreorder
	.set	nomacro
	jal	func_80081730
	move	$7,$17
	.set	macro
	.set	reorder

	sw	$2,0($18)
	li	$2,0x00000001		# 1
	.set	noreorder
	.set	nomacro
	j	.L3
	sw	$17,8($16)
	.set	macro
	.set	reorder

.L2:
	move	$2,$0
.L3:
	lw	$31,28($sp)
	lw	$18,24($sp)
	lw	$17,20($sp)
	lw	$16,16($sp)
	addu	$sp,$sp,32
	j	$31
	.end	func_80081B58
.Lfe1:
	.size	 func_80081B58,.Lfe1-func_80081B58
	.ident	"GCC: (GNU) 2.7.2"
