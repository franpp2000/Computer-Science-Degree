# encoding:utf-8

require_relative 'casilla.rb'

module Civitas
	class Casilla_juez < Casilla
		
		@@carcel = -1
		
		def initialize(num_casilla_carcel, nombre)
			super(nombre)
			@@carcel = num_casilla_carcel
		end
		
		def recibe_jugador(iactual, todos)
			if(jugador_correcto(iactual, todos))
				informe(iactual, todos)
				todos[iactual].encarcelar(@@carcel)
			end
		end
		
		def to_string()
			info = super
			
			if(@@carcel > 0)
				info += "\n\tCasilla Carcel: #{@@carcel}" 
			end
			
			return info
		end
		
	end
end
