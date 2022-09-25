# encoding:utf-8

require_relative 'casilla.rb'

module Civitas
	class Casilla_impuesto < Casilla
		
		def initialize(cantidad, nombre)
			super(nombre)
			@importe = cantidad
		end
		
		def recibe_jugador(iactual, todos)
			if(jugador_correcto(iactual, todos))
				informe(iactual, todos)
				todos[iactual].paga_impuesto(@importe)
			end
		end
		
		def to_string()
			info = super
			info += "\t\nImporte: #{@importe}"
			
			return info
		end
		
	end
end
