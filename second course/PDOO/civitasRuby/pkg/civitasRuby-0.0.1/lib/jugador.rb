# encoding:utf-8

require_relative 'diario'
require_relative 'sorpresa'
require_relative 'mazo_sorpresas'
require_relative 'tipo_sorpresa'
require_relative 'titulo_propiedad'

module Civitas
	
	class Jugador
	
		private_class_method :new
		
		attr_reader :nombre, :num_casilla_actual, 
			          :propiedades, :puede_comprar, :saldo,
								:encarcelado, :salvoconducto
		
		@@CASAS_MAX = 4
		@@CASAS_POR_HOTEL = 4
		@@HOTELES_MAX = 4
		@@PASO_POR_SALIDA = 1000.0
		@@PRECIO_LIBERTAD = 200.0
		@@SALDO_INICIAL = 5000.0
		
		def initialize(encarcelado, nombre, num_casilla_actual, puede_comprar, saldo, propiedades, salvoconducto)
			@encarcelado = encarcelado
			@nombre = nombre
			@num_casilla_actual = num_casilla_actual
			@puede_comprar = puede_comprar
			@saldo = saldo
			@propiedades = propiedades
			@salvoconducto = salvoconducto
		end
		
		def self.new_por_nombre(nombre)
			new(false, nombre, 0, true, @@SALDO_INICIAL, Array.new(), nil)
		end
		
		def self.new_por_copia(jugador)
			new(jugador.encarcelado(), jugador.nombre(), jugador.num_casilla_actual(), jugador.puede_comprar(), 
				jugador.saldo, jugador.propiedades(), jugador.salvoconducto())
		end
		
		private
		
		def perder_salvoconducto()
			@salvoconducto.usada()
			@salvoconducto = nil
		end
		
		def puedo_gastar(precio)
			resultado = false
			
			if(!@encarcelado)
				resultado = (@saldo >= precio)
			end
			
			return resultado
		end
		
		def puede_salir_carcel_pagando()
			return @saldo >= @@PRECIO_LIBERTAD
		end
		
		def existe_la_propiedad(ip)
			existe = false
			
			if(!@propiedades.empty? && ip >= 0 && ip < @propiedades.size())
				existe = true
			end
			
			return existe
		end
	
		def puedo_edificar_casa(propiedad)
			return propiedad.num_casas() <= @@CASAS_MAX
		end
		
		def puedo_edificar_hotel(propiedad)
			result = false
			precio = propiedad.precio_edificar()
			
			if(puedo_gastar(precio) && propiedades.num_hoteles() < @@HOTELES_MAX && propiedad.num_casas() >= @@CASAS_POR_HOTEL)
				result = true
			end
			
			return result
		end
		
		def casas_max()
			return @@CASAS_MAX
		end
		
		def hoteles_max()
			return @@HOTELES_MAX
		end
		
		def precio_libertad()
			return @@PRECIO_LIBERTAD
		end
		
		def premio_paso_salida()
			return @@PASO_POR_SALIDA
		end
		
		public
		
		def debe_ser_encarcelado()
			es_encarcelado = false
			
			if(!@encarcelado)
				if(!tiene_salvoconducto())
					es_encarcelado = true
				else
					perder_salvoconducto()
					Diario.instance.ocurre_evento("Jugador #{@nombre} se libra de la carcel
																				utilizando carta Salvoconducto")
				end
			end
			
			return es_encarcelado
		end
		
		def encarcelar(num_casilla_carcel)
			if(debe_ser_encarcelado())
				mover_a_casilla(num_casilla_carcel)
				@encarcelado = true
				Diario.instance.ocurre_evento("Jugador #{@nombre} encarcelado")
			end
			
			return @encarcelado
		end
		
		def obtener_salvoconducto(sorpresa)
			salvoconducto_obtenido = false
			
			if(!@encarcelado)
				@salvoconducto = sorpresa
				salvoconducto_obtenido  = true
			end
			
			return salvoconducto_obtenido
		end
		
		def tiene_salvoconducto()
			return @salvoconducto != nil
		end
		
		def puede_comprar_casilla()
			if(@encarcelado)
				@puede_comprar = false
			else
				@puede_comprar = true
			end
			
			return @puede_comprar
		end
		
		def paga(cantidad)
			
			resultado = modificar_saldo(cantidad * -1)
			
			return resultado
		end
		
		def paga_impuesto(cantidad)
			se_paga = false
			
			if(!@encarcelado)
				se_paga = paga(cantidad)
			end
			
			return se_paga
		end
		
		def paga_alquiler(cantidad) #IMPLEMENTACION TEMPORAL
			se_paga = false
			
			if(!@encarcelado)
				se_paga = paga(cantidad)
			end
			return se_paga
		end
		
		def recibe(cantidad)
			se_recibe = false
			
			if(!@encarcelado)
				se_recibe = modificar_saldo(cantidad)
			end
			
			return se_recibe
		end
		
		def modificar_saldo(cantidad)
			@saldo += cantidad
			Diario.instance.ocurre_evento("Saldo de #{@nombre} modificado en #{cantidad} unidades")
			
			return true
		end
		
		def mover_a_casilla(num_casilla)
			mov_completado = false
			
			if(!@encarcelado)
				mov_completado = true
				@num_casilla_actual = num_casilla
				@puede_comprar = false
				Diario.instance.ocurre_evento("#{@nombre} se ha movido a la casilla #{@num_casilla_actual}")
			end
			
			return mov_completado
		end
		
		def vender(ip)
			vendido = false
			
			if(!@encarcelado && existe_la_propiedad(ip))
				vendido = @propiedades[ip].vender(self)
			end
			
			if(vendido) 
				Diario.instance.ocurre_evento("#{@nombre} vende la propiedad #{@propiedades[ip].nombre()}")
			end
			
			return vendido
		end
		
		def tiene_algo_que_gestionar()
			return !@propiedades.empty?
		end
		
		def salir_carcel_pagando()
			sale_carcel = false
			
			if(@encarcelado && puede_salir_carcel_pagando())
				sale_carcel = true
				paga(@@PRECIO_LIBERTAD)
				@encarcelado = false
				Diario.instance.ocurre_evento("#{@nombre} ha sido puesto en libertad pagando")
			end
			
			return sale_carcel
		end
		
		def salir_carcel_tirando()
			sale_carcel = Dado.instance.salgo_de_la_carcel()
			
			if(@encarlado && sale_carcel)
				sale_carcel = true
				@encarcelado = false
				Diario.inatance.ocurre_evento("#{@nombre} ha salido de la carcel tirando el dado")
			end
			
			return sale_carcel
		end
		
		def pasa_por_salida()
			modificar_saldo(@@PASO_POR_SALIDA)
			Diario.instance.ocurre_evento("#{@nombre} ha pasado por la salida")
			
			return true
		end
		
		
		def compare_to(otro)
=begin
			Si a < b retorna -1
      Si a = b retorna  0
      Si a > b retorna  1
      Si a y b no son comparables retorna null
=end
      return @saldo <=> otro.saldo
		end
		
	
		
		def cancelar_hipoteca(ip)
			result = false
			
			if(!@encarcelado && existe_la_propiedad(ip))
				propiedad = @propiedades[ip]
				cantidad = propiedad.importe_cancelar_hipoteca()
				
				if(puedo_gastar(cantidad))
					result = propiedad.cancelar_hipoteca(self)
				end
				
				if(result)
					Diario.instance.ocurre_evento("El jugador #{@nombre} cancela la hipoteca de la propiedad #{ip}")
				end
			end
			
			return result;
		end	
		
		def comprar(titulo)
			result = false
			
			if(!@encarcelado && @puede_comprar)
				precio = titulo.precio_compra()
				
				if(puedo_gastar(precio))
					result = titulo.comprar(self)
				end
				
				if(result)
					@propiedades << titulo
					Diario.instance.ocurre_evento("El jugador #{@nombre} compra la propiedad #{titulo.to_string()}")
				end
				
				@puede_comprar = false
			end
			
			return result
		end
		
		def construir_hotel(ip)
			result = false
			
			if(!@encarcelado && existe_la_propiedad(ip))
				propiedad = @propiedades[ip]
				puedo_edificar_hotel = puedo_edificar_hotel(propiedad)
				
				if(puedo_edificar_hotel)
					result = propiedad.construir_hotel(self)
					casas_por_hotel = @@CASAS_POR_HOTEL
					propiedad.derruir_casas(casas_por_hotel, self)
					Dado.instance.ocurre_evento("El jugador #{@nombre} construye hotel en la propiedad #{ip}")
				end
				
			end
			
			return result
		end
		
		def construir_casa(ip)
			result = false
			
			if(!@encarcelado && existe_la_propiedad(ip))
				propiedad = @propiedades[ip]
				puedo_edificar_casa = puedo_edificar_casa(propiedad)
					
				if(puedo_edificar_casa)
					result = propiedad.construir_casa(self)
				end
				
				if(result)
					Diario.instance.ocurre_evento("El jugador #{nombre} construye casa en la propiedad #{ip}")
				end
			end
			
			return result
		end
		
		def hipotecar(ip)
			result = false
			
			if(!@encarcelado && existe_la_propiedad(ip))
				propiedad = @propiedades[ip]
				result = propiedad.hipotecar(self)
				
				if(result)
					Diario.instance.ocurre_evento("El jugador #{@nombre} hipoteca la propiedad #{ip}")
				end
			end
			
			return result
		end
		
		def cantidad_casas_hoteles()
			num_casas_hoteles = 0
			
			for y in (0 ... @propiedades.size())
				num_casas_hoteles += @propiedades[y].cantidad_casas_hoteles()
			end
			
			return num_casas_hoteles
		end
		
		def en_bancarrota()
			return @saldo < 0
		end
		
		def to_string()
			datos = "Nombre: #{@nombre}
							\nSaldo: #{@saldo}
							\nEncarcelado: #{@encarcelado}
							\nCasilla actual: #{@num_casilla_actual}
							\nPuede comprar: #{@puede_comprar}
							\nSalvoconducto: #{tiene_salvoconducto()}"
			
			return datos;
		end 
	end
end
