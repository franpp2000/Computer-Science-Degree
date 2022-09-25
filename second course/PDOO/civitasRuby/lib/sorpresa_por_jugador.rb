# encoding:utf-8

require_relative 'sorpresa.rb'

module Civitas
	class Sorpresa_por_jugador < Sorpresa
		
		def initialize(valor, texto)
			super(texto)
			@valor = valor
		end
		
		def aplicar_a_jugador(actual, todos)
			if(jugador_correcto(actual, todos))
				informe(actual, todos) 
				
				pagar = Sorpresa_pagar_cobrar.new(-1 * @valor, "Pagas #{@valor} a #{todos[actual]}")
				cobrar = Sorpresa_pagar_cobrar.new((todos.size() - 1) * @valor, "Recibes #{@valor} de cada jugador")
				
				for i in (0 ... todos.size())
					if(i != actual)
						pagar.aplicar_a_jugador(i, todos)
					end
				end
				
				cobrar.aplicar_a_jugador(actual, todos)
				
			end
		end
		
		def to_string()
			info = super
			info += "Valor: #{@valor}\n"
			return info
		end
		
	end
end
