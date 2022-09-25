# encoding:utf-8

require_relative 'sorpresa.rb'

module Civitas
	class Sorpresa_ir_carcel < Sorpresa
		
		def initialize(tablero)
			super("Mandado a la casilla carcel")
			@tablero = tablero
		end
		
		def aplicar_a_jugador(actual, todos)
			if(jugador_correcto(actual, todos))
				informe(actual, todos)
				todos[actual].encarcelar(@tablero.num_casilla_carcel())
			end
		end
		
		def to_string()
			return super
		end
		
	end
end
