# encoding:utf-8

require_relative 'casilla'
require_relative 'tablero'
require_relative 'dado'
require_relative 'mazo_sorpresas'
require_relative 'diario'
require_relative 'tipo_sorpresa'
require_relative 'tipo_casilla'
require_relative 'estados_juego'
require_relative 'jugador'
require_relative 'sorpresa'
require_relative 'civitas_juego'
require_relative 'gestor_estados'

module Civitas
	
	class MainTest
		
		def main_casilla
			
			mazo = MazoSorpresas.new(false)
			casilla = Casilla.new_por_mazo(mazo, "Sorpresa")
			
			puts casilla.to_string()
			
		end
		
		def main_sorpresas
			
			j = Jugador.new_por_nombre("Pepe")
			jugadores = Array.new()
			jugadores << j
			jugadores << Jugador.new_por_nombre("Jose")
			jugadores << Jugador.new_por_nombre("Miguel")
			
			t = Tablero.new(1)
			
			valor = 50
			
			mazo = MazoSorpresas.new(false)
			s = Sorpresa.new_por_valor(Civitas::TipoSorpresa::PORCASAHOTEL, valor, "porCasaHotel")
			
			mazo.al_mazo(s)
			
			s.aplicar_a_jugador(0, jugadores)
				
			while(Diario.instance.eventos_pendientes)
				puts Diario.instance.leer_evento()
			end
			
			puts j.saldo
			
			puts s.inspect()
		end
		
		def main_civitas_juego
			
			n_jugadores = Array.new()
			
			n_jugadores.push("Juan")
			n_jugadores.push("Cr7")
			n_jugadores.push("Faraque")
			n_jugadores.push("Panita")
			
			juego = CivitasJuego.new(n_jugadores)
			
			puts juego.siguiente_paso_completado(Civitas::Operaciones_juego::AVANZAR)
		end
		
	end	
	
	principal = MainTest.new()
	principal.main_civitas_juego()
	
end