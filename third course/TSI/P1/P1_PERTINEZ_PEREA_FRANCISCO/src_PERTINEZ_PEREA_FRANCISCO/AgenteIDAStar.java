package tracks.singlePlayer.evaluacion.src_PERTINEZ_PEREA_FRANCISCO;

import java.util.ArrayList;
import java.util.PriorityQueue;

import core.game.Observation;
import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types;
import ontology.Types.ACTIONS;
import tools.ElapsedCpuTimer;
import tools.Vector2d;

public class AgenteIDAStar extends AbstractPlayer {
	Vector2d fescala;
	Vector2d portal;
	ArrayList<ACTIONS> plan;
	ArrayList<Observation> grid[][];
	ArrayList<NodoIDAStar> ruta;
	int nodos_expandidos = 0;
	int nodos_en_memoria = 0;
	
	public AgenteIDAStar(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		grid = stateObs.getObservationGrid();
		plan = new ArrayList<>();
		ruta = new ArrayList<>();
		
		//Calculamos el factor de escala entre mundos (pixeles -> grid)
        fescala = new Vector2d(stateObs.getWorldDimension().width / stateObs.getObservationGrid().length , 
        		stateObs.getWorldDimension().height / stateObs.getObservationGrid()[0].length);
        
      //Se crea una lista de observaciones de portales, ordenada por cercania al avatar
        ArrayList<Observation>[] posiciones = stateObs.getPortalsPositions(stateObs.getAvatarPosition());
        
        //Seleccionamos el portal mas proximo
        portal = posiciones[0].get(0).position;
        portal.x = Math.floor(portal.x / fescala.x);
        portal.y = Math.floor(portal.y / fescala.y);
	}
	
	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		ACTIONS accion = Types.ACTIONS.ACTION_NIL;
		
		//Posicion del avatar
        Vector2d avatar =  new Vector2d(stateObs.getAvatarPosition().x / fescala.x, 
        		stateObs.getAvatarPosition().y / fescala.y);
        
        if(plan.size() == 0) {
        	NodoIDAStar inicial = new NodoIDAStar(avatar.copy(), portal.copy());
        	inicial.actualizar_coste_camino();
        	inicial.actualizar_heuristica();
        	NodoIDAStar objetivo = new NodoIDAStar(portal.copy(), portal.copy());
        	inicial.actualizar_coste_camino();
        	inicial.actualizar_heuristica();
        	
        	long tInicio = System.nanoTime();
        	plan = IDAStar(inicial, objetivo);
        	long tFin = System.nanoTime();
        	double tiempoTotalEnMiliSegundos = (tFin - tInicio)/1000000.0f;

        	System.out.println("Runtime: " + tiempoTotalEnMiliSegundos + " ms");
        	System.out.println("Tamaño de la ruta: " + (plan.size() + 1));
        	System.out.println("Número de nodos expandidos: " + nodos_expandidos);
        	System.out.println("Máximo número de nodos en memoria: " + nodos_en_memoria);
        }
        else {
        	accion = plan.get(0);
        	plan.remove(0);
        }
        
