TITLE	Prueba_Codigo01.c
.686
.XMM
.model 	flat
_DATA	SEGMENT
COMM	?r@@:DWORD
COMM	?k@@:DWORD
COMM	?h@@:DWORD:02H
COMM	?ptr@@:DWORD
_DATA	ENDS
_CONST	SEGMENT
__real@9999999a	DD	09999999ar
__real@00000000	DD	000000000r
__real@00000000	DD	000000000r
??@24@@	DB	'C Programming // %d', 0aH, 00H
__real@cccccccd	DD	0cccccccdr
__real@00000000	DD	000000000r
__real@cccccccd	DD	0cccccccdr
__real@33333333	DD	033333333r
__real@00000000	DD	000000000r
??@44@@	DB	'%d', 0aH, 00H
??@35@@	DB	'%d', 0aH, 00H
_CONST	ENDS
_TEXT	SEGMENT
_a$ = 8
_b$ = 12
_@1$ = -4
_myfunc	PROC
	push	ebp
	mov		ebp, esp
	sub		esp, 68
	push	ebx	
	push	esi	
	push	edi	
	mov		eax, DWORD PTR _b$[ebp]
	mul		DWORD PTR _b$[ebp]
	mov		DWORD PTR _b$[ebp], eax
	mov		eax, DWORD PTR _@1$[ebp]
	fld		eax
	jmp		SHORT $exit@myfunc
$exit@myfunc:
	pop		edi
	pop		esi
	pop		ebx
	mov		esp, ebp
	pop		ebp
	ret		0
_myfunc	ENDP
_TEXT	ENDS
_TEXT	SEGMENT
_argc$ = 8
_argv$ = 12
_x$ = -8
_@5$ = -16
_@6$ = -24
_y$ = -28
_@9$ = -32
_z$ = -36
_c$ = -37
_cc$ = -38
_i$ = -42
_@15$ = -46
_@17$ = -50
_@18$ = -58
_@19$ = -66
_@20$ = -70
_@22$ = -74
_@26$ = -78
_@30$ = -82
_@31$ = -86
_@34$ = -90
_@38$ = -98
_@43$ = -102
_@48$ = -106
_@49$ = -110
_@51$ = -114
_@52$ = -118
_@55$ = -122
_@56$ = -126
_@58$ = -134
_@60$ = -138
_@62$ = -142
_@45$ = -146
_@36$ = -150
_main	PROC
	push	ebp
	mov		ebp, esp
	sub		esp, 212
	push	ebx	
	push	esi	
	push	edi	
	movss	xmm0, DWORD PTR __real@9999999a
	movss	DWORD PTR _x$[ebp], xmm0
	movss	xmm0, DWORD PTR __real@00000003
	movss	DWORD PTR _@6$[ebp], xmm0
	movss	xmm0, DWORD PTR __real@00000000
	divss	xmm0, DWORD PTR _@6$[ebp]
	movss	DWORD PTR _@6$[ebp], xmm0
	movss	xmm0, DWORD PTR _@5$[ebp]
	movss	DWORD PTR _y$[ebp], xmm0
	mov		eax, 6
	add		eax, 5
	mov		DWORD PTR _@8$[ebp], eax
	mov		eax, DWORD PTR _@9$[ebp]
	mov		DWORD PTR _z$[ebp], eax
	mov		DWORD PTR _c$[ebp], 58066
	mov		DWORD PTR _cc$[ebp], 226
	mov		DWORD PTR _z$[ebp], 4
	mov		DWORD PTR _@14$[ebp], 12
	xor		edx, edx
	mov		eax, DWORD PTR _@16$[ebp]
	div		2
	mov		DWORD PTR _@16$[ebp], eax
	cvtsi2ss	xmm0, DWORD PTR _@17$[ebp]
	movss		DWORD PTR _@19$[ebp], xmm0
	movss	xmm0, DWORD PTR __real@00000000
	subss	xmm0, DWORD PTR _@19$[ebp]
	movss	DWORD PTR _@19$[ebp], xmm0
	cvttsd2si	eax, QWORD PTR _@18$[ebp]
	mov		DWORD PTR _@20$[ebp], eax
	mov		eax, DWORD PTR _@20$[ebp]
	mov		DWORD PTR ?r@@, eax
	movss	xmm0, DWORD PTR __real@00000000
	movss	DWORD PTR _@22$[ebp], xmm0
	movss	xmm0, DWORD PTR _@22$[ebp]
	mulss	xmm0, DWORD PTR _@22$[ebp]
	movss	DWORD PTR _@22$[ebp], xmm0
	mov		eax, 0
	cmp		eax, 3
	jg		SHORT $LN24@main
	jmp		SHORT $LN28@main
$LN24@main:
	push	5
	push	OFFSET _??@24@@
	call	_printf
	add		esp, 8
	mov		_$[ebp], eax
	jmp		SHORT $LN29@main
