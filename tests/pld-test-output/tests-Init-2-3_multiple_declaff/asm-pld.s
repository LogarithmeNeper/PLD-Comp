.globl	main
 main: 
	pushq %rbp
	movq %rsp, %rbp
	movl $5, -4(%rbp)
	movl	$6, %eax
	popq %rbp
	ret
