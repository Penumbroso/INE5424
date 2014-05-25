	.file	"ia32_crtend.s"

	.section	.ctors,"aw",@progbits
	.align 4
	.type	__CTOR_END__, @object
__CTOR_END__:
	.long	0

	.section	.dtors,"aw",@progbits
	.align 4
	.type	__DTOR_END__, @object
__DTOR_END__:
	.long	0

	.text
	.p2align 4,,15
	.globl	__do_global_ctors_aux
	.type	__do_global_ctors_aux, @function
__do_global_ctors_aux:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$4, %esp
	movl	$__CTOR_END__-4, %ebx
	movl	__CTOR_END__-4, %eax
	jmp	.L2
	.p2align 4,,7
.L1:
	subl	$4, %ebx
	call	*%eax
	movl	(%ebx), %eax
.L2:
	cmpl	$-1, %eax
	jne	.L1
	popl	%eax
	popl	%ebx
	popl	%ebp
	ret

	.section	.init
	call __do_global_ctors_aux

	.text
	.section	.note.GNU-stack,"",@progbits
