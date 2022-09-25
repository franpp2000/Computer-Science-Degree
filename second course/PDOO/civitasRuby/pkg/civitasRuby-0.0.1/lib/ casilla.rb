# encoding:utf-8

require_relative 'jugador'
require_relative 'tipo_casilla'
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
			new(0.0, nombre, Civitas::TipoCasilla::DESCANSO, nil, nil,nil)
		end
		
		def self.new_por_titulo_propiedad(titulo_propiedad)
			new(0.0, titulo_propiedad.nombre(), Civitas::TipoCasilla::CALLE, titulo_propiedad, nil, nil)
		end 
		
		def self.new_por_impuesto(cantidad, nombre)
			new(cantidad, nombre, Civitas::TipoCasilla::IMPUESTO, nil, nil, nil)
		end
		
		def self.new_por_juez(num_casilla_carcel, nombre)
			new(0.0, nombre, Civitas::TipoCasilla::JUEZ, nil, nil, nil)
			@@carcel = num_casilla_carcel
		end
		
		def self.new_por_mazo(mazo, nombre)
			new(0.0, nombre, Civitas::TipoCasilla::SORPRESA, nil, nil, mazo)
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
				todos[iactual].encarcelar(@carcel)
			end
		end
	
	#### PENDIENTES DE IMPLEMENTACION ####	
		
		def recibe_jugador_calle(iactual, todos)
			
		end
		
		def recibe_jugador(iactual, todos)
			
		end
		
		def recibe_jugador_sorpresa(iactual, todos)
			
		end
		
	########################################

		public
		
		def to_string()
			info = "Casilla : #{@nombre} 
											\n\timporte: #{@importe} 
											\n\tMazo: #{@mazo} 
											\n\tSorpresa: #{@sorpresa} 
											\n\ttipo: #{@tipo} 
											\n\tTitulo de propiedad: #{@titulo_propiedad} 
											\n\tCarcel: #{@carcel}"
			
			return info
		end
		
		def jugador_correcto(iactual, todos)
			return (iactual >= 0 && iactual < todos.size())
		end
		
	end
	
	casilla = Casilla.new_por_nombre("CR7")
	
	puts casilla.to_string();
	
end
