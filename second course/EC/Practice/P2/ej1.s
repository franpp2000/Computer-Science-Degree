.section .data
lista:		.int 0x10000000, 0x10000000, 0x10000000, 0x10000000
					.int 0x10000000, 0x10000000, 0x10000000, 0x10000000
					.int 0x10000000, 0x10000000, 0x10000000, 0x10000000
					.int 0x10000000, 0x10000000, 0x10000000, 0x10000000

longlista:	.int   (.-lista)/4
resultado:	.quad   0
formato: 	.asciz	"suma = %lu = 0x%lx hex\n"


.section .text

 main: .global  main

	mov     $lista, %rbx    #direccion de inicio de lista a registro rbx
	mov  longlista, %ecx    #tam de lista en registro ecx, se pone a cero 32 bits superiores de rcx
	call suma								# == suma(&lista, longlista);
	mov  %eax, resultado    #guardamos 32 bits inferiores de la suma
	mov  %edx, resultado+4  #guardamos 32 bits superiores de la suma

	#Llamada paso de parametros para llamada a pritnf:
	mov   $formato, %rdi
	mov   resultado,%rsi
	mov   resultado,%rdx
	mov          $0,%eax	# varargin sin xmm
	call  printf		# == printf(formato, res, res);

	mov  resultado, %edi
	call _exit		# ==  exit(resultado)
	ret

suma:
	xor %eax, %eax   #inicializar registro que guardara la suma hasta 32 bits a 0
	xor %rsi, %rsi   #inicializar registro que guardara el indice del bucle 0
	xor %edx, %edx   #inicializar contador de acarreos a 0
bucle:
	add  (%rbx,%rsi,4), %eax    #Acumulo suma de elementos de la lista
	jnc   no_acarreo            #Si no acarreo salto a etiqueta no_acarreo
	inc   %edx                  #Si acarreo, acumulo este en edx

no_acarreo:
	inc   %rsi        #incremento contador del bucle
	cmp   %rsi,%rcx   #comparo contador con tam de lista
	jne   bucle       #si no son iguales, vuelvo etiqueta bucle (no se ha recorrido la lista totalmente aun)
	ret               #si se ha recorrido toda la lista fin de la rutina de suma
