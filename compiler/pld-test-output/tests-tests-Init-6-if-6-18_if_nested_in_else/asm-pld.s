.globl main
 main: 
	pushq %rbp
	movq %rsp, %rbp
	movl $8, -8(%rbp)
	movl -8(%rbp), %eax
	movl %eax, -4(%rbp)
	movl $1, -16(%rbp)
	movl -16(%rbp), %eax
	movl %eax, -12(%rbp)
	movl $10, -20(%rbp)
	movl -4(%rbp), %eax
	cmpl -20(%rbp), %eax
	jle .L2
	movl $7, -24(%rbp)
	movl -24(%rbp), %eax
	movl %eax, -12(%rbp)
	jmp .L3
.L2:
	movl $7, -28(%rbp)
	movl -4(%rbp), %eax
	cmpl -28(%rbp), %eax
	jle .L3
	movl $3, -32(%rbp)
	movl -32(%rbp), %eax
	movl %eax, -12(%rbp)
	jmp .L4
.L3:
	movl $4, -36(%rbp)
	movl -36(%rbp), %eax
	movl %eax, -12(%rbp)
.L4:
.L5:
	movl	-12(%rbp), %eax
	popq %rbp
	ret
