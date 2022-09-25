#encoding:utf-8
require_relative 'operaciones_juego'
require_relative 'respuestas'
require_relative 'salidas_carcel'
require_relative 'gestiones_inmobiliarias'
require_relative 'diario'
require_relative 'civitas_juego'
require 'io/console'

module Civitas

  class Vista_textual
		
		def initialize
			@iGestion = -1
			@iPropiedad = -1
		end

    def mostrar_estado(estado)
      puts estado
    end

    
    def pausa
      print "Pulsa una tecla"
      STDIN.getch
      print "\n"
    end

    def lee_entero(max,msg1,msg2)
      ok = false
      begin
        print msg1
        cadena = gets.chomp
        begin
          if (cadena =~ /\A\d+\Z/)
            numero = cadena.to_i
            ok = true
          else
            raise IOError
          end
        rescue IOError
          puts msg2
        end
        if (ok)
          if (numero >= max)
            ok = false
          end
        end
      end while (!ok)

      return numero
    end



    def menu(titulo,lista)
      tab = "  "
      puts titulo
      index = 0
      lista.each { |l|
        puts tab+index.to_s+"-"+l
        index += 1
      }

      opcion = lee_entero(lista.length,
                          "\n"+tab+"Elige una opción: ",
                          tab+"Valor erróneo")
      return opcion
    end
    
    def comprar
			lista_respuestas = [Respuestas::SI, Respuestas::NO]
      opcion = menu("Quiere comprar la calle?", ["SI", "NO"])
      return lista_respuestas[opcion]
    end

    def gestionar			
			titulo = "Gestion"

			lista_gestiones_inmobiliarias = [Gestiones_inmobiliarias::VENDER, 
																			Gestiones_inmobiliarias::HIPOTECAR, 
																			Gestiones_inmobiliarias::CANCELAR_HIPOTECA, 
																			Gestiones_inmobiliarias::CONSTRUIR_CASA, 
																			Gestiones_inmobiliarias::CONSTRUIR_HOTEL,
																			Gestiones_inmobiliarias::TERMINAR]
																	
			opcion = menu(titulo, ["Vender", "Hipotecar","Cancelar hipoteca",
														"Construir casa","Construir hotel", "Terminar"])
			
			@iGestion = opcion
			
			lista_prop = Array.new()
			
			for i in (0 ... @juego.jugador_actual.propiedades.size())
				lista_prop << @juego.jugador_actual.propiedades[i].nombre()	
			end
			
			if(!@juego.jugador_actual.propiedades.empty? && lista_gestiones_inmobiliarias[@iGestion] != Gestiones_inmobiliarias::TERMINAR)
				@iPropiedad = menu("Propiedades:" , lista_prop)
			elsif(lista_gestiones_inmobiliarias[@iGestion] != Gestiones_inmobiliarias::TERMINAR)	
				puts "\n No posee ninguna propiedad"
			end
			
    end

    def gestion()
			return @iGestion
    end

    def propiedad()
			return @iPropiedad
    end

    def mostrar_siguiente_operacion(operacion)
			puts "Siguiente operacion a realizar: #{operacion}"
    end

    def mostrar_eventos
			while(Diario.instance.eventos_pendientes)
        puts Diario.instance.leer_evento
      end
    end

    def set_civitas_juego(civitas)
         @juego=civitas
         #actualizar_vista()
    end

    def actualizar_vista()
			puts "----ESTADO JUGADOR----"
      puts @juego.jugador_actual.to_string()
      puts "----ESTADO CASILLA----"
      puts @juego.casilla_actual.to_string()
    end
		
		def salir_carcel
      lista_salidas_carcel = [Salidas_carcel::PAGANDO, Salidas_carcel::TIRANDO]
      opcion = menu("Elige la forma para intentar salir de la cárcel", ["Pagando", "Tirando el dado"])
      return lista_salidas_carcel[opcion]
    end
    
  end

end
