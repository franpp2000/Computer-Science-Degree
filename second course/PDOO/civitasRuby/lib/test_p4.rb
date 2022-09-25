# encoding:utf-8

require_relative 'civitas_juego'
require_relative 'sorpresa_especulador'
require_relative 'diario.rb'

module Civitas
	class Test_p4
		
		def self.main()
			new_york = Titulo_propiedad.new("new york", 25.0,50.0,1000.0,2000.0,500.0)
			
			j1 = Jugador.new_por_nombre("Francisco")
			
			j1.puede_comprar_casilla()
			j1.comprar(new_york)
			new_york.actualiza_propietario_por_conversion(j1)
			
			puts j1.to_string()
			puts new_york.to_string()
			j1.paga_impuesto(200)
			
			convertir = Sorpresa_especulador.new(150)
			todos = Array.new()
			todos << j1
			
			convertir.aplicar_a_jugador(0, todos)
			
			puts new_york.propietario.to_string
			
			todos[0].paga_impuesto(200)
			
			while(Diario.instance.eventos_pendientes)
				puts Diario.instance.leer_evento()
			end
			
			puts casas_max
			
			puts casas_max
		
		end
		
	end
	
	Test_p4.main()

end


