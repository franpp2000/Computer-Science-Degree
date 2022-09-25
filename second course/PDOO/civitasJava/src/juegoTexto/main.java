
package juegoTexto;

import civitas.CivitasJuego;
import GUI.Dado;
import java.util.ArrayList;
import java.util.Scanner;

public class main {
	public static void main(String[] args) {
		
		int n_jugadores;
		Scanner entrada = new Scanner(System.in);
		
		System.out.print("Nº De jugadores: ");
		n_jugadores  = entrada.nextInt();
			
		ArrayList<String> nombresJugadores = new ArrayList<>();
		String j;
		
		for(int i = 0; i < n_jugadores; i++){
			System.out.print("Jugador " + i + ": ");
			j = entrada.next();
			nombresJugadores.add(j);
		}
        
		//Creo juego en modo debug
    CivitasJuego juego = new CivitasJuego(nombresJugadores);
    Dado.getInstance().setDebug(true);
        
    //Jugar
    VistaTextual interfaz = new VistaTextual();
//    Controlador controlador = new Controlador(juego,interfaz);

//		controlador.juega();
	}
	
}
