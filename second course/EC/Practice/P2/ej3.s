.section .data

#ifndef TEST
#define TEST 20
#endif

.macro linea
	#if TEST==1
		.int -1,-1,-1,-1

	#elif TEST==2
		.int 0x04000000, 0x04000000, 0x04000000, 0x04000000

	#elif TEST==3
		.int 0x08000000, 0x08000000, 0x08000000, 0x08000000

	#elif TEST==4
		.int 0x10000000, 0x10000000, 0x10000000, 0x10000000

	#elif TEST==5
		.int 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF

	#elif TEST==6
		.int 0x80000000, 0x80000000, 0x80000000, 0x80000000

	#elif TEST==7
		.int 0xF0000000, 0xF0000000, 0xF0000000, 0xF0000000

	#elif TEST==8
		.int 0xF8000000, 0xF8000000, 0xF8000000, 0xF8000000

	#elif TEST==9
		.int 0xF7FFFFFF, 0xF7FFFFFF, 0xF7FFFFFF, 0xF7FFFFFF

	#elif TEST==10
		.int 100000000, 100000000, 100000000, 100000000

	#elif TEST==11
		.int 200000000, 200000000, 200000000, 200000000

	#elif TEST==12
		.int 300000000, 300000000, 300000000, 300000000

	#elif TEST==13
		.int 2000000000, 2000000000, 2000000000, 2000000000

	#elif TEST==14
		.int 3000000000, 3000000000, 3000000000, 3000000000

	#elif TEST==15
		.int -100000000, -100000000, -100000000, -100000000

	#elif TEST==16
		.int -200000000, -200000000, -200000000, -200000000

	#elif TEST==17
		.int -300000000, -300000000, -300000000, -300000000

	#elif TEST==18
		.int -2000000000, -2000000000, -2000000000, -2000000000

	#elif TEST==19
		.int -3000000000, -3000000000, -3000000000, -3000000000

	#else
		.error "Definir TEST entre 1..19"

#endif
.endm

lista: .irpc i, 1234
						linea
       .endr

longlista:	.int   (.-lista)/4
resultado:	.quad	 0

formato:	.ascii "resultado \t = %18ld (sgn)\n"
					.ascii "\t\t = 0x%18lx (hex)\n"
					.asciz "\t\t = 0x %08x %08x \n"

.section .text

 main: .global  main

	mov     $lista, %rbx    #direccion de inicio de lista a registro rbx
	mov  longlista, %ecx    #tam de lista en registro ecx, se pone a cero 32 bits superiores de rcx
	call suma		            # == suma(&lista, longlista);
	mov  %eax, resultado    #guardamos 32 bits inferiores de la suma
	mov  %edx, resultado+4  #guardamos 32 bits superiores de la suma

	#Llamada paso de parametros para llamada a pritnf:
	mov   $formato, %rdi
	mov   resultado,%rsi
	mov   resultado,%rdx
	mov   resultado+4,%ecx
	mov   resultado,%r8
	mov          $0,%eax	# varargin sin xmm
	call  printf		# == printf(formato, res, res);

	mov  resultado, %edi
	call _exit		# ==  exit(resultado)
	ret

suma:
	xor 	%eax, %eax  #inicializar a 0 LSB
	xor	  %edx, %edx  #inicializar  a 0 MSB
	xor	  %esi, %esi	#inicializar a 0 indice vector
	xor   %ebp, %ebp  #inicializar a 0 registro acumulador de LSB
	xor   %edi, %edi  #inicializar a 0 registro acumulador de MSB

bucle:
	mov  (%rbx,%rsi,4), %eax

	cdq		#Convertir %eax a quad, a traves de extension de signo
				#la cual es guardada en %edx

  add	 %eax, %ebp  #acumular LSB
	adc  %edx, %edi  #acumular MSB
	inc  %rsi        #incremento contador del bucle
	cmp  %rsi,%rcx   #comparo contador con tam de lista
	jne  bucle       #si no son iguales, vuelvo etiqueta bucle

	#si se ha recorrido toda la lista:
	mov %ebp, %eax
	mov %edi, %edx
	ret
