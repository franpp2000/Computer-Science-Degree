package civitas;

import GUI.Dado;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Random;


public class CivitasJuego {
  
  private int indiceJugadorActual;
  
  //Atributos de referencia
  private ArrayList<Jugador> jugadores;
  private MazoSorpresas mazo;
  private Tablero tablero;
  private GestorEstados gestorEstados;
  private EstadosJuego estado;
  
  
  public CivitasJuego(ArrayList<String> nombres){
		jugadores = new ArrayList<>();
	
		for(String name: nombres)
			jugadores.add(new Jugador(name));
	
		gestorEstados = new GestorEstados();
		estado = gestorEstados.estadoInicial();
	
		indiceJugadorActual = Dado.getInstance().quienEmpieza(jugadores.size());
	
		mazo = new MazoSorpresas();
	
		inicializaTablero(mazo);
		inicializarMazoSorpresas(tablero);
	
  }
  
  private void inicializaTablero(MazoSorpresas mazo){
	
		int posCarcel = 5;
		tablero = new Tablero(posCarcel);
		
		int numCalles = 12;
		for(int i = 0; i < numCalles; i++)
    {
      TituloPropiedad prop = new TituloPropiedad("Calle " + i, 100 * i, 3, 50 * i, 500+100*i, 200);
      Casilla casillaCalle = new Casilla(prop);
      tablero.añadeCasilla(casillaCalle); 
    }
	
		int numSorpresas = 3;
		for(int i = 0; i < numSorpresas; i++)
		{
			Casilla casillaSorpresa = new Casilla(mazo,"Casilla Sorpresa");
			tablero.añadeCasilla(casillaSorpresa);
		}
	
		tablero.añadeJuez();
		
		tablero.añadeCasilla(new Casilla(100f,"Impuesto"));
	
		tablero.añadeCasilla(new Casilla("Parking"));
	
  }
  
  
  private void inicializarMazoSorpresas(Tablero tablero){
		Random ram = new Random();
    
		for(TipoSorpresa tipo:TipoSorpresa.values()){
      switch(tipo){
        case IRCARCEL:
          mazo.alMazo(new Sorpresa(tipo,tablero));   
            break;
        case IRCASILLA:
          mazo.alMazo(new Sorpresa(tipo,tablero,ram.nextInt(tablero.getTamTablero()),tipo.toString()));
            break;
        case SALIRCARCEL:
          mazo.alMazo(new Sorpresa(tipo,mazo));
            break;
        default:
          mazo.alMazo(new Sorpresa(tipo,ram.nextInt(400)+100,tipo.toString()));
			}
    }
  }
  
  private void contabilizarPasosPorSalida(Jugador jugadorActual){
		while(tablero.getPorSalida() > 0)
			jugadorActual.pasaPorSalida();
	}
  
  private void pasarTurno(){
		indiceJugadorActual = (indiceJugadorActual + 1) % jugadores.size();
  }
  
  public void siguientePasoCompletado(OperacionesJuego operacion){
		estado = gestorEstados.siguienteEstado(jugadores.get(indiceJugadorActual),estado,operacion);
  }
  
  public OperacionesJuego siguientePaso(){
		Jugador jugadorActual = jugadores.get(indiceJugadorActual);
	
		OperacionesJuego operacion = gestorEstados.operacionesPermitidas(jugadorActual, estado);
	
		if(operacion == OperacionesJuego.PASAR_TURNO)
			pasarTurno();
		else if(operacion == OperacionesJuego.AVANZAR)
			avanzaJugador();
	
		siguientePasoCompletado(operacion);
	
		return operacion;
  }
  
  private void avanzaJugador(){
	
		Jugador jugadorActual = jugadores.get(indiceJugadorActual);
		int posicionActual = jugadorActual.getNumCasillaActual();
	
		int tirada = Dado.getInstance().tirar();
		int posicionNueva = tablero.nuevaPosicion(posicionActual, tirada);
		Casilla casilla = tablero.getCasilla(posicionNueva);
	
		contabilizarPasosPorSalida(jugadorActual);
		jugadorActual.moverACasilla(posicionNueva);
		casilla.recibeJugador(indiceJugadorActual, jugadores);
		contabilizarPasosPorSalida(jugadorActual);
  }
  
  public boolean comprar(){
		boolean res;
		Jugador jugadorActual = jugadores.get(indiceJugadorActual);
		int numCasillaActual = jugadorActual.getNumCasillaActual();
		Casilla casilla = tablero.getCasilla(numCasillaActual);
		TituloPropiedad titulo = casilla.getTituloPropiedad();
		
		res = jugadorActual.comprar(titulo);
		
		return res;
  }
  
  
  public boolean construirCasa(int ip){
		return jugadores.get(indiceJugadorActual).construirCasa(ip);
  }
  
  public boolean construirHotel(int ip){
		return jugadores.get(indiceJugadorActual).construirHotel(ip);
  }
  
  public boolean vender(int ip){
		return jugadores.get(indiceJugadorActual).vender(ip);
  }
  
  public boolean hipotecar(int ip){
		return jugadores.get(indiceJugadorActual).hipotecar(ip);
  }
  
  public boolean cancelarHipoteca(int ip){
		return jugadores.get(indiceJugadorActual).cancelarHipoteca(ip);
  }
  
  public boolean salirCarcelPagando(){
		return jugadores.get(indiceJugadorActual).salirCarcelPagando();
  }
  
  public boolean salirCarcelTirando(){
		return jugadores.get(indiceJugadorActual).salirCarcelTirando();
  }
  
  public boolean finalDelJuego(){
		boolean jugadorEnBancarrota = false;
    
		for(int i = 0; i < jugadores.size() ; i++)
			if(jugadores.get(i).enBancarrota())
				jugadorEnBancarrota = true;
           
    return jugadorEnBancarrota;
  }
	
  //VISIBILIDAD CAMBIADA PARA PODER USARLO EN EL OTRO MODULO
  public ArrayList<Jugador> ranking(){
		Collections.sort(jugadores);
      
		return jugadores;
  }
  
  public Casilla getCasillaActual(){
		return tablero.getCasilla(jugadores.get(indiceJugadorActual).getNumCasillaActual());
  }
  
  public Jugador getJugadorActual(){
		return jugadores.get(indiceJugadorActual);
  }
  
  public String infoJugadorTexto(){
		return jugadores.get(indiceJugadorActual).toString();
  }
  
  
}
