package civitas;

import java.util.ArrayList;

public class Sorpresa{
  
  private String texto;
  private int valor;
  
  //Atributos de referencia
  private MazoSorpresas mazo;
  private TipoSorpresa tipo;
  private Tablero tablero;
  
  
  private void init(){
		mazo = null;
		tablero = null;
		valor = -1;
  }
  
  Sorpresa(TipoSorpresa tipo, Tablero tablero, int valor, String texto){ //Envia a otra casilla
		init();

		this.tipo = tipo;
		this.tablero = tablero;
		this.texto = texto;
		this.valor = valor;
  }
  
  Sorpresa(TipoSorpresa tipo, Tablero tablero){ //Envia carcel
		this(tipo, tablero, -1, null);
  }
  
  Sorpresa(TipoSorpresa tipo, int valor, String texto){ //Resto de sorpresas
		this(tipo, null, valor, texto);
  }
  
  Sorpresa(TipoSorpresa tipo, MazoSorpresas mazo){ //Evitar carcel
		this(tipo, null, -1, null);
		this.mazo = mazo;
  }
  
  public boolean jugadorCorrecto(int actual, ArrayList<Jugador> todos){
		return (actual >= 0 && actual < todos.size());
  }
  
  private void informe(int actual, ArrayList<Jugador> todos){
		Diario.getInstance().ocurreEvento(todos.get(actual).getNombre() + " ha activado una sorpresa. ");
  }
  
  void aplicarAJugador(int actual, ArrayList<Jugador> todos){
		switch(tipo){         
			case IRCARCEL:
				aplicarAJugador_irCarcel(actual,todos);
            
			case IRCASILLA:
        aplicarAJugador_irACasilla(actual, todos);
            
			case PAGARCOBRAR:
        aplicarAJugador_pagarCobrar(actual, todos);
            
			case PORCASAHOTEL:
        aplicarAJugador_porCasaHotel(actual, todos);
            
			case PORJUGADOR:
        aplicarAJugador_porJugador(actual, todos);
		
			case SALIRCARCEL:
        aplicarAJugador_salirCarcel(actual, todos);	
		}	
  }
  
  private void aplicarAJugador_irCarcel(int actual, ArrayList<Jugador> todos){
		if(jugadorCorrecto(actual, todos)){
			informe(actual, todos);
			todos.get(actual).encarcelar(tablero.getCarcel());
		}
  }
  
  private void aplicarAJugador_irACasilla(int actual, ArrayList<Jugador> todos){
		if(jugadorCorrecto(actual, todos)){
			informe(actual, todos);
	  
			int casillaActual = todos.get(actual).getNumCasillaActual();
			int tirada = tablero.calcularTirada(casillaActual, valor);
			int nuevaPos = tablero.nuevaPosicion(casillaActual, tirada);
	  
			todos.get(actual).moverACasilla(nuevaPos);
	  
			tablero.getCasilla(nuevaPos).recibeJugador(actual, todos);
		}
  }
  
  private void aplicarAJugador_pagarCobrar(int actual, ArrayList<Jugador> todos){
		if(jugadorCorrecto(actual, todos)){
			informe(actual, todos);
			todos.get(actual).modificarSaldo(valor);
		}
  }
  
  private void aplicarAJugador_porCasaHotel(int actual, ArrayList<Jugador> todos){
		if(jugadorCorrecto(actual, todos)){
			informe(actual, todos);
			todos.get(actual).modificarSaldo(valor * todos.get(actual).cantidadCasasHoteles());
		}
  }
  
  private void aplicarAJugador_porJugador(int actual, ArrayList<Jugador> todos){
		if(jugadorCorrecto(actual, todos)){
			informe(actual, todos);
		
			Sorpresa pagar = new Sorpresa(TipoSorpresa.PAGARCOBRAR, -1 * valor, "PAGAR");
			Sorpresa cobrar = new Sorpresa(TipoSorpresa.PAGARCOBRAR, (todos.size() - 1) * valor, "COBRAR");
		
			for(int i = 0; i < todos.size(); i++)
				if(todos.get(i) != todos.get(actual))
					pagar.aplicarAJugador_pagarCobrar(i, todos);
		
			cobrar.aplicarAJugador_pagarCobrar(actual, todos);
		}
  }
  
  private void aplicarAJugador_salirCarcel(int actual, ArrayList<Jugador> todos){
		if(jugadorCorrecto(actual, todos)){
			informe(actual, todos);
	  
			boolean haySalvoConducto = false;
	  
			for(int i = 0; i < todos.size() && !haySalvoConducto; i++)
				if(todos.get(i).tieneSalvoconducto())
					haySalvoConducto = true;
	  
			if(!haySalvoConducto){
				todos.get(actual).obtenerSalvoconducto(this);
				salirDelMazo();
			}
		}
  }
  
  void salirDelMazo(){
		if(tipo == TipoSorpresa.SALIRCARCEL)
			mazo.inhabilitarCartaEspecial(this);
  }
  
  @Override
  public String toString(){
		return "Sorpresa: " + tipo + "\n"; 
  }
  
  void usada(){
		if(tipo == TipoSorpresa.SALIRCARCEL)
			mazo.habilitarCartaEspecial(this);
  }
  
 
}
