# encoding:utf-8

require_relative 'jugador.rb'

module Civitas
	class Jugador_especulador < Jugador
		
		@@FACTOR_ESPECULADOR = 2
		
		def initialize(otro, fianza)
			super(otro.encarcelado(), otro.nombre(), otro.num_casilla_actual(), otro.puede_comprar(), 
				otro.saldo, otro.propiedades(), otro.salvoconducto())
			
			@fianza = fianza
			
			for i in(0 ... propiedades.size())
				propiedades[i].actualiza_propietario_por_conversion(self)
			end
			
		end
		
		def casas_max()
			return @@CASAS_MAX * @@FACTOR_ESPECULADOR
		end
		
		def hoteles_max()
			return @@HOTELES_MAX * @FACTOR_ESPECULADOR
		end
		
		def paga_impuesto(cantidad)
			return super(cantidad / @@FACTOR_ESPECULADOR)
		end
		
		def debe_ser_encarcelado()
			es_encarcelado = super
			
			if(es_encarcelado)
				if(@fianza <= saldo())
					es_encarcelado = false
					modificar_saldo(@fianza * -1)
					Diario.instance.ocurre_evento("El jugador #{nombre()} se libra de la carcel mediante fianza")
				end
			end
			
			return es_encarcelado
		end
		
		def to_string()
			info = "\nJugador Especulador:\n"
			info += super
		
			return info
		end
		
		
	end
end
