package GUI;

import civitas.CivitasJuego;
import civitas.OperacionesJuego;
import civitas.OperacionInmobiliaria;
import civitas.GestionesInmobiliarias;
import civitas.SalidasCarcel;
import java.util.ArrayList;
import civitas.Jugador;

class Controlador {
	
	private CivitasJuego juegoModel;
	private CivitasView vista;

	Controlador(CivitasJuego juegoModel, CivitasView vista) {
		this.juegoModel = juegoModel;
		this.vista = vista;
	}

	/*void juega(){
	
		vista.setCivitasJuego(juegoModel);
		
		while(!juegoModel.finalDelJuego()){
			
			vista.actualizarVista();
			vista.pausa();
			
			OperacionesJuego sigOperacion = juegoModel.siguientePaso();
			vista.mostrarSiguienteOperacion(sigOperacion);
			
			if(sigOperacion != OperacionesJuego.PASAR_TURNO)
				vista.mostrarEventos();
			
			if(!juegoModel.finalDelJuego()){
			
				switch(sigOperacion){
					
					case COMPRAR:
						if(vista.comprar() == Respuestas.SI)
							juegoModel.comprar();
							
						break;
					
					case GESTIONAR:
						
						vista.gestionar();
						OperacionInmobiliaria operacion = new OperacionInmobiliaria(GestionesInmobiliarias.values()[vista.getGestion()], vista.getPropiedad());
						
						switch(operacion.getGestionInmobiliaria())
				    {
							case VENDER:
								juegoModel.vender(operacion.getIndice());
								break;
							case HIPOTECAR:
								juegoModel.hipotecar(operacion.getIndice());
								break;								
							case CANCELAR_HIPOTECA:
								juegoModel.cancelarHipoteca(operacion.getIndice());
								break;
							case CONSTRUIR_CASA:
								juegoModel.construirCasa(operacion.getIndice());
								break;
							case CONSTRUIR_HOTEL:
								juegoModel.construirHotel(operacion.getIndice());									
								break;
							case TERMINAR:                          
								juegoModel.siguientePaso();
						}
						
						break;
						
					case SALIR_CARCEL:
						if(vista.salirCarcel() == SalidasCarcel.PAGANDO)
							juegoModel.salirCarcelPagando();
						else
							juegoModel.salirCarcelTirando();
						
						juegoModel.siguientePaso();
				
				}
			}
		}
		
		ArrayList<Jugador> jugadores = juegoModel.ranking();
		
		System.out.println("Ranking:");
		for(int i = 0; i < jugadores.size(); i++)
			System.out.println(jugadores.get(i).toString());
	}*/
	
}
