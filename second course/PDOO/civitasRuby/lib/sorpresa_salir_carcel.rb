# encoding:utf-8

require_relative 'sorpresa.rb'

module Civitas
	class Sorpresa_salir_carcel < Sorpresa
		
		def initialize(mazo)
			super("Escapas de prision")
			@mazo = mazo
		end
		
		def salir_del_mazo()
			@mazo.inhabilitar_carta_especial(self)
		end
		
		def usada()
			@mazo.habilitar_carta_especial(self)
		end
		
		def aplicar_a_jugador(actual, todos)
			if(jugador_correcto(actual, todos))
				informe(actual, todos)
				
				hay_salvo_conducto = false
				
				for i in (0 ... todos.size())
					if(todos[i].tiene_salvoconducto())
						hay_salvo_conducto = true
					end
				end
				
				if(!hay_salvo_conducto)
					todos[actual].obtener_salvoconducto(self)
					salir_del_mazo()
				end
			end	
		end
		
		def to_string()
			return super
		end
		
	end
end
