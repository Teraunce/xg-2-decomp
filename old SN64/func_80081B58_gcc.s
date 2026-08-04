	.verstamp	7 10
	.option	pic0
	.text	
	.align	2
	.file	2 "/tmp/func_80081B58_gcc.c"
	.globl	func_80081B58
	.loc	2 14
 #  14	s32 func_80081B58(Struct80081B58 *arg0, s32 *arg1) {
	.ent	func_80081B58 2
func_80081B58:
	.option	O1
	subu	$sp, 32
	sw	$31, 20($sp)
	sw	$4, 32($sp)
	sw	$5, 36($sp)
	.mask	0x80000000, -12
	.frame	$sp, 32, $31
	.loc	2 14
	.loc	2 15
 #  15	    s32 unk8 = arg0->unk8;
	lw	$14, 32($sp)
	lw	$15, 8($14)
	sw	$15, 28($sp)
	.loc	2 16
 #  16	    if ((u32)unk8 >= (u32)(arg0->unk0 + arg0->unk10)) return 0;
	lw	$24, 0($14)
	lw	$25, 16($14)
	addu	$8, $24, $25
	bltu	$15, $8, $32
	.loc	2 16
	move	$2, $0
	b	$33
$32:
	.loc	2 17
 #  17	    *arg1 = func_80081730(arg0, arg1, arg0, unk8);
	lw	$9, 32($sp)
	move	$4, $9
	lw	$5, 36($sp)
	move	$6, $9
	lw	$7, 28($sp)
	.livereg	0x0F00000E,0x00000000
	jal	func_80081730
	lw	$10, 36($sp)
	sw	$2, 0($10)
	.loc	2 18
 #  18	    arg0->unk8 = unk8;
	lw	$11, 28($sp)
	lw	$12, 32($sp)
	sw	$11, 8($12)
	.loc	2 19
 #  19	    return 1;
	li	$2, 1
$33:
	.livereg	0x2000FF0E,0x00000FFF
	lw	$31, 20($sp)
	addu	$sp, 32
	j	$31
	.end	func_80081B58