$LN28@main:
	mov		eax, DWORD PTR _z$[ebp]
	mov		DWORD PTR ?r@@, eax
$LN29@main:
	mov		eax, DWORD PTR _@27$[ebp]
	add		eax, 170
	mov		DWORD PTR _@27$[ebp], eax
	mov		DWORD PTR _@30$[ebp],-107374184
	mov		eax, 5
	sub		eax, DWORD PTR _@30$[ebp]
	mov		DWORD PTR _@30$[ebp], eax
	mov		eax, DWORD PTR _@31$[ebp]
	mov		DWORD PTR _z$[ebp], eax
	mov		DWORD PTR _i$[ebp], 0
$LN34@main:
	cmp		DWORD PTR _@33$[ebp], 5
	jl		SHORT $LN39@main
	jmp		SHORT $LN43@main
$LN36@main:
	mov		eax, DWORD PTR _i$[ebp]
	mov		DWORD PTR _@34$[ebp], eax
	mov		eax, DWORD PTR _i$[ebp]
	add		eax, 1
	mov		DWORD PTR _i$[ebp], eax
	jmp		SHORT $LN34@main
$LN39@main:
	push	DWORD PTR _i$[ebp]
	push	OFFSET _??@35@@
	call	_printf
	add		esp, 8
	mov		_$[ebp], eax
	jmp		SHORT $LN36@main
$LN43@main:
	movss	xmm0, DWORD PTR _y$[ebp]
	movss	DWORD PTR _@38$[ebp], xmm0
	movss	xmm0, DWORD PTR __real@00000000
	comiss	xmm0, DWORD PTR _@37$[ebp]
	jng		SHORT $LN46@main
	jmp		SHORT $LN48@main
$LN46@main:
	mov		DWORD PTR _z$[ebp], 1
	jmp		SHORT $LN49@main
$LN48@main:
	mov		DWORD PTR _z$[ebp], 0
$LN49@main:
	mov		DWORD PTR _i$[ebp], 0
$LN50@main:
	cmp		DWORD PTR _@42$[ebp], 5
	jl		SHORT $LN55@main
	jmp		SHORT $LN59@main
$LN52@main:
	mov		eax, DWORD PTR _i$[ebp]
	mov		DWORD PTR _@43$[ebp], eax
	mov		eax, DWORD PTR _i$[ebp]
	add		eax, 1
	mov		DWORD PTR _i$[ebp], eax
	jmp		SHORT $LN50@main
$LN55@main:
	push	DWORD PTR _i$[ebp]
	push	OFFSET _??@44@@
	call	_printf
	add		esp, 8
	mov		_$[ebp], eax
	jmp		SHORT $LN52@main
$LN59@main:
	mov		DWORD PTR _@47$[ebp], 4
	mov		eax, DWORD PTR _@48$[ebp]
	mov		ebx, DWORD PTR _?h@@$[ebp+eax]
	mov		DWORD PTR _@49$[ebp], ebx
	push	5
	push	DWORD PTR _@49$[ebp]
	call	_myfunc
	add		esp, 8
	fstp	_$[ebp]
	cvttsd2si	eax, QWORD PTR _@51$[ebp]
	mov		DWORD PTR _@52$[ebp], eax
	mov		eax, DWORD PTR _@52$[ebp]
	mov		DWORD PTR _z$[ebp], eax
	push	DWORD PTR __real@33333333
	push	DWORD PTR __real@cccccccd
	call	_myfunc
	add		esp, 8
	fstp	_$[ebp]
	cvttsd2si	eax, QWORD PTR _@55$[ebp]
	mov		DWORD PTR _@56$[ebp], eax
	mov		eax, DWORD PTR _@56$[ebp]
	mov		DWORD PTR _z$[ebp], eax
	movss	xmm0, DWORD PTR _y$[ebp]
	movss	DWORD PTR _@58$[ebp], xmm0
	movss	xmm0, DWORD PTR __real@00000000
	comiss	xmm0, DWORD PTR _@57$[ebp]
	jng		SHORT $LN74@main
	jmp		SHORT $LN76@main
$LN74@main:
	mov		DWORD PTR _@60$[ebp], 1
	jmp		SHORT $LN77@main
$LN76@main:
	mov		DWORD PTR _@60$[ebp], 0
$LN77@main:
	mov		eax, DWORD PTR _@60$[ebp]
	mov		DWORD PTR _z$[ebp], eax
	mov		eax, DWORD PTR _z$[ebp]
	mov		DWORD PTR _@62$[ebp], eax
	mov		eax, DWORD PTR _z$[ebp]
	sub		eax, 1
	mov		DWORD PTR _z$[ebp], eax
	mov		eax, DWORD PTR _z$[ebp]
	jmp		SHORT $exit@main
$exit@main:
	pop		edi
	pop		esi
	pop		ebx
	mov		esp, ebp
	pop		ebp
	ret		0
_main	ENDP
_TEXT	ENDS
END

