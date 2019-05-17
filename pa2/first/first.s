	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$24, %rsp
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	movq	8(%rsi), %rdi
	leaq	L_.str(%rip), %rsi
	callq	_fopen
	movq	%rax, %rbx
	leaq	L_.str.1(%rip), %rsi
	leaq	-42(%rbp), %rdx
	xorl	%eax, %eax
	movq	%rbx, %rdi
	callq	_fscanf
	leaq	L_.str.2(%rip), %rsi
	leaq	-57(%rbp), %rdx
	leaq	-48(%rbp), %rcx
	leaq	-52(%rbp), %r8
	xorl	%eax, %eax
	movq	%rbx, %rdi
	callq	_fscanf
	cmpl	$-1, %eax
	je	LBB0_10
## %bb.1:
	leaq	L_.str.2(%rip), %r15
	leaq	-57(%rbp), %r12
	leaq	-48(%rbp), %r13
	leaq	-52(%rbp), %r14
	.p2align	4, 0x90
LBB0_2:                                 ## =>This Inner Loop Header: Depth=1
	movsbl	-57(%rbp), %eax
	cmpl	$99, %eax
	je	LBB0_6
## %bb.3:                               ##   in Loop: Header=BB0_2 Depth=1
	cmpl	$115, %eax
	je	LBB0_7
## %bb.4:                               ##   in Loop: Header=BB0_2 Depth=1
	cmpl	$103, %eax
	jne	LBB0_9
## %bb.5:                               ##   in Loop: Header=BB0_2 Depth=1
	movzwl	-42(%rbp), %esi
	movzbl	-48(%rbp), %ecx
	shrl	%cl, %esi
	andl	$1, %esi
	jmp	LBB0_8
	.p2align	4, 0x90
LBB0_7:                                 ##   in Loop: Header=BB0_2 Depth=1
	xorl	%eax, %eax
	subl	-52(%rbp), %eax
	movzwl	-42(%rbp), %edx
	xorl	%edx, %eax
	movzbl	-48(%rbp), %ecx
	movl	$1, %esi
	shlq	%cl, %rsi
	andl	%eax, %esi
	xorl	%edx, %esi
	movw	%si, -42(%rbp)
	movzwl	%si, %esi
	jmp	LBB0_8
	.p2align	4, 0x90
LBB0_6:                                 ##   in Loop: Header=BB0_2 Depth=1
	movzbl	-48(%rbp), %ecx
	movl	$1, %eax
	shlq	%cl, %rax
	xorw	-42(%rbp), %ax
	movw	%ax, -42(%rbp)
	movzwl	%ax, %esi
LBB0_8:                                 ##   in Loop: Header=BB0_2 Depth=1
	xorl	%eax, %eax
	leaq	L_.str.3(%rip), %rdi
	callq	_printf
LBB0_9:                                 ##   in Loop: Header=BB0_2 Depth=1
	xorl	%eax, %eax
	movq	%rbx, %rdi
	movq	%r15, %rsi
	movq	%r12, %rdx
	movq	%r13, %rcx
	movq	%r14, %r8
	callq	_fscanf
	cmpl	$-1, %eax
	jne	LBB0_2
LBB0_10:
	movq	%rbx, %rdi
	callq	_fclose
	xorl	%eax, %eax
	addq	$24, %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"r"

L_.str.1:                               ## @.str.1
	.asciz	"%hu\n"

L_.str.2:                               ## @.str.2
	.asciz	"%s\t%d\t%d\n"

L_.str.3:                               ## @.str.3
	.asciz	"%d\n"


.subsections_via_symbols
