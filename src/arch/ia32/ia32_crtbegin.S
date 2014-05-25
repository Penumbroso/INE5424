	.file	"ia32_crtbegin.s"
	
	.section .ctors,"aw",@progbits
	.align 4
	.type	__CTOR_LIST__, @object
__CTOR_LIST__:
	.long	-1
	
	.section .dtors,"aw",@progbits
	.align 4
	.type	__DTOR_LIST__, @object
__DTOR_LIST__:
	.long	-1
	
	.data
	.align	4
	.type	p.0, @object
p.0:
	.long	__DTOR_LIST__+4
	.local	finished
	.comm	finished,1,1

	.text
	.p2align 4,,15
	.type	__do_global_dtors_aux, @function
__do_global_dtors_aux:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	cmpb	$0, finished
	je	.L2
	jmp	.L3
	.p2align 4,,7
.L1:
	addl	$4, %eax
	movl	%eax, p.0
	call	*%edx
.L2:
	movl	p.0, %eax
	movl	(%eax), %edx
	testl	%edx, %edx
	jne	.L1
	movb	$1, finished
.L3:
	leave
	ret

	.section	.fini
	call __do_global_dtors_aux

// frame_dummy cannot be removed even if EPOS is fully compiled with -no-exceptions
// because glibc is inherently compiled to throw exceptions such as division by zero
	.text
	.p2align 4,,15
	.type	frame_dummy, @function
frame_dummy:
	pushl	%ebp
	movl	%esp, %ebp
	leave
	ret

	.section	.init
	call frame_dummy

	.text
	.section	.note.GNU-stack,"",@progbits
