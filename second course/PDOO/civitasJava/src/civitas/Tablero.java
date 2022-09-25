
package civitas;

import java.util.ArrayList;

class Tablero{
  
  private int numCasillaCarcel;        
  private int porSalida;    
  private Boolean tieneJuez;    
	
	//Atributos de referencia
	private ArrayList <Casilla> casillas;  

	
  public Tablero(int posCarcel){ //TESTED
    if(posCarcel >= 1)
      numCasillaCarcel = posCarcel;
	
    else
      numCasillaCarcel = 1;
       
    casillas = new ArrayList<>();
    casillas.add(new Casilla("Salida"));
        
    porSalida = 0;
        
	  tieneJuez = false;
  }
    
	private Boolean correcto(){ //TESTED
    return (casillas.size() > numCasillaCarcel && tieneJuez);
  }

  private Boolean correcto(int numCasilla){ //TESTED
    Boolean indiceValido = (numCasilla >= 0 && numCasilla < casillas.size());
        
    return(correcto() && indiceValido);
  }

  int getCarcel(){ //TESTED
    return numCasillaCarcel;
  }
    
  int getPorSalida(){ //TESTED
	  int vecesPorSalida = porSalida;
	
	  if(porSalida > 0)
			--porSalida;
		  
    return vecesPorSalida; 
  }
    
  void añadeCasilla(Casilla casilla){ //TESTED
    if(casillas.size() == numCasillaCarcel)//Precomprobacion
      casillas.add(new Casilla("Carcel"));
        
    casillas.add(casilla);
        
    if(casillas.size() == numCasillaCarcel)//Poscomprobacion
      casillas.add(new Casilla("Carcel"));
  }
    
  void añadeJuez(){ //TESTED
    if(!tieneJuez){
      añadeCasilla(new Casilla(numCasillaCarcel, "Juez"));
			tieneJuez = true;
    }   
  }
    
	public int getTamTablero(){ //TESTED
	  return casillas.size();
	}
	
  public Casilla getCasilla(int numCasilla){ //TESTED
    return correcto(numCasilla)? casillas.get(numCasilla) : null;
  }
    
  int nuevaPosicion(int actual, int tirada){
	  int nuevaPosActual = -1;//preinicializacion a tablero no correcto
	
	  if(correcto()){//Comprobamos si el tablero es correcto
									//Calculamos nueva posicion
			nuevaPosActual = (actual + tirada) % casillas.size();
			
			if(actual + tirada != nuevaPosActual)//Paso por salida?
		  ++porSalida;
	  }
	
	  return nuevaPosActual;
	}
	
	int calcularTirada(int origen, int destino){ //TESTED
	  int tirada = destino - origen;
		
	  if(tirada < 0)//Ajuste por si paso por salida
			tirada += casillas.size();
		
	  return tirada;
	}
    
	public static void main(String [] args){
		
		Tablero t = new Tablero(3);
		
		System.out.println("FIN");
		System.out.println("FIN");
	}
}
