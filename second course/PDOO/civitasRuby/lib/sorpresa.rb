# encoding:utf-8

require_relative 'diario'
require_relative 'mazo_sorpresas'
require_relative 'tablero'
require_relative 'jugador'
require_relative 'casilla'

module Civitas
	
	class Sorpresa # TESTED
		
		def initialize(texto)
			@texto = texto
		end
		
		public
		
		def informe(actual, todos)
			Diario.instance.ocurre_evento(todos[actual].nombre() + " ha activado una sorpresa. ")
		end
		
		def jugador_correcto(actual, todos)
			return actual >= 0 && actual < todos.size()
		end
		

		def aplicar_a_jugador(actual, todos)
		end

		
		def to_string()
			return "Sorpresa: #{@texto}\n"
		end	
	
		
	end
end
