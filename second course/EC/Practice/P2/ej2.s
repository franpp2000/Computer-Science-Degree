.section .data

#ifndef TEST
#define TEST 7
#endif

.macro linea
#if TEST==1
	.int 1,1,1,1
#elif TEST==2
	.int 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF, 0x0FFFFFFF
#elif TEST==3
	.int 0x10000000, 0x10000000, 0x10000000, 0x10000000
#elif TEST==4
	.int 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
#elif TEST==5
	.int -1,-1,-1,-1
#elif TEST==6
	.int 200000000, 200000000, 200000000, 200000000
#elif TEST==7
	.int 300000000, 300000000, 300000000, 300000000
#else
	.error "Definir TEST entre 1..7"
#endif
.endm

lista: .irpc i, 1234
		linea
       .endr

longlista:	.int   (.-lista)/4
resultado:	.quad   0

formato:	.ascii "resultado \t = %18lu (uns)\n"
					.ascii "\t\t = 0x%18lx (hex)\n"
					.asciz "\t\t = 0x %08x %08x \n"

.section .text
 main: .global main

	mov     $lista, %rbx    #direccion de inicio de lista a registro rbx
	mov  longlista, %ecx    #tam de lista en registro ecx, se pone a cero 32 bits superiores de rcx
	call suma		# == suma(&lista, longlista);
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
	xor %eax, %eax   #inicializar registro que guardara la suma hasta 32 bits a 0
	xor  %rsi, %rsi   #inicializar registro que guardara el indice del bucle 0
	xor %edx, %edx   #inicializar contador de acarreos a 0
bucle:
	add  (%rbx,%rsi,4), %eax    #Acumulo suma de elementos de la lista
	adc  $0, %edx               #Si flag de acarreo esta a 1, acumulo este en edx
	inc   %rsi        	    #incremento contador del bucle
	cmp   %rsi,%rcx   	    #comparo contador con tam de lista
	jne   bucle       	    #si no son iguales, vuelvo etiqueta bucle (no se ha recorrido la lista totalmente aun)
	ret               	    #si se ha recorrido toda la lista fin de la rutina de suma
