package civitas;

import java.util.ArrayList;

public class Casilla {
  
  private static int carcel = -1;
  
  private float importe;
  private String nombre;
  
  //Atributos de referencia
  private TipoCasilla tipo;
  private TituloPropiedad tituloPropiedad;
  private Sorpresa sorpresa;
  private MazoSorpresas mazo;
  
  
  private void init(){ //TESTED
		importe = 0f;
		nombre = null;
		tipo = null;
		tituloPropiedad = null;
		sorpresa = null;
		mazo = null;
  }
  
  Casilla(String nombre){ //TESTED
		init();
	
		switch(nombre){
			case "Salida":
				tipo = TipoCasilla.DESCANSO;
				break;
		
			case "Parking":
				tipo = TipoCasilla.DESCANSO;
				break;
		
			case "Carcel":
				tipo = TipoCasilla.DESCANSO;
		}
		this.nombre = nombre;
  }
  
  Casilla(TituloPropiedad titulo){ //TESTED
		init();
		tipo = TipoCasilla.CALLE;
		tituloPropiedad = titulo;
		nombre = titulo.getNombre();
  }
  
  Casilla(float cantidad, String nombre){ //TESTED
		init();
		tipo = TipoCasilla.IMPUESTO;
		this.nombre = nombre;
		importe = cantidad;
  }
  
  Casilla(int numCasillaCarcel, String nombre){ //TESTED
		init();
		tipo = TipoCasilla.JUEZ;
		this.nombre = nombre;
		carcel = numCasillaCarcel;
  }
  
  Casilla(MazoSorpresas mazo, String nombre){ //TESTED
		init();
		tipo = TipoCasilla.SORPRESA;
		this.nombre = nombre;
		this.mazo = mazo;
  }
  
  private void informe(int iactual, ArrayList<Jugador> todos){ //TESTED
		Diario.getInstance().ocurreEvento("El jugador " + todos.get(iactual).getNombre() + " ha caido en:\n" + toString());
  }
  
  private void recibeJugador_impuesto(int iactual, ArrayList<Jugador> todos){ //TESTED
		if(jugadorCorrecto(iactual, todos)){
			informe(iactual, todos);
			todos.get(iactual).pagaImpuesto(importe);
		}
  }
  
  private void recibeJugador_juez(int iactual, ArrayList<Jugador> todos){ //TESTED
		if(jugadorCorrecto(iactual, todos)){
			informe(iactual, todos);
			todos.get(iactual).encarcelar(carcel);
		}
  }
  
  @Override
  public String toString(){ //TESTED
		String info = "Casilla :" + nombre
                + "\n\timporte: " + importe
                + "\n\ttipo:" + tipo
                + "\n\tTitulo de propiedad: " + tituloPropiedad;
        
    return info;
  }
  
  public String getNombre(){ //TESTED
		return nombre;
  }
  
  TituloPropiedad getTituloPropiedad(){ //TESTED
		return tituloPropiedad;
  }
  
  public boolean jugadorCorrecto(int iactual, ArrayList<Jugador> todos){ //TESTED
		return (iactual >= 0 && iactual < todos.size());
  }
  
  private void recibeJugador_calle(int iactual, ArrayList<Jugador> todos){ //TESTED
		if(jugadorCorrecto(iactual, todos)){
			informe(iactual, todos);
	  
			Jugador jugador = todos.get(iactual);
	  
	  if(!tituloPropiedad.tienePropietario())
			jugador.puedeComprarCasilla();
	  else
			tituloPropiedad.tramitarAlquiler(jugador);
	  
		}
  }
  
  void recibeJugador(int iactual, ArrayList<Jugador> todos){ //TESTED
		switch(tipo){
      case CALLE:
        recibeJugador_calle(iactual,todos);
        break;
      case IMPUESTO:
        recibeJugador_impuesto(iactual,todos);
        break;
      case JUEZ:
        recibeJugador_juez(iactual,todos);
        break;
      case SORPRESA:
        recibeJugador_sorpresa(iactual,todos);
        break;
      default:
        informe(iactual,todos);                 
    }
  }
  
  private void recibeJugador_sorpresa(int iactual, ArrayList<Jugador> todos){ //TESTED
		if(jugadorCorrecto(iactual, todos)){
			informe(iactual, todos);
			sorpresa = mazo.siguiente();
			sorpresa.aplicarAJugador(iactual, todos);
		}
  }
  
  ///////////////////////////////////////////
   
  public static void main(String [] args){
		
		
		ArrayList<Jugador> jugadores = new ArrayList<>();
		jugadores.add(new Jugador("Juan"));
		jugadores.add(new Jugador("Paco"));
		
		MazoSorpresas m = new MazoSorpresas();
		Sorpresa s = new Sorpresa(TipoSorpresa.SALIRCARCEL, m);
		m.alMazo(s);
		
		Casilla c = new Casilla(m, "Sorpresa");
		
		c.recibeJugador_sorpresa(1, jugadores);
		
		while(Diario.getInstance().eventosPendientes())
			System.out.println(Diario.getInstance().leerEvento());
		
		System.out.println(jugadores.get(1).toString());

  }
}
