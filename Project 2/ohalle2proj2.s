	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 11, 0	sdk_version 12, 1
	.globl	_init                           ## -- Begin function init
	.p2align	4, 0x90
_init:                                  ## @init
## %bb.0:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movl	$16, %edi
	callq	_malloc
	movq	%rax, -8(%rbp)
	movl	$2, %edi
	callq	_malloc
	movq	%rax, %rcx
	movq	-8(%rbp), %rax
	movq	%rcx, (%rax)
	movq	-8(%rbp), %rax
	movl	$-1, 8(%rax)
	movq	-8(%rbp), %rax
	movl	$2, 12(%rax)
	movq	-8(%rbp), %rax
	addq	$16, %rsp
	popq	%rbp
	retq
                                        ## -- End function
	.globl	_is_empty                       ## -- Begin function is_empty
	.p2align	4, 0x90
_is_empty:                              ## @is_empty
## %bb.0:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, -16(%rbp)
	movq	-16(%rbp), %rax
	cmpl	$-1, 8(%rax)
	jne	LBB1_2
## %bb.1:
	movl	$1, -4(%rbp)
	jmp	LBB1_3
LBB1_2:
	movl	$0, -4(%rbp)
LBB1_3:
	movl	-4(%rbp), %eax
	popq	%rbp
	retq
                                        ## -- End function
	.globl	_push                           ## -- Begin function push
	.p2align	4, 0x90
_push:                                  ## @push
## %bb.0:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movb	%sil, %al
	movq	%rdi, -8(%rbp)
	movb	%al, -9(%rbp)
	movq	-8(%rbp), %rax
	movl	8(%rax), %eax
	movq	-8(%rbp), %rcx
	movl	12(%rcx), %ecx
	subl	$1, %ecx
	cmpl	%ecx, %eax
	jne	LBB2_2
## %bb.1:
	movq	-8(%rbp), %rdi
	callq	_grow
LBB2_2:
	movq	_DebugMode@GOTPCREL(%rip), %rax
	movq	-8(%rbp), %rcx
	movl	8(%rcx), %edx
	addl	$1, %edx
	movl	%edx, 8(%rcx)
	movb	-9(%rbp), %sil
	movq	-8(%rbp), %rcx
	movq	(%rcx), %rcx
	movq	-8(%rbp), %rdx
	movslq	8(%rdx), %rdx
	movb	%sil, (%rcx,%rdx)
	cmpl	$1, (%rax)
	jne	LBB2_4
## %bb.3:
	movsbl	-9(%rbp), %esi
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
LBB2_4:
	movl	$1, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
                                        ## -- End function
	.p2align	4, 0x90                         ## -- Begin function grow
_grow:                                  ## @grow
## %bb.0:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	_DebugMode@GOTPCREL(%rip), %rax
	movq	%rdi, -8(%rbp)
	movl	$0, -20(%rbp)
	cmpl	$1, (%rax)
	jne	LBB3_2
## %bb.1:
	movq	-8(%rbp), %rax
	movl	12(%rax), %esi
	leaq	L_.str.12(%rip), %rdi
	movb	$0, %al
	callq	_printf
LBB3_2:
	movq	-8(%rbp), %rax
	movl	12(%rax), %ecx
	shll	$1, %ecx
	movq	-8(%rbp), %rax
	movl	%ecx, 12(%rax)
	movq	-8(%rbp), %rax
	movslq	12(%rax), %rdi
	shlq	$0, %rdi
	callq	_malloc
	movq	%rax, -16(%rbp)
	movl	$0, -24(%rbp)
LBB3_3:                                 ## =>This Inner Loop Header: Depth=1
	movl	-24(%rbp), %eax
	movq	-8(%rbp), %rcx
	cmpl	8(%rcx), %eax
	jg	LBB3_6
