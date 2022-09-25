# encoding:utf-8

require_relative "casilla"

module Civitas
	
	class Tablero
		
		attr_reader :num_casilla_carcel
		
		
		def initialize(pos_carcel)
			if(pos_carcel >= 1)
				@num_casilla_carcel = pos_carcel
			else
				@num_casilla_carcel = 1
			end
			
			@casillas = Array.new()
			@casillas << Casilla.new_por_nombre("Salida")
			
			@por_salida = 0
			
			@tiene_juez = false			
		end
		
		
		private
		
		def correct()
			return (@casillas.size() > @num_casilla_carcel) && @tiene_juez
		end
		
	
		def correcto(num_casilla)
			indice_valido = (num_casilla >= 0 && num_casilla < @casillas.size()) 
			
			return correct() && indice_valido 
		end
		
		
		public
		
		def por_salida()
			veces_por_salida = @por_salida
			
			if(@por_salida > 0)
				@por_salida -= 1
			end
			
			return veces_por_salida
		end
		
		def tam_tablero()
			return @casillas.size()
		end
		
		
		def añade_casilla(casilla)
			if(@casillas.size() == @num_casilla_carcel)
				@casillas << Casilla.new_por_nombre("Carcel")
			end
			
			@casillas << casilla
			
			if(@casillas.size() == @num_casilla_carcel)
				@casillas << Casilla.new_por_nombre("Carcel")
			end
			
		end
		
	
		def añade_juez()
			if(!@tiene_juez)
				añade_casilla(Casilla.new_por_juez(@num_casilla_carcel, "Juez"))
				@tiene_juez = true
			end
		end
		
		
		def casilla(num_casilla)
			return correcto(num_casilla)? @casillas[num_casilla] : nil
		end
		
		
		def nueva_posicion(actual, tirada)
			nueva_pos_actual = -1
			
			if(correct())
				nueva_pos_actual = (actual + tirada) % @casillas.size()
				
				if(actual + tirada != nueva_pos_actual)
					@por_salida += 1
				end
			end
			
			return nueva_pos_actual
		end
		
		
		def calcular_tirada(origen, destino)
			tirada = destino - origen
			
			if(tirada < 0)
				tirada += @casillas.size()
			end
			
			return tirada	
		end
		
		
	end   
end
