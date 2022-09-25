# encoding:utf-8

require_relative 'jugador'
require_relative 'titulo_propiedad'
require_relative 'tipo_casilla'
require_relative 'sorpresa'

module Civitas
	class Casilla
		
		private_class_method :new
		
		attr_reader :nombre, :titulo_propiedad
		
		@@carcel = -1
		
		
		def initialize(importe, nombre, tipo, titulo_propiedad, sorpresa, mazo)
			@importe = importe
			@nombre = nombre
			@tipo = tipo
			@titulo_propiedad = titulo_propiedad
			@sorpresa = sorpresa
			@mazo = mazo
		end
		
		def self.new_por_nombre(nombre)
			
			case nombre
			when "Salida"
				tipo_casilla = Tipo_casilla::DESCANSO
				
			when "Parking"
				tipo_casilla = Tipo_casilla::DESCANSO
				
			when "Carcel" 
				tipo_casilla = Tipo_casilla::DESCANSO
			end
			
			
			new(0.0, nombre, tipo_casilla, nil, nil,nil)
		end
		
		def self.new_por_titulo_propiedad(titulo_propiedad)
			new(0.0, titulo_propiedad.nombre(), Tipo_casilla::CALLE, titulo_propiedad, nil, nil)
		end 
		
		def self.new_por_impuesto(cantidad, nombre)
			new(cantidad, nombre, Tipo_casilla::IMPUESTO, nil, nil, nil)
		end
		
		def self.new_por_juez(num_casilla_carcel, nombre)
			@@carcel = num_casilla_carcel
			new(0.0, nombre, Tipo_casilla::JUEZ, nil, nil, nil)
		end
		
		def self.new_por_mazo(mazo, nombre)
			new(0.0, nombre, Tipo_casilla::SORPRESA, nil, nil, mazo)
		end
		
		def recibe_jugador(iactual, todos)
			
			case @tipo
        when Tipo_casilla::CALLE
          recibe_jugador_calle(iactual,todos)
        when Tipo_casilla::IMPUESTO
          recibe_jugador_impuesto(iactual,todos)
        when Tipo_casilla::JUEZ
          recibe_jugador_juez(iactual,todos)
        when Tipo_casilla::SORPRESA
          recibe_jugador_sorpresa(iactual,todos)
        else
					informe(iactual,todos)
      end
		end
		
		private
		
		def informe(iactual, todos)
			Diario.instance.ocurre_evento("El jugador " + todos[iactual].nombre() + "ha caido en \n" + to_string())
		end
		
		def recibe_jugador_impuesto(iactual, todos)
			if(jugador_correcto(iactual, todos))
				informe(iactual, todos)
				todos[iactual].paga_impuesto(@importe)
			end
		end
		
		def recibe_jugador_juez(iactual, todos)
			if(jugador_correcto(iactual, todos))
				informe(iactual, todos)
				todos[iactual].encarcelar(@@carcel)
			end
		end	
		
		def recibe_jugador_calle(iactual, todos)
			if(jugador_correcto(iactual, todos))
				informe(iactual, todos)
				
				jugador = todos[iactual]
				
				if(!@titulo_propiedad.tiene_propietario())
					jugador.puede_comprar_casilla()
				else
					@titulo_propiedad.tramitar_alquiler(jugador)
					
				end
			end
		end
		
		def recibe_jugador_sorpresa(iactual, todos)
			if(jugador_correcto(iactual,todos))
				informe(iactual, todos)
				@sorpresa = @mazo.siguiente()
				@sorpresa.aplicar_a_jugador(iactual, todos)
			end
		end
		

		public
		
		def to_string()
			return "Casilla : #{@nombre}
							\n\timporte: #{@importe}
              \n\ttipo: #{@tipo}
              \n\tTitulo de propiedad: #{@titulo_propiedad}"
		end
		
		def jugador_correcto(iactual, todos)
			return (iactual >= 0 && iactual < todos.size())
		end
		
	end
	
end