# encoding:utf-8

require_relative 'sorpresa.rb'
require_relative 'jugador_especulador'

module Civitas
	class Sorpresa_especulador < Sorpresa
		
		def initialize(fianza)
			super("Te conviertes en jugador especulador")
			@fianza = fianza
		end
		
		def aplicar_a_jugador(actual, todos)
			if(jugador_correcto(actual, todos))
			  informe(actual, todos)
				especulador = Jugador_especulador.new(todos[actual], @fianza)
				todos[actual] = especulador
			end
		end
		
		
	end
end
