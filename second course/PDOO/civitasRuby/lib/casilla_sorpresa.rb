# encoding:utf-8

require_relative 'casilla.rb'

module Civitas
	class Casilla_sorpresa < Casilla
		
		def initialize(mazo, nombre)
			super(nombre)
			@mazo = mazo
			@sorpresa = nil
		end
		
		def recibe_jugador(iactual, todos)
			if(jugador_correcto(iactual, todos))
				informe(iactual, todos)
				@sorpresa = @mazo.siguiente()
				@sorpresa.aplicar_a_jugador(iactual, todos)
			end
		end
		
		def to_string()
			info = super
			
			if(@sorpresa != nil)
				info += "\n\t Sorpresa: #{@sorpresa.to_string()}"
			end
			
			return info
		end
		
	end
end
