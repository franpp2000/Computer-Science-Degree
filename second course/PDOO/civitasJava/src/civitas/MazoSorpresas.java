package civitas;

import java.util.ArrayList;
import java.util.Collections;

class MazoSorpresas{
    
  private Boolean barajada;   
  private int usadas;   
  private Boolean debug;       
  private Sorpresa ultimaSorpresa;  

  //Atributos de referencia
  private ArrayList <Sorpresa> sorpresas;  
  private ArrayList <Sorpresa> cartasEspeciales;
  
  
  MazoSorpresas(Boolean d){ //TESTED
    init();
		debug = d;
	
		if(debug)
			Diario.getInstance().ocurreEvento("Modo debug del mazo: ACTIVADO.");
	}
  
  MazoSorpresas(){ //TESTED
    init();
		debug = false;
  }
  
  private void init(){
    sorpresas = new ArrayList<>();
		cartasEspeciales = new ArrayList<>();
		barajada = false;
		usadas = 0;
  }
    
  void alMazo(Sorpresa s){ //TESTED
		if(!barajada)
			sorpresas.add(s);
  }
  
  Sorpresa siguiente(){ //TESTED
		if(!barajada || usadas == sorpresas.size() + cartasEspeciales.size()){
			if(!debug){ 
				Collections.shuffle(sorpresas);
				barajada = true;
			}
			
			usadas = 0;
		}
	
		++usadas;
		ultimaSorpresa = sorpresas.remove(0);
		sorpresas.add(ultimaSorpresa);
	
		return ultimaSorpresa;
  } 
  
  void inhabilitarCartaEspecial(Sorpresa sorpresa){ //TESTED
		boolean encontrada = sorpresas.remove(sorpresa);
	
		if(encontrada){
			cartasEspeciales.add(sorpresa);
			Diario.getInstance().ocurreEvento("Carta Especial inhabilitada!!");
		}
  }
  
  void habilitarCartaEspecial(Sorpresa sorpresa){ //TESTED
		boolean encontrada = cartasEspeciales.remove(sorpresa);
	
		if(encontrada){
			sorpresas.add(sorpresa);
			Diario.getInstance().ocurreEvento("Carta Especial habilitada!!");
		}
    
  }
	
	public static void main(String [] args){
		
		MazoSorpresas mazo = new MazoSorpresas(true);
		
		mazo.alMazo(new Sorpresa(TipoSorpresa.IRCASILLA, 0, "IRCASILLA"));
		mazo.alMazo(new Sorpresa(TipoSorpresa.PAGARCOBRAR, 37, "PAGARCOBRAR"));
		mazo.alMazo(new Sorpresa(TipoSorpresa.PORCASAHOTEL,60, "PORCASAHOTEL"));
		mazo.alMazo(new Sorpresa(TipoSorpresa.PORJUGADOR, 50, "PORJUGADOR"));
		
		Sorpresa s;
		
		while(mazo.sorpresas.size() > 0){
			
			s = mazo.siguiente();
			System.out.println(s.toString());
			mazo.inhabilitarCartaEspecial(s);
		}
		
		System.out.println("---------");
		
		while(mazo.cartasEspeciales.size() > 0){
			
			s = mazo.cartasEspeciales.get(0);
			System.out.println(s.toString());
			mazo.habilitarCartaEspecial(s);
		}
		
		System.out.println("---------");
		
		while(Diario.getInstance().eventosPendientes())
			System.out.println(Diario.getInstance().leerEvento());
	}
  
}  
  
  
  
