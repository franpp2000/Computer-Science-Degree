# encoding:utf-8

require_relative 'jugador'
require_relative 'titulo_propiedad'
require_relative 'sorpresa'

module Civitas
	class Casilla
		
		attr_reader :nombre
		
		def initialize(nombre)
			@nombre = nombre
		end
		
		def recibe_jugador(iactual, todos)
			informe(iactual, todos)
		end
		
		def informe(iactual, todos)
			Diario.instance.ocurre_evento("El jugador " + todos[iactual].nombre() + "ha caido en \n" + to_string())
		end
		
		def to_string()
			return "Casilla : #{@nombre}"
		end
		
		def jugador_correcto(iactual, todos)
			return (iactual >= 0 && iactual < todos.size())
		end
		
	end
	
end