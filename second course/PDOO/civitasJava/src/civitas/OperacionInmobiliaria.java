package civitas;

public class OperacionInmobiliaria {
	GestionesInmobiliarias gestInm;
	int indice;

	OperacionInmobiliaria(){
		indice = 0;
		gestInm = null;
	}
	
	public OperacionInmobiliaria(GestionesInmobiliarias valor, int i){
		gestInm = valor;
		indice = i;
	}
	
	public GestionesInmobiliarias getGestionInmobiliaria(){
    return gestInm;
  }
    
  public int getIndice()
  {
    return indice;
  }

}
