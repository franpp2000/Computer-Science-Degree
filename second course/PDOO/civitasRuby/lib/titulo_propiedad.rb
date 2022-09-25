# encoding:utf-8

module Civitas
	class Titulo_propiedad
		
		attr_reader   :num_casas, :num_hoteles, :precio_compra,
                  :precio_edificar, :propietario, :hipotecado, :nombre
		
		@FACTOR_INTERESES_HIPOTECA = 1.1
		
		def initialize(nom, ab, fr, hb, pc, pe)
			@nombre = nom
			@alquiler_base = ab
			@factor_revalorizacion = fr
			@hipoteca_base = hb
			@precio_compra = pc
			@precio_edificar = pe
			@propietario = nil
			@num_casas = 0
			@num_hoteles = 0
			@hipotecado = false 
		end
		
		private
		
		def precio_alquiler()
			precio_alquiler = 0 #inicializando al caso de estar hipotecado
			                    #o esta el propietario encarcelado
													
			if(!propietario_encarcelado && !@hipotecado)
					precio_alquiler = @alquiler_base * (1 + (@num_casas * 0.5) + (@num_hoteles * 2.5))
			end
			
			return precio_alquiler
		end
		
		def propietario_encarcelado()
			encarcelado = true
			
			if(!@propietario.encarcelado() || !tienePropietario())
				encarcelado = false
			end
			
			return encarcelado
		end
		
		def precio_venta()
			return @precio_compra + (cantidad_casas_hoteles() * @precio_edificar) * @factor_revalorizacion
		end
		
		def es_este_el_propietario(jugador)
			return jugador == propietario
		end
		
		def importe_hipoteca()
			return @hipoteca_base * (1 + (@num_casas * 0.5) + (@num_hoteles * 2.5))
		end
		
		
		public
		
		def to_string()
			return "\n\t\tnombre: #{@nombre}
							\n\t\tAlquiler Base: #{@alquiler_base}
              \n\t\tfactor revalorizacion: #{@factor_revalorizacion} 
              \n\t\thipoteca base: #{@hipoteca_base} 
							\n\t\thipotecado: #{@hip}
              \n\t\tnºcasas: #{@num_casas}  
							\n\t\tnºhoteles: #{@num_hoteles} 
              \n\t\tprecio compra: #{@precio_compra}
              \n\t\tprecio edificar: #{@precio_edificar}"
		end
		
		def importe_cancelar_hipoteca()
			cantidad_recibida = @hipoteca_base * (1 + (@num_casas * 0.5) + (@num_hoteles * 2.5))
			
			return cantidad_recibida * @FACTOR_INTERESES_HIPOTECA
		end
		
		def tramitar_alquiler(jugador)
			if(tiene_propietario() && !es_este_el_propietario(jugador))
				alquiler = precio_alquiler()
				
				jugador.paga_alquiler(alquiler)
				@propietario.recibe(alquiler)
			end
			
		end
		
		def cantidad_casas_hoteles()
			return @num_casas + @num_hoteles
		end
		
		def derruir_casas(n, jugador)
			casa_derruida = false
			
			if(es_este_el_propietario(jugador) && @num_casas >= n)
				@num_casas -= n
				casa_derruida = true
			end
			
			return casa_derruida
		end
		
		def vender(jugador)
			vendido = false
			
			if(es_este_el_propietario(jugador) && !@hipotecado)
				jugador.recibe(precio_venta())
				@num_casas = 0
				@num_hoteles = 0
				@propietario = nil
				vendido = true
			end
			
			return vendido
		end
		
		def actualiza_propietario_por_conversion(jugador)
			@propietario = jugador
		end
		
		def hipotecar(jugador)
			salida = false
			
			if(!@hipotecado && es_este_el_propietario(jugador))
				jugador.recibe(importe_hipoteca())
				@hipotecado = true
				salida = true
			end
			
			return salida
		end
		
		def cancelar_hipoteca(jugador)
			result = false
			
			if(@hipotecado && es_este_el_propietario(jugador))
				@propietario.paga(importe_cancelar_hipoteca())
				@hipotecado = false
				result = true
			end
			
			return result
		end
		
		def comprar(jugador)
			result = false
			
			if(!tiene_propietario())
				@propietario = jugador
				result = true
				@propietario.paga(@precio_compra)
			end
			
			return result
		end
		
		def construir_casa(jugador)
			result = false
			
			if(es_este_el_propietario(jugador))
				result = true
				@num_casas += 1
				jugador.paga(@precio_edificar)
			end
			
			return result
		end
		
		def construir_hotel(jugador)
			result = false
			
			if(es_este_el_propietario(jugador))
				jugador.paga(@precio_edificar)
				@num_hoteles += 1
				result = true
			end
			
			return result
		end
		
		def importe_hipoteca()
			return @hipoteca_base * (1 + (@num_casas * 0.5) + (@num_hoteles * 2.5))
		end
		
		def tiene_propietario()
			return propietario != nil
		end
		
		

	end	
end
