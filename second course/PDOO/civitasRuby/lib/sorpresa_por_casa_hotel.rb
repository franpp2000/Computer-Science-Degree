# encoding:utf-8

require_relative 'sorpresa.rb'

module Civitas
	class Sorpresa_por_casa_hotel < Sorpresa
		
		def initialize(valor, texto)
			super(texto)
			@valor = valor
		end
		
		def aplicar_a_jugador(actual, todos)
			if(jugador_correcto(actual, todos))
				informe(actual, todos)
				todos[actual].modificar_saldo(@valor * todos[actual].cantidad_casas_hoteles())
			end
		end
		
		def to_string()
			info = super
			info += "Valor: #{@valor}\n"
			return info
		end

	end
end
