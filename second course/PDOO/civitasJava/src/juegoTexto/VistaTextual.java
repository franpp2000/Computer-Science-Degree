package juegoTexto;

import civitas.CivitasJuego;
import civitas.Diario;
import civitas.OperacionesJuego;
import civitas.SalidasCarcel;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
import GUI.Respuestas;

class VistaTextual {
  
  CivitasJuego juegoModel; 
  int iGestion=-1;
  int iPropiedad=-1;
  private static String separador = "=====================";
  
  private Scanner in;
  
  VistaTextual () {
    in = new Scanner (System.in);
  }
  
  void mostrarEstado(String estado) {
    System.out.println (estado);
  }
              
  void pausa() {
    System.out.print ("Pulsa una tecla");
    in.nextLine();
  }

  int leeEntero (int max, String msg1, String msg2) {
    Boolean ok;
    String cadena;
    int numero = -1;
    do {
      System.out.print (msg1);
      cadena = in.nextLine();
      try {  
        numero = Integer.parseInt(cadena);
        ok = true;
      } catch (NumberFormatException e) { // No se ha introducido un entero
        System.out.println (msg2);
        ok = false;  
      }
      if (ok && (numero < 0 || numero >= max)) {
        System.out.println (msg2);
        ok = false;
      }
    } while (!ok);

    return numero;
  }

  int menu (String titulo, ArrayList<String> lista) {
    String tab = "  ";
    int opcion;
    System.out.println (titulo);
    for (int i = 0; i < lista.size(); i++) {
      System.out.println (tab+i+"-"+lista.get(i));
    }

    opcion = leeEntero(lista.size(),
                          "\n"+tab+"Elige una opción: ",
                          tab+"Valor erróneo");
    return opcion;
  }

  SalidasCarcel salirCarcel() {
    int opcion = menu ("Elige la forma para intentar salir de la carcel",
      new ArrayList<> (Arrays.asList("Pagando","Tirando el dado")));
    return (SalidasCarcel.values()[opcion]);
  }

  Respuestas comprar(){
		String titulo = "Quiere comprar la calle?";
		ArrayList<String> lista = new ArrayList<>();
		lista.add("SI");
		lista.add("NO");
		
		if(menu(titulo,lista) == 0)
			return Respuestas.SI;
		else
			return Respuestas.NO;
	}

  void gestionar(){
		String titulo = "Gestion";
		ArrayList<String> listaGestiones = new ArrayList<>();
		ArrayList<String> listaProp = new ArrayList<>();
		
		listaGestiones.add("Vender");
    listaGestiones.add("Hipotecar");
    listaGestiones.add("Cancelar Hipoteca");      
    listaGestiones.add("Construir Casa");
    listaGestiones.add("Construir Hotel");
    listaGestiones.add("Terminar");
		
		iGestion = menu(titulo, listaGestiones);
		
		for(int i = 0; i < juegoModel.getJugadorActual().getPropiedades().size();i++)
			listaProp.add(juegoModel.getJugadorActual().getPropiedades().get(i).getNombre());
		
		if(!juegoModel.getJugadorActual().getPropiedades().isEmpty() && listaGestiones.get(iGestion) != "Terminar")
			iPropiedad = menu("Propiedad:", listaProp);
		else if(listaGestiones.get(iGestion) != "Terminar")
			System.out.println("\n No posee ninguna propiedad");
	}
  
  public int getGestion(){
		return iGestion;
	}
  
  public int getPropiedad(){
		return iPropiedad;
	}
    

  void mostrarSiguienteOperacion(OperacionesJuego operacion){
		System.out.println("Siguiente operacion a realizar: " + operacion);
	}


  void mostrarEventos(){
		while(Diario.getInstance().eventosPendientes())
			System.out.println(Diario.getInstance().leerEvento());
	}
  
  public void setCivitasJuego(CivitasJuego civitas){ 
        juegoModel=civitas;
        //this.actualizarVista();
	}
  
  void actualizarVista(){
		System.out.println("----ESTADO JUGADOR----");
		System.out.println(juegoModel.getJugadorActual().toString());
		System.out.println("----ESTADO CASILLA----");
		System.out.println(juegoModel.getCasillaActual().toString());
	} 
}