# encoding:utf-8

require_relative "sorpresa"
require_relative "diario"

module Civitas
	class Mazo_sorpresas
		
		def initialize(d = false)
			init()
			@debug = d
			
			if(@debug)
				Diario.instance.ocurre_evento("Modo debug del mazo: ACTIVADO.")
			end
		end
		
		
		private
		
		def init()
			@sorpresas = Array.new() 
			@cartas_especiales = Array.new() 
			@barajada = false
			@usadas = 0
		end
		
		
		public
		
		def al_mazo(s)
			if(!@barajada)
				@sorpresas << s
			end
		end
		
		def siguiente()
			if(!@barajada || @usadas == @sorpresas.size() + @cartas_especiales.size())
				if(!@debug)
					@sorpresas.shuffle!
					@barajada = true
				end
				@usadas = 0
			end
			
			@usadas += 1
			@ultima_sorpresa = @sorpresas.shift()
			@sorpresas << @ultima_sorpresa
			
			return @ultima_sorpresa
		end
		
		def inhabilitar_carta_especial(sorpresa)
			for i in (0 .. @sorpresas.size() - 1)
        if(@sorpresas[i] == sorpresa)
          aux = @sorpresas[i]
          @sorpresas.delete_at(i)
          @cartas_especiales << aux
          Diario.instance.ocurre_evento("Carta Especial inhabilitada!!")
        end
      end
		end
		
		def habilitar_carta_especial(sorpresa)
    
      for i in (0 .. @cartas_especiales.size() - 1)
        if(@cartas_especiales[i] == sorpresa)
          aux = @cartas_especiales[i]
          @cartas_especiales.delete_at(i)
          @sorpresas << aux
          Diario.instance.ocurre_evento("Carta Especial habilitada!!")
        end
      end
    end
		
		
	end
end
