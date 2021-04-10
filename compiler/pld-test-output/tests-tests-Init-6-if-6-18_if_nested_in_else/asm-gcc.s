	.file	"input.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$8, -4(%rbp)
	movl	$1, -8(%rbp)
	cmpl	$10, -4(%rbp)
	jle	.L2
	movl	$7, -8(%rbp)
	jmp	.L3
.L2:
	cmpl	$7, -4(%rbp)
	jle	.L4
	movl	$3, -8(%rbp)
	jmp	.L3
.L4:
	movl	$4, -8(%rbp)
.L3:
	movl	-8(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