        return accion;
	}
	
	public ArrayList<ACTIONS> IDAStar(NodoIDAStar inicial, NodoIDAStar objetivo) {
		ArrayList<ACTIONS> result = new ArrayList<>();
		
		String t;
		
		int cota = (int)inicial.distancia_objetivo;
		
		ruta.add(inicial);
		nodos_en_memoria = ruta.size();
		
		while(true) {
			t = search(0, cota, objetivo);
			
			if(t == "ENCONTRADO") {
				result = ruta.get(ruta.size() - 1).acciones;
				return result;
			}
			if(t == "INFINITO") {
				return result;
			}
			
			cota = Integer.parseInt(t);
		}
		
	}
	
	public String search(int g, int cota, NodoIDAStar objetivo) {
		NodoIDAStar u = ruta.get(ruta.size() - 1);
		
		int f = g + (int)u.distancia_objetivo;
		
		if(f > cota) {
			return Integer.toString(f);
		}
		
		if(u.posicion.x == objetivo.posicion.x && u.posicion.y == objetivo.posicion.y) {
			return "ENCONTRADO";
		}
		nodos_expandidos++;
		
		int min = 9999999;
		
		PriorityQueue<NodoIDAStar> sucesores = new PriorityQueue<>();
		
		if(grid[(int) (u.posicion.x)][(int) (u.posicion.y - 1)].isEmpty() 
				|| (u.posicion.x == objetivo.posicion.x && u.posicion.y - 1 == objetivo.posicion.y)) {
			
			NodoIDAStar hijoArriba = new NodoIDAStar(u.posicion.copy(), objetivo.posicion.copy());
			hijoArriba.padre = u;
			hijoArriba.acciones = (ArrayList<ACTIONS>) (u.acciones.clone());
			hijoArriba.posicion.y--;
			hijoArriba.acciones.add(Types.ACTIONS.ACTION_UP);
			hijoArriba.actualizar_coste_camino();
			hijoArriba.actualizar_heuristica();
			sucesores.add(hijoArriba);
		}
    
		if(grid[(int) (u.posicion.x)][(int) (u.posicion.y + 1)].isEmpty() 
				|| (u.posicion.x == objetivo.posicion.x && u.posicion.y + 1 == objetivo.posicion.y)) {
			NodoIDAStar hijoAbajo = new NodoIDAStar(u.posicion.copy(), objetivo.posicion.copy());
			hijoAbajo.padre = u;
			hijoAbajo.acciones = (ArrayList<ACTIONS>) (u.acciones.clone());
			hijoAbajo.posicion.y++;
			hijoAbajo.acciones.add(Types.ACTIONS.ACTION_DOWN);
			hijoAbajo.actualizar_coste_camino();
			hijoAbajo.actualizar_heuristica();
			sucesores.add(hijoAbajo);
		} 
    		
		
		if(grid[(int) (u.posicion.x - 1)][(int) (u.posicion.y)].isEmpty() 
				|| (u.posicion.x - 1 == objetivo.posicion.x && u.posicion.y == objetivo.posicion.y)) {
			NodoIDAStar hijoIzquierda = new NodoIDAStar(u.posicion.copy(), objetivo.posicion.copy());
			hijoIzquierda.padre = u;
			hijoIzquierda.acciones = (ArrayList<ACTIONS>) (u.acciones.clone());
			hijoIzquierda.posicion.x--;
			hijoIzquierda.acciones.add(Types.ACTIONS.ACTION_LEFT);
			hijoIzquierda.actualizar_coste_camino();
			hijoIzquierda.actualizar_heuristica();
			sucesores.add(hijoIzquierda);
		} 
		
		if(grid[(int) (u.posicion.x + 1)][(int) (u.posicion.y)].isEmpty() 
				|| (u.posicion.x + 1 == objetivo.posicion.x && u.posicion.y == objetivo.posicion.y)) {
			NodoIDAStar hijoDerecha = new NodoIDAStar(u.posicion.copy(), objetivo.posicion.copy());
			hijoDerecha.padre = u;
			hijoDerecha.acciones = (ArrayList<ACTIONS>) (u.acciones.clone());
			hijoDerecha.posicion.x++;
			hijoDerecha.acciones.add(Types.ACTIONS.ACTION_RIGHT);
			hijoDerecha.actualizar_coste_camino();
			hijoDerecha.actualizar_heuristica();
			sucesores.add(hijoDerecha);
		}
		
		for(NodoIDAStar sucesor:sucesores) {
			if(!ruta.contains(sucesor)) {
				ruta.add(sucesor);
				
				String t = search(g + 1, cota, objetivo);
				
				if(t == "ENCONTRADO") {
					return "ENCONTRADO";
				}
				
				if(Integer.parseInt(t) < min) {
					min = Integer.parseInt(t);
				}
				
				if(nodos_en_memoria < ruta.size()) {
					nodos_en_memoria = ruta.size();
				}
				
				ruta.remove(ruta.size() - 1);
			}
		}
		
		return Integer.toString(min);
	}
}
