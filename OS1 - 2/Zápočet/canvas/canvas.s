	.file	"canvas.c"
	.text
	.globl	rotr
	.type	rotr, @function
rotr:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, %eax
	movl	%esi, -8(%rbp)
	movb	%al, -4(%rbp)
	movl	-8(%rbp), %edx
	movl	%edx, %eax
	imulq	$613566757, %rax, %rax
	shrq	$32, %rax
	movl	%edx, %ecx
	subl	%eax, %ecx
	shrl	%ecx
	addl	%ecx, %eax
	shrl	$2, %eax
	movl	%eax, %ecx
	movl	%ecx, %eax
	sall	$3, %eax
	subl	%ecx, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -8(%rbp)
	jmp	.L2
.L3:
	movzbl	-4(%rbp), %eax
	shrb	%al
	movl	%eax, %edx
	movsbl	-4(%rbp), %eax
	sall	$7, %eax
	orl	%edx, %eax
	movb	%al, -4(%rbp)
.L2:
	movl	-8(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, -8(%rbp)
	testl	%eax, %eax
	jne	.L3
	movsbl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	rotr, .-rotr
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$10, %esi
	movl	$20, %edi
	call	canvas_create
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$13, %ecx
	movl	$2, %edx
	movl	$3, %esi
	movq	%rax, %rdi
	call	canvas_hline
	movq	-8(%rbp), %rax
	movl	$-11, %ecx
	movl	$5, %edx
	movl	$14, %esi
	movq	%rax, %rdi
	call	canvas_hline
	movq	-8(%rbp), %rax
	movl	$6, %ecx
	movl	$1, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	canvas_vline
	movq	-8(%rbp), %rax
	movl	$-6, %ecx
	movl	$6, %edx
	movl	$14, %esi
	movq	%rax, %rdi
	call	canvas_vline
	movq	-8(%rbp), %rax
	movl	$20, %ecx
	movl	$5, %edx
	movl	$9, %esi
	movq	%rax, %rdi
	call	canvas_vline
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	canvas_print
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	canvas_free
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.globl	canvas_create
	.type	canvas_create, @function
canvas_create:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	-20(%rbp), %eax
	imull	-24(%rbp), %eax
	leal	7(%rax), %edx
	testl	%eax, %eax
	cmovs	%edx, %eax
	sarl	$3, %eax
	movl	%eax, -4(%rbp)
	sall	-4(%rbp)
	movl	$24, %edi
	call	malloc
	movq	%rax, -16(%rbp)
	movl	-4(%rbp), %eax
	cltq
	movq	%rax, %rdi
	call	malloc
	movq	%rax, %rdx
	movq	-16(%rbp), %rax
	movq	%rdx, (%rax)
	movq	-16(%rbp), %rax
	movl	-24(%rbp), %edx
	movl	%edx, 12(%rax)
	movq	-16(%rbp), %rax
	movl	-20(%rbp), %edx
	movl	%edx, 8(%rax)
	movq	-16(%rbp), %rax
	movl	-4(%rbp), %edx
	movl	%edx, 16(%rax)
	movq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	canvas_init
	movq	-16(%rbp), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	canvas_create, .-canvas_create
	.globl	canvas_init
	.type	canvas_init, @function
canvas_init:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L10
.L11:
	movq	-24(%rbp), %rax
	movq	(%rax), %rdx
	movl	-4(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movb	$0, (%rax)
	addl	$1, -4(%rbp)
.L10:
	movq	-24(%rbp), %rax
	movl	16(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L11
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	canvas_init, .-canvas_init
	.globl	canvas_free
	.type	canvas_free, @function
canvas_free:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	free
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	free
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	canvas_free, .-canvas_free
	.globl	canvas_print
	.type	canvas_print, @function
canvas_print:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movl	$0, -4(%rbp)
	movb	$-64, -17(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L14
.L22:
	movq	-40(%rbp), %rax
	movq	(%rax), %rdx
	movl	-8(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movb	%al, -9(%rbp)
	movl	$0, -16(%rbp)
	jmp	.L15
.L21:
	movzbl	-9(%rbp), %eax
	andb	-17(%rbp), %al
	movsbl	%al, %eax
	movl	%eax, -24(%rbp)
	movsbl	-9(%rbp), %eax
	sall	$2, %eax
	movb	%al, -9(%rbp)
	cmpl	$0, -24(%rbp)
	jne	.L16
	movl	$46, %edi
	call	putchar
	jmp	.L17
.L16:
	cmpl	$-64, -24(%rbp)
	jne	.L18
	movl	$43, %edi
	call	putchar
	jmp	.L17
.L18:
	cmpl	$-128, -24(%rbp)
	jne	.L19
	movl	$45, %edi
	call	putchar
	jmp	.L17
.L19:
	movl	$124, %edi
	call	putchar
.L17:
	addl	$1, -4(%rbp)
	movq	-40(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jne	.L20
	movl	$10, %edi
	call	putchar
	movl	$0, -4(%rbp)
.L20:
	addl	$2, -16(%rbp)
.L15:
	cmpl	$7, -16(%rbp)
	jle	.L21
	addl	$1, -8(%rbp)
.L14:
	movq	-40(%rbp), %rax
	movl	16(%rax), %eax
	cmpl	%eax, -8(%rbp)
	jl	.L22
	nop
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE11:
	.size	canvas_print, .-canvas_print
	.globl	canvas_hline
	.type	canvas_hline, @function
canvas_hline:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$136, %rsp
	movq	%rdi, -120(%rbp)
	movl	%esi, -124(%rbp)
	movl	%edx, -128(%rbp)
	movl	%ecx, -132(%rbp)
	movq	-120(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	%eax, -124(%rbp)
	ja	.L49
	movq	-120(%rbp), %rax
	movl	12(%rax), %eax
	cmpl	%eax, -128(%rbp)
	ja	.L49
	movq	-120(%rbp), %rax
	movl	8(%rax), %eax
	addl	%eax, %eax
	movl	%eax, -48(%rbp)
	movl	$1, -4(%rbp)
	movl	$1, -8(%rbp)
	cmpl	$0, -132(%rbp)
	jle	.L27
	movl	-48(%rbp), %eax
	imull	-128(%rbp), %eax
	movl	%eax, -80(%rbp)
	movl	-124(%rbp), %eax
	leal	(%rax,%rax), %edx
	movl	-80(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -80(%rbp)
	movl	-132(%rbp), %eax
	leal	(%rax,%rax), %edx
	movl	-80(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -84(%rbp)
	movl	$0, -12(%rbp)
	movl	$0, -16(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L28
.L38:
	movl	-20(%rbp), %eax
	sall	$3, %eax
	movl	%eax, -88(%rbp)
	movl	-20(%rbp), %eax
	sall	$3, %eax
	addl	$7, %eax
	movl	%eax, -92(%rbp)
	movl	-20(%rbp), %eax
	addl	$1, %eax
	imull	-48(%rbp), %eax
	cmpl	%eax, -80(%rbp)
	jge	.L29
	cmpl	$0, -16(%rbp)
	jne	.L29
	movl	-20(%rbp), %eax
	imull	-48(%rbp), %eax
	movl	-80(%rbp), %edx
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -16(%rbp)
.L29:
	movl	-88(%rbp), %eax
	cmpl	-80(%rbp), %eax
	jg	.L30
	movl	-80(%rbp), %eax
	cmpl	-92(%rbp), %eax
	jg	.L30
	cmpl	$0, -4(%rbp)
	je	.L30
	movl	-80(%rbp), %eax
	subl	-88(%rbp), %eax
	movl	%eax, -96(%rbp)
	movl	-96(%rbp), %eax
	movl	%eax, -24(%rbp)
	jmp	.L31
.L32:
	movq	-120(%rbp), %rax
	movq	(%rax), %rdx
	movl	-20(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	leal	0(,%rax,4), %ecx
	movq	-120(%rbp), %rax
	movq	(%rax), %rdx
	movl	-20(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movl	%ecx, %edx
	movb	%dl, (%rax)
	movq	-120(%rbp), %rax
	movq	(%rax), %rdx
	movl	-20(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %ecx
	movq	-120(%rbp), %rax
	movq	(%rax), %rdx
	movl	-20(%rbp), %eax
	cltq
	addq	%rdx, %rax
	orl	$2, %ecx
	movl	%ecx, %edx
	movb	%dl, (%rax)
	addl	$2, -12(%rbp)
	addl	$2, -24(%rbp)
.L31:
	cmpl	$7, -24(%rbp)
	jle	.L32
	movl	$0, -4(%rbp)
.L30:
	movl	-20(%rbp), %eax
	sall	$3, %eax
	cmpl	%eax, -80(%rbp)
	jg	.L33
	movl	-20(%rbp), %eax
	sall	$3, %eax
	addl	$7, %eax
	cmpl	%eax, -84(%rbp)
	jle	.L33
	movq	-120(%rbp), %rax
	movq	(%rax), %rdx
	movl	-20(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %ecx
	movq	-120(%rbp), %rax
	movq	(%rax), %rdx
	movl	-20(%rbp), %eax
	cltq
	addq	%rdx, %rax
	orl	$-86, %ecx
	movl	%ecx, %edx
	movb	%dl, (%rax)
	addl	$8, -12(%rbp)
.L33:
	movl	-88(%rbp), %eax
	cmpl	-84(%rbp), %eax
	jg	.L34
	movl	-84(%rbp), %eax
	cmpl	-92(%rbp), %eax
	jg	.L34
	cmpl	$0, -8(%rbp)
	je	.L34
	movl	-84(%rbp), %eax
	subl	-88(%rbp), %eax
	movl	%eax, -100(%rbp)
	movl	$8, %eax
	subl	-100(%rbp), %eax
	movl	%eax, -28(%rbp)
	jmp	.L35
.L36:
	movq	-120(%rbp), %rax
	movq	(%rax), %rdx
	movl	-20(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %ecx
	movq	-120(%rbp), %rax
	movq	(%rax), %rdx
	movl	-20(%rbp), %eax
	cltq
	addq	%rdx, %rax
	orl	$2, %ecx
	movl	%ecx, %edx
	movb	%dl, (%rax)
	movq	-120(%rbp), %rax
	movq	(%rax), %rdx
	movl	-20(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	$2, %esi
	movl	%eax, %edi
	call	rotr
	movl	%eax, %ecx
	movq	-120(%rbp), %rax
	movq	(%rax), %rdx
	movl	-20(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movl	%ecx, %edx
	movb	%dl, (%rax)
	addl	$2, -12(%rbp)
	addl	$2, -28(%rbp)
.L35:
	cmpl	$7, -28(%rbp)
	jle	.L36
	movl	$0, -8(%rbp)
.L34:
	movl	-48(%rbp), %eax
	subl	-16(%rbp), %eax
	cmpl	%eax, -12(%rbp)
	jge	.L50
	addl	$1, -20(%rbp)
.L28:
	movq	-120(%rbp), %rax
	movl	16(%rax), %eax
	cmpl	%eax, -20(%rbp)
	jl	.L38
	jmp	.L23
.L27:
	cmpl	$0, -132(%rbp)
	jns	.L23
	movl	-48(%rbp), %eax
	imull	-128(%rbp), %eax
	movl	%eax, -32(%rbp)
	movl	-124(%rbp), %eax
	addl	$1, %eax
	leal	(%rax,%rax), %edx
	movl	-32(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -32(%rbp)
	movl	-32(%rbp), %eax
	movl	%eax, -52(%rbp)
	movl	-52(%rbp), %eax
	cltd
	idivl	-48(%rbp)
	movl	%eax, -56(%rbp)
	movl	-56(%rbp), %eax
	imull	-48(%rbp), %eax
	movl	%eax, -60(%rbp)
	movl	-132(%rbp), %eax
	addl	$1, %eax
	addl	%eax, %eax
	addl	%eax, -32(%rbp)
	movl	-32(%rbp), %eax
	cmpl	-60(%rbp), %eax
	jge	.L39
	movl	-60(%rbp), %eax
	movl	%eax, -32(%rbp)
.L39:
	movl	$0, -36(%rbp)
	jmp	.L40
.L48:
	movl	-36(%rbp), %eax
	sall	$3, %eax
	movl	%eax, -64(%rbp)
	movl	-36(%rbp), %eax
	sall	$3, %eax
	addl	$7, %eax
	movl	%eax, -68(%rbp)
	movl	-64(%rbp), %eax
	cmpl	-32(%rbp), %eax
	jg	.L41
	movl	-32(%rbp), %eax
	cmpl	-68(%rbp), %eax
	jg	.L41
	cmpl	$0, -4(%rbp)
	je	.L41
	movl	-32(%rbp), %eax
	subl	-64(%rbp), %eax
	movl	%eax, -72(%rbp)
	movl	-72(%rbp), %edx
	movq	-120(%rbp), %rax
	movq	(%rax), %rcx
	movl	-36(%rbp), %eax
	cltq
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	rotr
	movl	%eax, %ecx
	movq	-120(%rbp), %rax
	movq	(%rax), %rdx
	movl	-36(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movl	%ecx, %edx
	movb	%dl, (%rax)
	movl	-72(%rbp), %eax
	movl	%eax, -40(%rbp)
	jmp	.L42
.L43:
	movq	-120(%rbp), %rax
	movq	(%rax), %rdx
	movl	-36(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %ecx
	movq	-120(%rbp), %rax
	movq	(%rax), %rdx
	movl	-36(%rbp), %eax
	cltq
	addq	%rdx, %rax
	orl	$2, %ecx
	movl	%ecx, %edx
	movb	%dl, (%rax)
	movq	-120(%rbp), %rax
	movq	(%rax), %rdx
	movl	-36(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	$2, %esi
	movl	%eax, %edi
	call	rotr
	movl	%eax, %ecx
	movq	-120(%rbp), %rax
	movq	(%rax), %rdx
	movl	-36(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movl	%ecx, %edx
	movb	%dl, (%rax)
	addl	$2, -40(%rbp)
.L42:
	cmpl	$8, -40(%rbp)
	jle	.L43
	movl	$0, -4(%rbp)
.L41:
	movl	-36(%rbp), %eax
	sall	$3, %eax
	cmpl	%eax, -32(%rbp)
	jg	.L44
	movl	-36(%rbp), %eax
	sall	$3, %eax
	addl	$7, %eax
	cmpl	%eax, -52(%rbp)
	jle	.L44
	movq	-120(%rbp), %rax
	movq	(%rax), %rdx
	movl	-36(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %ecx
	movq	-120(%rbp), %rax
	movq	(%rax), %rdx
	movl	-36(%rbp), %eax
	cltq
	addq	%rdx, %rax
	orl	$-86, %ecx
	movl	%ecx, %edx
	movb	%dl, (%rax)
.L44:
	movl	-64(%rbp), %eax
	cmpl	-52(%rbp), %eax
	jg	.L45
	movl	-52(%rbp), %eax
	cmpl	-68(%rbp), %eax
	jg	.L45
	cmpl	$0, -8(%rbp)
	je	.L45
	movl	-52(%rbp), %eax
	subl	-64(%rbp), %eax
	movl	%eax, -76(%rbp)
	movl	$8, %eax
	subl	-76(%rbp), %eax
	movl	%eax, -44(%rbp)
	jmp	.L46
.L47:
	movq	-120(%rbp), %rax
	movq	(%rax), %rdx
	movl	-36(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %ecx
	movq	-120(%rbp), %rax
	movq	(%rax), %rdx
	movl	-36(%rbp), %eax
	cltq
	addq	%rdx, %rax
	orl	$2, %ecx
	movl	%ecx, %edx
	movb	%dl, (%rax)
	movq	-120(%rbp), %rax
	movq	(%rax), %rdx
	movl	-36(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	$2, %esi
	movl	%eax, %edi
	call	rotr
	movl	%eax, %ecx
	movq	-120(%rbp), %rax
	movq	(%rax), %rdx
	movl	-36(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movl	%ecx, %edx
	movb	%dl, (%rax)
	addl	$2, -44(%rbp)
.L46:
	cmpl	$7, -44(%rbp)
	jle	.L47
	movl	$0, -8(%rbp)
.L45:
	addl	$1, -36(%rbp)
.L40:
	movq	-120(%rbp), %rax
	movl	16(%rax), %eax
	cmpl	%eax, -36(%rbp)
	jl	.L48
	jmp	.L23
.L49:
	nop
	jmp	.L23
.L50:
	nop
.L23:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE12:
	.size	canvas_hline, .-canvas_hline
	.globl	canvas_vline
	.type	canvas_vline, @function
canvas_vline:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$104, %rsp
	movq	%rdi, -88(%rbp)
	movl	%esi, -92(%rbp)
	movl	%edx, -96(%rbp)
	movl	%ecx, -100(%rbp)
	movq	-88(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	%eax, -92(%rbp)
	ja	.L64
	movq	-88(%rbp), %rax
	movl	12(%rax), %eax
	cmpl	%eax, -96(%rbp)
	ja	.L64
	movq	-88(%rbp), %rax
	movl	8(%rax), %eax
	addl	%eax, %eax
	movl	%eax, -36(%rbp)
	cmpl	$0, -100(%rbp)
	jle	.L55
	movl	-36(%rbp), %eax
	imull	-96(%rbp), %eax
	movl	%eax, -60(%rbp)
	movl	-92(%rbp), %eax
	addl	$1, %eax
	leal	(%rax,%rax), %edx
	movl	-60(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -60(%rbp)
	movl	-100(%rbp), %eax
	imull	-36(%rbp), %eax
	movl	%eax, %edx
	movl	-60(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -64(%rbp)
	movl	-60(%rbp), %eax
	movl	%eax, -4(%rbp)
	movl	$1, -8(%rbp)
	movl	$1, -68(%rbp)
	movl	$0, -12(%rbp)
	movl	$0, -16(%rbp)
	jmp	.L56
.L59:
	movl	-16(%rbp), %eax
	sall	$3, %eax
	movl	%eax, -72(%rbp)
	movl	-16(%rbp), %eax
	sall	$3, %eax
	addl	$7, %eax
	movl	%eax, -76(%rbp)
	movl	-4(%rbp), %eax
	cmpl	-76(%rbp), %eax
	jg	.L57
	movl	-76(%rbp), %eax
	cmpl	-64(%rbp), %eax
	jg	.L57
	cmpl	$0, -8(%rbp)
	je	.L58
	movl	-72(%rbp), %eax
	subl	-60(%rbp), %eax
	movl	%eax, -12(%rbp)
	movl	$0, -8(%rbp)
.L58:
	movl	-12(%rbp), %edx
	movq	-88(%rbp), %rax
	movq	(%rax), %rcx
	movl	-16(%rbp), %eax
	cltq
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	rotr
	movl	%eax, %ecx
	movq	-88(%rbp), %rax
	movq	(%rax), %rdx
	movl	-16(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movl	%ecx, %edx
	movb	%dl, (%rax)
	movq	-88(%rbp), %rax
	movq	(%rax), %rdx
	movl	-16(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %ecx
	movq	-88(%rbp), %rax
	movq	(%rax), %rdx
	movl	-16(%rbp), %eax
	cltq
	addq	%rdx, %rax
	orl	$1, %ecx
	movl	%ecx, %edx
	movb	%dl, (%rax)
	movl	$7, %eax
	subl	-12(%rbp), %eax
	movl	%eax, %ecx
	movq	-88(%rbp), %rax
	movq	(%rax), %rdx
	movl	-16(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	rotr
	movl	%eax, %ecx
	movq	-88(%rbp), %rax
	movq	(%rax), %rdx
	movl	-16(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movl	%ecx, %edx
	movb	%dl, (%rax)
	movl	-36(%rbp), %eax
	addl	%eax, -4(%rbp)
	movq	-88(%rbp), %rax
	movl	8(%rax), %edx
	movq	-88(%rbp), %rax
	movl	12(%rax), %eax
	imull	%edx, %eax
	addl	%eax, %eax
	cmpl	%eax, -4(%rbp)
	jg	.L65
.L57:
	addl	$1, -16(%rbp)
.L56:
	movq	-88(%rbp), %rax
	movl	16(%rax), %eax
	cmpl	%eax, -16(%rbp)
	jl	.L59
	jmp	.L51
.L55:
	cmpl	$0, -100(%rbp)
	jns	.L51
	movl	-36(%rbp), %eax
	imull	-96(%rbp), %eax
	movl	%eax, -40(%rbp)
	movl	-92(%rbp), %eax
	addl	$1, %eax
	leal	(%rax,%rax), %edx
	movl	-40(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -40(%rbp)
	movl	-100(%rbp), %eax
	addl	$1, %eax
	imull	-36(%rbp), %eax
	movl	%eax, %edx
	movl	-40(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -44(%rbp)
	movl	-44(%rbp), %eax
	movl	%eax, -20(%rbp)
	movl	$1, -24(%rbp)
	movl	$1, -48(%rbp)
	movl	$0, -28(%rbp)
	movl	$0, -32(%rbp)
	jmp	.L60
.L63:
	movl	-32(%rbp), %eax
	sall	$3, %eax
	movl	%eax, -52(%rbp)
	movl	-32(%rbp), %eax
	sall	$3, %eax
	addl	$7, %eax
	movl	%eax, -56(%rbp)
	movl	-20(%rbp), %eax
	cmpl	-56(%rbp), %eax
	jg	.L61
	movl	-20(%rbp), %eax
	cmpl	-40(%rbp), %eax
	jg	.L61
	cmpl	$0, -24(%rbp)
	je	.L62
	movl	-44(%rbp), %eax
	subl	-52(%rbp), %eax
	movl	%eax, -28(%rbp)
	movl	$0, -24(%rbp)
.L62:
	movl	$8, %eax
	subl	-28(%rbp), %eax
	movl	%eax, %ecx
	movq	-88(%rbp), %rax
	movq	(%rax), %rdx
	movl	-32(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	rotr
	movl	%eax, %ecx
	movq	-88(%rbp), %rax
	movq	(%rax), %rdx
	movl	-32(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movl	%ecx, %edx
	movb	%dl, (%rax)
	movq	-88(%rbp), %rax
	movq	(%rax), %rdx
	movl	-32(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %ecx
	movq	-88(%rbp), %rax
	movq	(%rax), %rdx
	movl	-32(%rbp), %eax
	cltq
	addq	%rdx, %rax
	orl	$1, %ecx
	movl	%ecx, %edx
	movb	%dl, (%rax)
	movl	-28(%rbp), %edx
	movq	-88(%rbp), %rax
	movq	(%rax), %rcx
	movl	-32(%rbp), %eax
	cltq
	addq	%rcx, %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%edx, %esi
	movl	%eax, %edi
	call	rotr
	movl	%eax, %ecx
	movq	-88(%rbp), %rax
	movq	(%rax), %rdx
	movl	-32(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movl	%ecx, %edx
	movb	%dl, (%rax)
	movl	-36(%rbp), %eax
	addl	%eax, -20(%rbp)
	cmpl	$0, -20(%rbp)
	js	.L66
.L61:
	addl	$1, -32(%rbp)
.L60:
	movq	-88(%rbp), %rax
	movl	16(%rax), %eax
	cmpl	%eax, -32(%rbp)
	jl	.L63
	jmp	.L51
.L64:
	nop
	jmp	.L51
.L65:
	nop
	jmp	.L51
.L66:
	nop
.L51:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE13:
	.size	canvas_vline, .-canvas_vline
	.ident	"GCC: (GNU) 9.3.1 20200408 (Red Hat 9.3.1-2)"
	.section	.note.GNU-stack,"",@progbits
