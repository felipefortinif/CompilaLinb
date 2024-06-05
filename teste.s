.text
.globl main
main:
	pushq	%rbp
	movq	%rsp,	%rbp
	

	movl	$0,	%eax
	cmpl	$0,	%eax
	jne	0
	
	leave
	ret
	
	
