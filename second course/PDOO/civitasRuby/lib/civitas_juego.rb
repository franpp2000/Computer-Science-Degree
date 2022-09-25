# encoding:utf-8

require_relative 'jugador'
require_relative 'gestor_estados'
require_relative 'estados_juego'
require_relative 'dado'
require_relative 'sorpresa'
require_relative 'tablero'
require_relative 'titulo_propiedad'
require_relative 'diario'
require_relative 'casilla_calle'
require_relative 'casilla_sorpresa'
require_relative 'casilla_juez'
require_relative 'casilla_impuesto'
require_relative 'sorpresa_ir_carcel'
require_relative 'sorpresa_ir_casilla'
require_relative 'sorpresa_salir_carcel'
require_relative 'sorpresa_pagar_cobrar'
require_relative 'sorpresa_por_casa_hotel'
require_relative 'sorpresa_por_jugador'
require_relative 'sorpresa_especulador'

module Civitas
	
	class Civitas_juego
	
		def initialize(nombres)
			@jugadores = Array.new()
			
			for nombre in nombres
				@jugadores << Jugador.new_por_nombre(nombre)
			end
			
			@gestor_estados = Gestor_estados.new()
			@estado = @gestor_estados.estado_inicial()
			
			@indice_jugador_actual = Dado.instance.quien_empieza(@jugadores.size())
			
			@mazo = Mazo_sorpresas.new()
			
			inicializar_tablero(@mazo)
			inicializar_mazo_sorpresas(@tablero)
		end
		
		
		private
		
		def inicializar_tablero(mazo)
			pos_carcel = 5
			@tablero = Tablero.new(pos_carcel)
			
			@tablero.añade_juez()
			
			num_sorpresas = 3
			for i in (0 ... num_sorpresas)
				#casilla_sorpresa = Casilla.new_por_mazo(mazo, "Casilla Sorpresa")
				casilla_sorpresa = Casilla_sorpresa.new(mazo, "Casilla Sorpresa")
				@tablero.añade_casilla(casilla_sorpresa)
			end
			
			num_calles = 12
			for i in(0 ... num_calles)
				prop = Titulo_propiedad.new("Calle #{i}", 100 * i, 3, 50 * i, 500 + 100 * i, 200)
				#casilla_calle = Casilla.new_por_titulo_propiedad(prop)
				casilla_calle = Casilla_calle.new(prop)
				@tablero.añade_casilla(casilla_calle)
			end
			
			@tablero.añade_juez()
			#@tablero.añade_casilla(Casilla.new_por_impuesto(100.0, "Impuesto"))
			@tablero.añade_casilla(Casilla_impuesto.new(100.0, "Impuesto"))
			@tablero.añade_casilla(Casilla.new("Parking"))
		end
		
		def inicializar_mazo_sorpresas(tablero)
			
			@mazo.al_mazo(Sorpresa_ir_carcel.new(tablero))
			@mazo.al_mazo(Sorpresa_ir_casilla.new(tablero, 16, "Movido a la casilla 16"))
			@mazo.al_mazo(Sorpresa_ir_casilla.new(tablero, 5, "Movido a la casilla 5"))
			@mazo.al_mazo(Sorpresa_salir_carcel.new(@mazo))
			@mazo.al_mazo(Sorpresa_pagar_cobrar.new(150, "Ganas 150 euros"))
			@mazo.al_mazo(Sorpresa_pagar_cobrar.new(-150, "Pierdes 150 euros"))
			@mazo.al_mazo(Sorpresa_por_casa_hotel.new(100, "Ganas 100 euros por cada casa/hotel"))
			@mazo.al_mazo(Sorpresa_por_casa_hotel.new(-50, "Pierdes 50 euros por cada casa/hotel"))
			@mazo.al_mazo(Sorpresa_por_jugador.new(100, "Cada jugador te dona 100 euros"))
			@mazo.al_mazo(Sorpresa_por_jugador.new(-50, "Donas a cada jugador 50 euros"))
			@mazo.al_mazo(Sorpresa_especulador.new(300))
      
		end
		
		def contabilizar_pasos_por_salida(jugador_actual)
			while(@tablero.por_salida() > 0)
				jugador_actual.pasa_por_salida();
			end
		end
		
		def pasar_turno()
			@indice_jugador_actual = (@indice_jugador_actual + 1) % @jugadores.size()
		end
		
		def avanza_jugador()
			jugador_actual = @jugadores[@indice_jugador_actual]
			posicion_actual = jugador_actual.num_casilla_actual()
			
			tirada = Dado.instance.tirar()
			posicion_nueva = @tablero.nueva_posicion(posicion_actual, tirada)
			casilla = @tablero.casilla(posicion_nueva)
			
			contabilizar_pasos_por_salida(jugador_actual)
			jugador_actual.mover_a_casilla(posicion_nueva)
			casilla.recibe_jugador(@indice_jugador_actual, @jugadores)
			contabilizar_pasos_por_salida(jugador_actual)
		end
		
		public
		
		def ranking()
			@jugadores.sort! { |a,b| a.saldo() <=> b.saldo()  }
			
			return @jugadores.reverse!
		end
		
		
		def siguiente_paso_completado(operacion)
			@estado = @gestor_estados.siguiente_estado(@jugadores[@indice_jugador_actual], @estado, operacion)
		end
		
		
		def siguiente_paso()
			jugador_actual = @jugadores[@indice_jugador_actual]
			operacion = @gestor_estados.operaciones_permitidas(jugador_actual, @estado)
			
			if(operacion == Operaciones_juego::PASAR_TURNO)
				pasar_turno()
			elsif(operacion == Operaciones_juego::AVANZAR)
				avanza_jugador();	
			end
			
			siguiente_paso_completado(operacion)
			
			return operacion	
		end
		
		
		
		def comprar()
			jugador_actual = @jugadores[@indice_jugador_actual]
			num_casilla_actual = jugador_actual.num_casilla_actual()
			casilla = @tablero.casilla(num_casilla_actual)
			titulo = casilla.titulo_propiedad()
			res = jugador_actual.comprar(titulo)
			
			return res
		end
		
		######################################
		
		def construir_casa(ip)
			return @jugadores[@indice_jugador_actual].construir_casa(ip)
		end

		def construir_hotel(ip)
			return @jugadores[@indice_jugador_actual].construir_hotel(ip)
		end
		
		def vender(ip)
			return @jugadores[@indice_jugador_actual].vender(ip)
		end
		
		def hipotecar(ip)
			return @jugadores[@indice_jugador_actual].hipotecar(ip)
		end
		
		def cancelar_hipoteca(ip)
			return @jugadores[@indice_jugador_actual].cancelar_hipoteca(ip)
		end
		
		def salir_carcel_pagando()
			return @jugadores[@indice_jugador_actual].salir_carcel_pagando()
		end
		
		def salir_carcel_tirando()
			return @jugadores[@indice_jugador_actual].salir_carcel_tirando()
		end
		
		def final_del_juego()
			jugador_en_bancarrota = false
			
			for jugador in @jugadores
				if(jugador.en_bancarrota())
					jugador_en_bancarrota = true
				end
			end
			
			return jugador_en_bancarrota
		end
		
		def casilla_actual()
			return @tablero.casilla(@jugadores[@indice_jugador_actual].num_casilla_actual())
		end
		
		def jugador_actual()
			return @jugadores[@indice_jugador_actual]
		end
		
		def info_jugador_texto()
			return @jugadores[@indice_jugador_actual].to_string()
		end
		
	end
end