# encoding:utf-8

require_relative 'sorpresa.rb'

module Civitas
	class Sorpresa_ir_casilla < Sorpresa
		
		def initialize(tablero, valor, texto)
			super(texto)
			@tablero = tablero
			@valor = valor
		end
	
		def aplicar_a_jugador(actual, todos)
			if(jugador_correcto(actual, todos))
				informe(actual, todos)
				
				casilla_actual = todos[actual].num_casilla_actual()
				tirada = @tablero.calcular_tirada(casilla_actual, @valor)
				nueva_pos = @tablero.nueva_posicion(casilla_actual, tirada)
				
				todos[actual].mover_a_casilla(nueva_pos)
				@tablero.casilla(nueva_pos).recibe_jugador(actual, todos)
			end
		end
		
		def to_string()
			
			info = super
			info += "Valor: #{@valor}\n"
			return info
		end
		
	end
end
