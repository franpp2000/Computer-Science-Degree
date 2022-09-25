# encoding:utf-8

require_relative "casilla"
require_relative "tablero"
require_relative "dado"
require_relative "mazo_sorpresas"
require_relative 'diario'
require_relative 'tipo_sorpresa'
require_relative 'tipo_casilla'
require_relative 'estados_juego'

module Civitas
	class TestP1
		def main
			for i in (0 ... 100)
				puts Dado.instance.quien_empieza(4)
			end
			puts "..........................\n\n"
	
			Dado.instance.set_debug(true)
			for i in (0 ...20)
				puts Dado.instance.tirar()
			end
			puts "..........................\n\n"
	
	    
			Dado.instance.set_debug(false)
			for i in (0 ... 50)
				puts Dado.instance.tirar()
			end
			puts "..........................\n\n"
	
	
			puts "Ultimo resultado obtenido #{Dado.instance.ultimo_resultado()}"
			puts "..........................\n\n"
	
	
			for i in (0 ... 50)
				puts Dado.instance.salgo_de_la_carcel()
			end
			puts "..........................\n\n"
			
			
			puts Civitas::TipoCasilla::CALLE
			puts Civitas::TipoSorpresa::IRCASILLA
			puts Civitas::EstadosJuego::INICIO_TURNO
			puts "..........................\n\n"
			
			
=begin
			sorpresa1 = Sorpresa.new()
			sorpresa2 = Sorpresa.new()
  
			mazo = MazoSorpresas.new()
			mazo.al_mazo(sorpresa1) 
			mazo.al_mazo(sorpresa2)
  
			mazo.inhabilitar_carta_especial(sorpresa2)
  
			puts Diario.instance.leer_evento + "\n"
  
			mazo.inhabilitar_carta_especial(sorpresa1)
			mazo.habilitar_carta_especial(sorpresa2)	
=end
			puts Diario.instance.leer_evento  
			puts Diario.instance.leer_evento
			puts "..............................\n\n"
			
			
			c1 = Casilla.new("Madrid")
			c2 = Casilla.new("Granada")
			
			tablero = Tablero.new(-1)
			tablero.añade_casilla(c1)
			tablero.añade_juez()
			tablero.añade_casilla(c2)
			puts "..............................\n\n"
			
			
			puts tablero.calcular_tirada(1, 0)
			puts "..............................\n\n"
			
			puts tablero.nueva_posicion(1, 4)
			
		end
		
	end	
	
	principal = TestP1.new()
	principal.main()
	
end

