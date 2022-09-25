# encoding:utf-8

require 'singleton'

module Civitas
	class Dado
		include Singleton
		
		attr_reader :ultimo_resultado
		
		@@SALIDA_CARCEL = 5
		
		def initialize()
			@random = Random.new()
			@ultimo_resultado = -1
			@debug = false
		end
		
		
		def tirar()
			
			maximo_resultado_tirada = 6

			if(!@debug)
				@ultimo_resultado = @random.rand(1 .. maximo_resultado_tirada)
			else
				@ultimo_resultado = 1
			end
			
			return @ultimo_resultado 
		end
		
		
		def salgo_de_la_carcel()
			return tirar() >= @@SALIDA_CARCEL
		end
		
		
		def quien_empieza(n)
			return @random.rand(0 ... n)
		end
		
		
		def set_debug(d)
			@debug = d
			modo = @debug? "ON" : "OFF"
			Diario.instance.ocurre_evento("Modo debug del dado: #{modo}")	
		end
		
		
	end
end