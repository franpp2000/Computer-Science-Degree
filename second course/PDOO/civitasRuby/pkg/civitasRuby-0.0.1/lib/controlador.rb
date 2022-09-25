#encoding:utf-8

require_relative 'civitas_juego'
require_relative 'vista_textual'
require_relative 'operaciones_juego'
require_relative 'respuestas'
require_relative 'salidas_carcel'
require_relative 'operacion_inmobiliaria'
require_relative 'gestiones_inmobiliarias'

module Civitas
	class Controlador
		
		def initialize(juego, vista)
			@juego = juego
			@vista = vista
		end
		
		def juega()
			@vista.set_civitas_juego(@juego)
			
			while(!@juego.final_del_juego())
				
				@vista.actualizar_vista()
				@vista.pausa()
				
				sig_operacion = @juego.siguiente_paso()
				@vista.mostrar_siguiente_operacion(sig_operacion)
				
				if(sig_operacion != Operaciones_juego::PASAR_TURNO)
					@vista.mostrar_eventos();
				end
				
				if(!@juego.final_del_juego())
					case(sig_operacion)
					
					when Operaciones_juego::COMPRAR
						if(@vista.comprar() == Respuestas::SI)
							@juego.comprar()
						end
	
					when Operaciones_juego::GESTIONAR
						@vista.gestionar()
						 lista_gestiones_inmobiliarias = [Gestiones_inmobiliarias::VENDER,
              Gestiones_inmobiliarias::HIPOTECAR,Gestiones_inmobiliarias::CANCELAR_HIPOTECA,
              Gestiones_inmobiliarias::CONSTRUIR_CASA,Gestiones_inmobiliarias::CONSTRUIR_HOTEL,
              Gestiones_inmobiliarias::TERMINAR]
            
						operacion = Operacion_inmobiliaria.new(lista_gestiones_inmobiliarias[@vista.gestion()], @vista.propiedad())
						
						case(operacion.gestion_inm())
						
						when Gestiones_inmobiliarias::VENDER
							@juego.vender(operacion.indice())
						
						when Gestiones_inmobiliarias::HIPOTECAR
							@juego.hipotecar(operacion.indice())
						
						when Gestiones_inmobiliarias::CANCELAR_HIPOTECA
							@juego.cancelar_hipoteca(operacion.indice())
							
						when Gestiones_inmobiliarias::CONSTRUIR_CASA
							@juego.construir_casa(operacion.indice())
							
						when Gestiones_inmobiliarias::CONSTRUIR_HOTEL
							@juego.construir_hotel(operacion.indice())
							
						when Gestiones_inmobiliarias::TERMINAR
							@juego.siguiente_paso()
							
						end
						
					when Operaciones_juego::SALIR_CARCEL
						if(@vista.salir_carcel() == Salidas_carcel::PAGANDO)
							@juego.salir_carcel_pagando()
						else
							@juego.salir_carcel_tirando()
						end
						
						@juego.siguiente_paso()
					end
				end
			end
			
			jugadores = @juego.ranking()
			
			puts "Ranking:"
			for i in (0 ... jugadores.size())
				puts jugadores[i].nombre()
			end
			
		
		end
	end
end
