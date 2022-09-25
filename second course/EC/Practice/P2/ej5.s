.section .data

#ifndef TEST
#define TEST 20
#endif

.macro linea
	#if TEST==1
		.int 1, 2, 1, 2

	#elif TEST==2
		.int -1, -2, -1, -2

	#elif TEST==3
		.int 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF

	#elif TEST==4
		.int 0x80000000, 0x80000000, 0x80000000, 0x80000000

	#elif TEST==5
		.int 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF

	#elif TEST==6
		.int 2000000000, 2000000000, 2000000000, 2000000000

	#elif TEST==7
		.int 3000000000, 3000000000, 3000000000, 3000000000

	#elif TEST==8
		.int -2000000000, -2000000000, -2000000000, -2000000000

	#elif TEST==9
		.int -3000000000, -3000000000, -3000000000, -3000000000

	#elif TEST>=10 && TEST<=14
		.int 1, 1, 1, 1

	#elif TEST>=15 && TEST<=19
		.int -1, -1, -1, -1

	#else
		.error "Definir TEST entre 1..19"

#endif
.endm

.macro linea0

#if TEST>=1 && TEST<=9
		    linea

	#elif TEST==10
		.int 0, 2, 1, 1

	#elif TEST==11
		.int 1, 2, 1, 1

	#elif TEST==12
		.int 8, 2, 1, 1

	#elif TEST==13
		.int 15, 2, 1, 1

	#elif TEST==14
		.int 16, 2, 1, 1

	#elif TEST==15
		.int 0, -2, -1, -1

	#elif TEST==16
		.int -1, -2, -1, -1

	#elif TEST==17
		.int -8, -2, -1, -1

	#elif TEST==18
		.int -15, -2, -1, -1

	#elif TEST==19
		.int -16, -2, -1, -1

	#else
		.error "Definir TEST entre 1..19"
#endif
.endm

lista:      linea0
				.irpc i, 123
						linea
        .endr

longlista:	.int   (.-lista)/4
resultado: .int	0
cociente:	.int	0
resto:  .int  0

formato:	.ascii "media \t = %11d \t resto \t = %11d\n"
					.asciz "\t = 0x %08x \t\t = 0x %08x\n"

.section .text
 main: .global  main

	mov     $lista, %rbx    #direccion de inicio de la lista
	mov  longlista, %ecx    #tam de lista
	call  division
	mov  %eax, cociente    #guardamos cociente(media) de la division
	mov  %edx, resto		#guardamos resto

	#Llamada y paso de parametros para llamada a pritnf:
	mov  $formato, %rdi
	mov  cociente, %esi
	mov  resto, %edx
	mov	 cociente, %ecx
	mov  resto, %r8d
	mov  $0,%eax	# varargin sin xmm
	call  printf

	mov  resultado, %edi
	call exit		# ==  exit(resultado)
	ret

division:
	xor %rax, %rax
	xor %rdx, %rdx
	xor %rsi, %rsi
	xor %rdi, %rdi

bucle:
	mov  (%rbx,%rsi,4), %eax
	cltq	           #convertir %eax a quad extendiendo el signo
  add	 %rax, %rdi  #acumulamos
	inc  %rsi        #incremento contador del bucle
	cmp  %rsi,%rcx   #comparo contador con tam de lista
	jne  bucle       #si no son iguales, vuelvo etiqueta bucle

	#si se ha recorrido toda la lista:
	mov  %rdi, %rax
	cqto
	idiv %rcx
	ret
