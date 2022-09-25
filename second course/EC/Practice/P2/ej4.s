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
cociente:	.int	0
resto:  .int  0

formato:	.ascii "media \t = %11d \t resto \t = %11d\n"
					.asciz "\t = 0x %08x \t\t = 0x %08x\n"

# opción: 1) no usar printf, 2)3) usar printf/fmt/exit, 4) usar tb main
# 1) as  suma.s -o suma.o
#    ld  suma.o -o suma					1232 B
# 2) as  suma.s -o suma.o				6520 B
#    ld  suma.o -o suma -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2
# 3) gcc suma.s -o suma -no-pie –nostartfiles		6544 B
# 4) gcc suma.s -o suma	-no-pie				8664 B

.section .text
#_start: .global _start
 main: .global  main

	mov     $lista, %rbx    #direccion de inicio de lista a registro rbx
	mov  longlista, %ecx    #tam de lista en registro ecx, se pone a cero 32 bits superiores de rcx
	call division
	mov  %eax, cociente    #guardamos media
	mov  %edx, resto		#guardamos resto

	#Llamada paso de parametros para llamada a pritnf:
	mov  $formato, %rdi
	mov  cociente, %esi
	mov  resto, %edx
	mov	 cociente, %ecx
	mov  resto, %r8d
	mov  $0,%eax	# varargin sin xmm
	call  printf		# == printf(formato, res, res);

	mov  cociente, %edi
	mov  resto, %esi
	call _exit		# ==  exit(resultado)
	ret

division:
  xor   %eax, %eax  #inicializar a 0 LSB
  xor   %edx, %edx  #inicializar  a 0 MSB
  xor   %esi, %esi  #inicializar a 0 indice vector
  xor   %ebp, %ebp  #inicializar a 0 registro acumulador de LSB
  xor   %edi, %edi  #inicializar a 0 registro acumulador de MSB

bucle:
	mov  (%rbx,%rsi,4), %eax
	cdq	           #convertir %eax a quad extendiendo el signo
  add	 %eax, %ebp  #acumular LSB
	adc  %edx, %edi  #acumular MSB
	inc  %rsi        #incremento contador del bucle
	cmp  %rsi,%rcx   #comparo contador con tam de lista
	jne  bucle       #si no son iguales, vuelvo etiqueta bucle

	#si se ha recorrido toda la lista:
	mov %ebp, %eax
	mov %edi, %edx

	idiv %ecx
	ret
