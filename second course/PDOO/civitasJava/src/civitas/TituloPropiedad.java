package civitas;

public class TituloPropiedad{
  
  private static float factorInteresesHipoteca = 1.1f;
  
  private float alquilerBase;
  private float factorRevalorizacion;
  private float hipotecaBase;
  private boolean hipotecado;
  private String nombre;
  private int numCasas;
  private int numHoteles;
  private float precioCompra;
  private float precioEdificar;
  
  //Atributos de referencia
  private Jugador propietario;
  
  
  TituloPropiedad(String nom, float ab, float fr, float hb, float pc, float pe){ //TESTED
		nombre = nom;
		alquilerBase = ab;
		factorRevalorizacion = fr;
		hipotecaBase = hb;
		precioCompra = pc;
		precioEdificar = pe;
		propietario = null;
		numCasas = 0;
		numHoteles = 0;
		hipotecado = false;
  }
  
  @Override
  public String toString(){ //TESTED
    return "\n\t\tnombre: " + nombre + "\n\t\tAlquiler Base: " + alquilerBase
            + "\n\t\tfactor revalorizacion: " + factorRevalorizacion +
            "\n\t\thipoteca base: " + hipotecaBase + "\n\t\thipotecado: " + hipotecado
            + "\n\t\tnºcasas: " + numCasas + "\n\t\tnºhoteles: " + numHoteles +
            "\n\t\tprecio compra: "+ precioCompra +"\n\t\tprecio edificar: "
            + precioEdificar;
  }
  
  private float getPrecioAlquiler(){ //TESTED
		float precioAlquiler = 0; //inicializado al caso de estar hipotecado
                              //o esta el propietario encarcelado
							  
		if(!propietarioEncarcelado() && !hipotecado)
			precioAlquiler = alquilerBase * (1 + (numCasas * 0.5f) + (numHoteles * 2.5f));
		
		return precioAlquiler;
  }
  
  float getImporteCancelarHipoteca(){
		float cantidadRecibida = hipotecaBase * (1 + (numCasas * 0.5f) + (numHoteles * 2.5f));
	
		return cantidadRecibida * factorInteresesHipoteca;
  }
  
  void tramitarAlquiler(Jugador jugador){ //TESTED
		if(tienePropietario() && !esEsteElPropietario(jugador)){
			float alquiler = getPrecioAlquiler();
	  
			jugador.pagaAlquiler(alquiler);
			propietario.recibe(alquiler);
		}
  }
  
  private boolean propietarioEncarcelado(){ //TESTED
		boolean encarcelado = true;
	
		if(!propietario.isEncarcelado() || !tienePropietario())
			encarcelado = false;
	
		return encarcelado;
  }
  
  int cantidadCasasHoteles(){ //TESTED
		return numCasas + numHoteles;
  }
  
  private float getPrecioVenta(){ //TESTED
    return precioCompra + (cantidadCasasHoteles() * precioEdificar) * factorRevalorizacion;
  }
  
  boolean derruirCasas(int n, Jugador jugador){ //TESTED
		boolean casasDerruidas = false;
	
		if(esEsteElPropietario(jugador) && numCasas >= n){
			numCasas -= n;
			casasDerruidas = true;
		}  
	  
		return casasDerruidas;  
  }
  
  boolean vender(Jugador jugador){ //TESTED
	
		boolean vendido = false;
	
		if(esEsteElPropietario(jugador) && !hipotecado){
			jugador.recibe(getPrecioVenta());
			numCasas = 0;
			numHoteles = 0;
			propietario = null;
			vendido = true;
		}  
	
		return vendido;
  }
  
  void actualizaPropietarioPorConversion(Jugador jugador){ //TESTED
		propietario = jugador;
  }
  
  
  boolean hipotecar(Jugador jugador){ //TESTED
		boolean salida = false;
	
		if(!hipotecado && esEsteElPropietario(jugador)){
			jugador.recibe(getImporteHipoteca());
			hipotecado = true;
			salida = true;
		}
	
		return salida;
  }
 
  boolean cancelarHipoteca(Jugador jugador){ //TESTED
		boolean result = false;
	
		if(hipotecado && esEsteElPropietario(jugador)){
			propietario.paga(getImporteCancelarHipoteca());
			hipotecado = false;
			result = true;
		}
	
		return result;
  }
  
  boolean comprar(Jugador jugador){ //TESTED
		boolean result = false;
	
		if(!tienePropietario()){
			propietario = jugador;
			result = true;
			propietario.paga(precioCompra);
		}
	
		return result;
  }
  
  boolean construirCasa(Jugador jugador){ //TESTED???
		boolean result = false;
    
		if(esEsteElPropietario(jugador)){
      result = true;
      numCasas++;
    }
        
		return result;
  }
  
  boolean construirHotel(Jugador jugador){ //TESTED
		boolean result = false;
	
		if(esEsteElPropietario(jugador)){
			jugador.paga(precioEdificar);
			numHoteles++;
			result = true;
		}
	
		return result;
  }
  
  private boolean esEsteElPropietario(Jugador jugador){ //TESTED
		return jugador == propietario;
  }
  
  public boolean getHipotecado(){
		return hipotecado;
  }
  
  private float getImporteHipoteca(){ //TESTED
		return hipotecaBase * (1 + (numCasas * 0.5f) + (numHoteles * 2.5f));
  }
  
	//VISIBILIDAD CAMBIADA PARA PODER USARLO EN EL OTRO MODULO
  public String getNombre(){
		return nombre;
  }
  
  int getNumCasas(){
		return numCasas;
  }
  
  int getNumHoteles(){
		return numHoteles;
  }
  
  float getPrecioCompra(){
		return precioCompra;
  }
  
  float getPrecioEdificar(){
		return precioEdificar;
  }
  
  Jugador getPropietario(){
		return propietario;
  }
  
  boolean tienePropietario(){ //TESTED
		return propietario != null;
  }
	
	public static void main(String [] args){
		TituloPropiedad t = new TituloPropiedad("Calle Madrid", 30.36f, 45.6f, 23.4f, 14.6f, 43.6f);
		
		Jugador j1 = new Jugador("Paco");
		Jugador j2 = new Jugador("Juan");
		
		t.comprar(j1);
		
		t.construirCasa(j1);
		t.construirCasa(j1);
		t.construirCasa(j1);
		t.construirCasa(j1);
		
		t.derruirCasas(3, j1);
		
		while(Diario.getInstance().eventosPendientes())
			System.out.println(Diario.getInstance().leerEvento());
	}
}
