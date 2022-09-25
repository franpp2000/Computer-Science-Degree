# encoding:utf-8

require_relative 'tipo_sorpresa'
require_relative 'diario'
require_relative 'mazo_sorpresas'
require_relative 'tablero'
require_relative 'jugador'
require_relative 'casilla'

module Civitas
	
	class Sorpresa # TESTED
		
		private_class_method :new
		
		def initialize(tipo, tablero, valor, texto, mazo)
			@texto = texto
			@valor = valor
			@mazo = mazo
			@tipo = tipo
			@tablero = tablero
		end
		
		def self.new_por_tablero(tipo, tablero)
			new(tipo, tablero, -1, nil, nil)
		end
		
		def self.new_por_tablero_valor(tipo, tablero, valor, texto)
			new(tipo, tablero, valor, texto, nil)
		end
		
		def self.new_por_valor(tipo, valor, texto)
			new(tipo, nil, valor, texto, nil)
		end
		
		def self.new_por_mazo(tipo, mazo)
			new(tipo, nil, -1, nil, mazo)
		end
		
		private
		
		def informe(actual, todos)
			Diario.instance.ocurre_evento(todos[actual].nombre() + " ha activado una sorpresa. ")
		end
		
		def aplicar_a_jugador_ir_carcel(actual, todos)
			if(jugador_correcto(actual, todos))
				informe(actual, todos)
				todos[actual].encarcelar(@tablero.num_casilla_carcel())
			end
		end
		
		def aplicar_a_jugador_ir_a_casilla(actual, todos)
			if(jugador_correcto(actual, todos))
				informe(actual, todos)
				
				casilla_actual = todos[actual].num_casilla_actual()
				tirada = @tablero.calcular_tirada(casilla_actual, @valor)
				nueva_pos = @tablero.nueva_posicion(casilla_actual, tirada)
				
				todos[actual].mover_a_casilla(nueva_pos)
				@tablero.casilla(nueva_pos).recibe_jugador(actual, todos)
			end
		end
		
		def aplicar_a_jugador_por_casa_hotel(actual, todos)
			if(jugador_correcto(actual, todos))
				informe(actual, todos)
				todos[actual].modificar_saldo(@valor * todos[actual].cantidad_casas_hoteles())
			end
		end
		
		public
		def aplicar_a_jugador_pagar_cobrar(actual, todos)
			if(jugador_correcto(actual, todos))
				informe(actual, todos)
				todos[actual].modificar_saldo(@valor)
			end
		end
		
		private
		def aplicar_a_jugador_por_jugador(actual, todos)
			if(jugador_correcto(actual, todos))
				informe(actual, todos) 
				
				pagar = Sorpresa.new_por_valor(Tipo_sorpresa::PAGARCOBRAR, -1 * @valor, "PAGAR")
				cobrar = Sorpresa.new_por_valor(Tipo_sorpresa::PAGARCOBRAR, (todos.size() - 1) * @valor, "COBRAR")
				
				for i in (0 ... todos.size())
					if(todos[i] != todos[actual])
						pagar.aplicar_a_jugador_pagar_cobrar(i, todos)
					end
				end
				
				cobrar.aplicar_a_jugador_pagar_cobrar(actual, todos)
				
			end
		end
		
		def aplicar_a_jugador_salir_carcel(actual, todos)
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
		
		
		public
		
		def jugador_correcto(actual, todos)
			return actual >= 0 && actual < todos.size()
		end
		
		def aplicar_a_jugador(actual, todos)
			case @tipo
				when Tipo_sorpresa::IRCARCEL
          aplicar_a_jugador_ir_carcel(actual,todos)
				when Tipo_sorpresa::IRCASILLA
         aplicar_a_jugador_ir_a_casilla(actual, todos)
				when Tipo_sorpresa::SALIRCARCEL
          aplicar_a_jugador_salir_carcel(actual, todos)
				when Tipo_sorpresa::PAGARCOBRAR
          aplicar_a_jugador_pagar_cobrar(actual, todos)
				when Tipo_sorpresa::PORCASAHOTEL
          aplicar_a_jugador_por_casa_hotel(actual, todos)
				when Tipo_sorpresa::PORJUGADOR               
          aplicar_a_jugador_por_jugador(actual,todos)
      end
		end
		
		def salir_del_mazo()
			
			if(@tipo == Tipo_sorpresa::SALIRCARCEL)
				@mazo.inhabilitar_carta_especial(self)
			end
		end
		
		def to_string()
			return "Sorpresa: #{@tipo} 
							texto: #{@texto}\n"
		end
		
		def usada()
			if((@tipo == Tipo_sorpresa::SALIRCARCEL))
				@mazo.habilitar_carta_especial(self)
			end
		end
		
		
	end
end
