#encoding:utf-8
module Civitas
  
  class Operacion_inmobiliaria
    attr_reader :gestion_inm , :indice
    
    def initialize(gestion , num_propiedad)
      @gestion_inm = gestion
      @indice = num_propiedad
    end
    
  end
  
end