## %bb.4:                               ##   in Loop: Header=BB3_3 Depth=1
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movslq	-24(%rbp), %rcx
	movb	(%rax,%rcx), %dl
	movq	-16(%rbp), %rax
	movslq	-24(%rbp), %rcx
	movb	%dl, (%rax,%rcx)
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
## %bb.5:                               ##   in Loop: Header=BB3_3 Depth=1
	movl	-24(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -24(%rbp)
	jmp	LBB3_3
LBB3_6:
	movq	-8(%rbp), %rax
	movq	(%rax), %rdi
	callq	_free
	movq	_DebugMode@GOTPCREL(%rip), %rax
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rcx
	movq	%rdx, (%rcx)
	cmpl	$1, (%rax)
	jne	LBB3_8
## %bb.7:
	movq	-8(%rbp), %rax
	movl	12(%rax), %esi
	leaq	L_.str.13(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	-20(%rbp), %esi
	leaq	L_.str.14(%rip), %rdi
	movb	$0, %al
	callq	_printf
LBB3_8:
	addq	$32, %rsp
	popq	%rbp
	retq
                                        ## -- End function
	.globl	_pop                            ## -- Begin function pop
	.p2align	4, 0x90
_pop:                                   ## @pop
## %bb.0:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$16, %rsp
	movq	%rdi, -16(%rbp)
	movq	-16(%rbp), %rax
	cmpl	$-1, 8(%rax)
	jne	LBB4_2
## %bb.1:
	movb	$-1, -1(%rbp)
	jmp	LBB4_5
LBB4_2:
	movq	_DebugMode@GOTPCREL(%rip), %rax
	movq	-16(%rbp), %rcx
	movl	8(%rcx), %edx
	addl	$-1, %edx
	movl	%edx, 8(%rcx)
	cmpl	$1, (%rax)
	jne	LBB4_4
## %bb.3:
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	-16(%rbp), %rcx
	movl	8(%rcx), %ecx
	addl	$1, %ecx
	movslq	%ecx, %rcx
	movsbl	(%rax,%rcx), %esi
	leaq	L_.str.1(%rip), %rdi
	movb	$0, %al
	callq	_printf
LBB4_4:
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	-16(%rbp), %rcx
	movl	8(%rcx), %ecx
	addl	$1, %ecx
	movslq	%ecx, %rcx
	movb	(%rax,%rcx), %al
	movb	%al, -1(%rbp)
LBB4_5:
	movsbl	-1(%rbp), %eax
	addq	$16, %rsp
	popq	%rbp
	retq
                                        ## -- End function
	.globl	_top                            ## -- Begin function top
	.p2align	4, 0x90
_top:                                   ## @top
## %bb.0:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, -16(%rbp)
	movq	-16(%rbp), %rax
	cmpl	$-1, 8(%rax)
	jne	LBB5_2
## %bb.1:
	movb	$-1, -1(%rbp)
	jmp	LBB5_3
LBB5_2:
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	movq	-16(%rbp), %rcx
	movslq	8(%rcx), %rcx
	movb	(%rax,%rcx), %al
	movb	%al, -1(%rbp)
LBB5_3:
	movsbl	-1(%rbp), %eax
	popq	%rbp
	retq
                                        ## -- End function
	.globl	_clearStack                     ## -- Begin function clearStack
	.p2align	4, 0x90
_clearStack:                            ## @clearStack
## %bb.0:
	pushq	%rbp
	movq	%rsp, %rbp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$-1, 8(%rax)
	popq	%rbp
	retq
                                        ## -- End function
	.globl	_isMatching                     ## -- Begin function isMatching
	.p2align	4, 0x90
_isMatching:                            ## @isMatching
## %bb.0:
	pushq	%rbp
	movq	%rsp, %rbp
	movb	%sil, %al
	movb	%dil, %cl
	movb	%cl, -5(%rbp)
	movb	%al, -6(%rbp)
	movsbl	-5(%rbp), %eax
	cmpl	$40, %eax
	jne	LBB7_3
## %bb.1:
	movsbl	-6(%rbp), %eax
	cmpl	$41, %eax
	jne	LBB7_3
## %bb.2:
	movl	$1, -4(%rbp)
	jmp	LBB7_13
LBB7_3:
	movsbl	-5(%rbp), %eax
	cmpl	$123, %eax
	jne	LBB7_6
## %bb.4:
	movsbl	-6(%rbp), %eax
	cmpl	$125, %eax
	jne	LBB7_6
## %bb.5:
	movl	$1, -4(%rbp)
	jmp	LBB7_13
LBB7_6:
	movsbl	-5(%rbp), %eax
	cmpl	$91, %eax
	jne	LBB7_9
## %bb.7:
	movsbl	-6(%rbp), %eax
	cmpl	$93, %eax
	jne	LBB7_9
## %bb.8:
	movl	$1, -4(%rbp)
	jmp	LBB7_13
LBB7_9:
	movsbl	-5(%rbp), %eax
	cmpl	$60, %eax
	jne	LBB7_12
## %bb.10:
	movsbl	-6(%rbp), %eax
	cmpl	$62, %eax
	jne	LBB7_12
## %bb.11:
	movl	$1, -4(%rbp)
	jmp	LBB7_13
LBB7_12:
	movl	$0, -4(%rbp)
LBB7_13:
	movl	-4(%rbp), %eax
	popq	%rbp
	retq
                                        ## -- End function
	.globl	_balancedBrackets               ## -- Begin function balancedBrackets
	.p2align	4, 0x90
_balancedBrackets:                      ## @balancedBrackets
## %bb.0:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$32, %rsp
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movl	$0, -28(%rbp)
LBB8_1:                                 ## =>This Inner Loop Header: Depth=1
	movq	-16(%rbp), %rax
	movslq	-28(%rbp), %rcx
	cmpb	$0, (%rax,%rcx)
	je	LBB8_17
## %bb.2:                               ##   in Loop: Header=BB8_1 Depth=1
	movq	-16(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movsbl	(%rax,%rcx), %eax
	cmpl	$123, %eax
	je	LBB8_6
## %bb.3:                               ##   in Loop: Header=BB8_1 Depth=1
	movq	-16(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movsbl	(%rax,%rcx), %eax
	cmpl	$40, %eax
	je	LBB8_6
## %bb.4:                               ##   in Loop: Header=BB8_1 Depth=1
	movq	-16(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movsbl	(%rax,%rcx), %eax
	cmpl	$91, %eax
	je	LBB8_6
## %bb.5:                               ##   in Loop: Header=BB8_1 Depth=1
	movq	-16(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movsbl	(%rax,%rcx), %eax
	cmpl	$60, %eax
	jne	LBB8_7
LBB8_6:                                 ##   in Loop: Header=BB8_1 Depth=1
	movq	-24(%rbp), %rdi
	movq	-16(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movsbl	(%rax,%rcx), %esi
	callq	_push
LBB8_7:                                 ##   in Loop: Header=BB8_1 Depth=1
	movq	-16(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movsbl	(%rax,%rcx), %eax
	cmpl	$125, %eax
	je	LBB8_11
## %bb.8:                               ##   in Loop: Header=BB8_1 Depth=1
	movq	-16(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movsbl	(%rax,%rcx), %eax
	cmpl	$41, %eax
	je	LBB8_11
## %bb.9:                               ##   in Loop: Header=BB8_1 Depth=1
	movq	-16(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movsbl	(%rax,%rcx), %eax
	cmpl	$93, %eax
	je	LBB8_11
## %bb.10:                              ##   in Loop: Header=BB8_1 Depth=1
	movq	-16(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movsbl	(%rax,%rcx), %eax
	cmpl	$62, %eax
	jne	LBB8_16
LBB8_11:                                ##   in Loop: Header=BB8_1 Depth=1
	movq	-24(%rbp), %rdi
	callq	_is_empty
	cmpl	$1, %eax
	jne	LBB8_13
## %bb.12:
	movl	$2, -4(%rbp)
	jmp	LBB8_20
LBB8_13:                                ##   in Loop: Header=BB8_1 Depth=1
	movq	-24(%rbp), %rdi
	callq	_pop
	movb	%al, -29(%rbp)
	movb	-29(%rbp), %dl
	movq	-16(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movsbl	%dl, %edi
	movsbl	(%rax,%rcx), %esi
	callq	_isMatching
	cmpl	$0, %eax
	jne	LBB8_15
## %bb.14:
	movl	$3, -4(%rbp)
	jmp	LBB8_20
LBB8_15:                                ##   in Loop: Header=BB8_1 Depth=1
	jmp	LBB8_16
LBB8_16:                                ##   in Loop: Header=BB8_1 Depth=1
	movl	-28(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -28(%rbp)
	jmp	LBB8_1
LBB8_17:
	movq	-24(%rbp), %rdi
	callq	_is_empty
	cmpl	$1, %eax
	jne	LBB8_19
## %bb.18:
	movl	$1, -4(%rbp)
	jmp	LBB8_20
LBB8_19:
	movl	$4, -4(%rbp)
LBB8_20:
	movl	-4(%rbp), %eax
	addq	$32, %rsp
	popq	%rbp
	retq
                                        ## -- End function
	.globl	_main                           ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
## %bb.0:
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$368, %rsp                      ## imm = 0x170
	movq	_DebugMode@GOTPCREL(%rip), %rax
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	%rcx, -8(%rbp)
	movl	$0, -324(%rbp)
	movl	%edi, -328(%rbp)
	movq	%rsi, -336(%rbp)
	movl	$0, (%rax)
	movl	$0, -340(%rbp)
LBB9_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	-340(%rbp), %eax
	cmpl	-328(%rbp), %eax
	jge	LBB9_6
## %bb.2:                               ##   in Loop: Header=BB9_1 Depth=1
	movq	-336(%rbp), %rax
	movslq	-340(%rbp), %rcx
	movq	(%rax,%rcx,8), %rdi
	leaq	L_.str.2(%rip), %rsi
	callq	_strcmp
	cmpl	$0, %eax
	jne	LBB9_4
## %bb.3:                               ##   in Loop: Header=BB9_1 Depth=1
	movq	_DebugMode@GOTPCREL(%rip), %rax
	movl	$1, (%rax)
LBB9_4:                                 ##   in Loop: Header=BB9_1 Depth=1
	jmp	LBB9_5
LBB9_5:                                 ##   in Loop: Header=BB9_1 Depth=1
	movl	-340(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -340(%rbp)
	jmp	LBB9_1
LBB9_6:
	jmp	LBB9_7
LBB9_7:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB9_8 Depth 2
	leaq	L_.str.3(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	___stdinp@GOTPCREL(%rip), %rax
	leaq	-320(%rbp), %rdi
	movq	(%rax), %rdx
	movl	$300, %esi                      ## imm = 0x12C
	callq	_fgets
	movl	$0, -344(%rbp)
LBB9_8:                                 ##   Parent Loop BB9_7 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	xorl	%eax, %eax
                                        ## kill: def $al killed $al killed $eax
	movslq	-344(%rbp), %rcx
	movsbl	-320(%rbp,%rcx), %ecx
	cmpl	$10, %ecx
	movb	%al, -357(%rbp)                 ## 1-byte Spill
	je	LBB9_10
## %bb.9:                               ##   in Loop: Header=BB9_8 Depth=2
	movslq	-344(%rbp), %rax
	movsbl	-320(%rbp,%rax), %eax
	cmpl	$0, %eax
	setne	%al
	movb	%al, -357(%rbp)                 ## 1-byte Spill
LBB9_10:                                ##   in Loop: Header=BB9_8 Depth=2
	movb	-357(%rbp), %al                 ## 1-byte Reload
	testb	$1, %al
	jne	LBB9_11
	jmp	LBB9_12
LBB9_11:                                ##   in Loop: Header=BB9_8 Depth=2
	movl	-344(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -344(%rbp)
	jmp	LBB9_8
LBB9_12:                                ##   in Loop: Header=BB9_7 Depth=1
	leaq	-320(%rbp), %rdi
	movslq	-344(%rbp), %rax
	movb	$0, -320(%rbp,%rax)
	leaq	L_.str.4(%rip), %rsi
	callq	_strcmp
	cmpl	$0, %eax
	je	LBB9_14
## %bb.13:                              ##   in Loop: Header=BB9_7 Depth=1
	leaq	-320(%rbp), %rdi
	leaq	L_.str.5(%rip), %rsi
	callq	_strcmp
	cmpl	$0, %eax
	jne	LBB9_15
LBB9_14:
	jmp	LBB9_27
LBB9_15:                                ##   in Loop: Header=BB9_7 Depth=1
	leaq	-320(%rbp), %rsi
	leaq	L_.str.6(%rip), %rdi
	movb	$0, %al
	callq	_printf
	callq	_init
	leaq	-320(%rbp), %rdi
	movq	%rax, -352(%rbp)
	movq	-352(%rbp), %rsi
	callq	_balancedBrackets
	movl	%eax, -356(%rbp)
	cmpl	$1, -356(%rbp)
	jne	LBB9_17
## %bb.16:                              ##   in Loop: Header=BB9_7 Depth=1
	leaq	L_.str.7(%rip), %rdi
	movb	$0, %al
	callq	_printf
	jmp	LBB9_26
LBB9_17:                                ##   in Loop: Header=BB9_7 Depth=1
	cmpl	$2, -356(%rbp)
	jne	LBB9_19
## %bb.18:                              ##   in Loop: Header=BB9_7 Depth=1
	leaq	L_.str.8(%rip), %rdi
	movb	$0, %al
	callq	_printf
	jmp	LBB9_25
LBB9_19:                                ##   in Loop: Header=BB9_7 Depth=1
	cmpl	$3, -356(%rbp)
	jne	LBB9_21
## %bb.20:                              ##   in Loop: Header=BB9_7 Depth=1
	leaq	L_.str.9(%rip), %rdi
	movb	$0, %al
	callq	_printf
	jmp	LBB9_24
LBB9_21:                                ##   in Loop: Header=BB9_7 Depth=1
	cmpl	$4, -356(%rbp)
	jne	LBB9_23
## %bb.22:                              ##   in Loop: Header=BB9_7 Depth=1
	leaq	L_.str.10(%rip), %rdi
	movb	$0, %al
	callq	_printf
LBB9_23:                                ##   in Loop: Header=BB9_7 Depth=1
	jmp	LBB9_24
LBB9_24:                                ##   in Loop: Header=BB9_7 Depth=1
	jmp	LBB9_25
LBB9_25:                                ##   in Loop: Header=BB9_7 Depth=1
	jmp	LBB9_26
LBB9_26:                                ##   in Loop: Header=BB9_7 Depth=1
	movq	-352(%rbp), %rdi
	callq	_clearStack
	jmp	LBB9_7
LBB9_27:
	leaq	L_.str.11(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rcx
	cmpq	%rcx, %rax
	jne	LBB9_29
## %bb.28:
	xorl	%eax, %eax
	addq	$368, %rsp                      ## imm = 0x170
	popq	%rbp
	retq
LBB9_29:
	callq	___stack_chk_fail
	ud2
                                        ## -- End function
	.comm	_DebugMode,4,2                  ## @DebugMode
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"A value has been pushed onto the stack : %c\n"

L_.str.1:                               ## @.str.1
	.asciz	"A value has been popped from the stack: %c\n"

L_.str.2:                               ## @.str.2
	.asciz	"-d"

L_.str.3:                               ## @.str.3
	.asciz	"\nEnter input to check or q to quit\n"

L_.str.4:                               ## @.str.4
	.asciz	"q"

L_.str.5:                               ## @.str.5
	.asciz	"Q"

L_.str.6:                               ## @.str.6
	.asciz	"%s\n"

L_.str.7:                               ## @.str.7
	.asciz	"The input is balanced."

L_.str.8:                               ## @.str.8
	.asciz	"The input is unbalanced because it is missing an opening symbol."

L_.str.9:                               ## @.str.9
	.asciz	"The input is unbalanced because it it is expecting a different closing symbol."

L_.str.10:                              ## @.str.10
	.asciz	"The input unbalanced because it is missing a closing symbol."

L_.str.11:                              ## @.str.11
	.asciz	"\nGoodbye\n"

L_.str.12:                              ## @.str.12
	.asciz	"Old size: %d\n"

L_.str.13:                              ## @.str.13
	.asciz	"New size: %d\n"

L_.str.14:                              ## @.str.14
	.asciz	"Number of values copied from the current to the new dynamic array: %d\n"

.subsections_via_symbols
