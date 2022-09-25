# encoding:utf-8

require_relative 'casilla.rb'

module Civitas
	class Casilla_calle < Casilla
		
		attr_reader :titulo_propiedad
		
		def initialize(titulo)
			super(titulo.nombre())
			@titulo_propiedad = titulo
		end
		
		def recibe_jugador(iactual, todos)
			if(jugador_correcto(iactual, todos))
				informe(iactual, todos)
				
				jugador = todos[iactual]
				
				if(!@titulo_propiedad.tiene_propietario())
					jugador.puede_comprar_casilla()
				else
					@titulo_propiedad.tramitar_alquiler(jugador)
				end
			end
		end
		
		def to_string()
			info = super
			
			if(@titulo_propiedad != nil)
				info += "\n\t Titulo Propiedad: #{@titulo_propiedad.to_string()}"
			end
			
			return info
		end
		
	end
end