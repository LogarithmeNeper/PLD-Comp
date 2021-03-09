.globl	main
 main: 
	pushq %rbp
	movq %rsp, %rbp
	movl $4, -4(%rbp)
	movl	$8, %eax
	popq %rbp
	ret
