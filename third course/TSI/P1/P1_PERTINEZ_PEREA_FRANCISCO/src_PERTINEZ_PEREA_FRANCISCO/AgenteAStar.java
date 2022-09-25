package tracks.singlePlayer.evaluacion.src_PERTINEZ_PEREA_FRANCISCO;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;
import core.game.Observation;
import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types;
import ontology.Types.ACTIONS;
import tools.ElapsedCpuTimer;
import tools.Vector2d;

public class AgenteAStar extends AbstractPlayer {
	Vector2d fescala;
	Vector2d portal;
	ArrayList<ACTIONS> plan;
	int matriz_costes[][];
	ArrayList<Observation> grid[][];
	boolean estaEnCerrados[][];
	boolean estaEnAbiertos[][];
	int nodos_expandidos = 0;
	int nodos_en_memoria = 0;
	
	
	public AgenteAStar(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		grid = stateObs.getObservationGrid();
		plan = new ArrayList<>();
		
		//Calculamos el factor de escala entre mundos (pixeles -> grid)
        fescala = new Vector2d(stateObs.getWorldDimension().width / stateObs.getObservationGrid().length , 
        		stateObs.getWorldDimension().height / stateObs.getObservationGrid()[0].length);
        
        estaEnCerrados = new boolean[(int) (stateObs.getWorldDimension().height / fescala.y)][(int) (stateObs.getWorldDimension().width / fescala.x)];
        estaEnAbiertos = new boolean[(int) (stateObs.getWorldDimension().height / fescala.y)][(int) (stateObs.getWorldDimension().width / fescala.x)];
        matriz_costes = new int[(int) (stateObs.getWorldDimension().height / fescala.y)][(int) (stateObs.getWorldDimension().width / fescala.x)];
        
        for(int i = 0; i < (int) (stateObs.getWorldDimension().height / fescala.y); i++) {
        	for(int j = 0; j < (int) (stateObs.getWorldDimension().width / fescala.x); j++) {
        		matriz_costes[i][j] = 9999999;
        	}
        }
        
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
        	NodoAStar inicial = new NodoAStar(avatar.copy(), portal.copy());
        	inicial.actualizar_coste_camino();
        	inicial.actualizar_heuristica();
        	NodoAStar objetivo = new NodoAStar(portal.copy(), portal.copy());
        	inicial.actualizar_coste_camino();
        	inicial.actualizar_heuristica();
        	
        	long tInicio = System.nanoTime();
        	plan = AStar(inicial, objetivo, stateObs);
        	long tFin = System.nanoTime();
        	double tiempoTotalEnMiliSegundos = (tFin - tInicio)/1000000.f;

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
	
	public ArrayList<ACTIONS> AStar(NodoAStar inicial, NodoAStar objetivo, StateObservation stateObs){
		NodoAStar result;
		
		PriorityQueue<NodoAStar> abiertos = new PriorityQueue<>();
	    PriorityQueue<NodoAStar> cerrados = new PriorityQueue<>();
	    
	    abiertos.add(inicial);
	    estaEnAbiertos[(int) (inicial.posicion.y)][(int) (inicial.posicion.x)] = true;
	    
	    nodos_en_memoria = abiertos.size() + cerrados.size();
	    
	    NodoAStar u;
	    while(true) {
	    	u = abiertos.poll();
	    	estaEnAbiertos[(int) (u.posicion.y)][(int) (u.posicion.x)] = false;
	    	
	    	cerrados.add(u);
	    	estaEnCerrados[(int) (u.posicion.y)][(int) (u.posicion.x)] = true;
	    	
	    	if(u.posicion.x == objetivo.posicion.x && u.posicion.y == objetivo.posicion.y) {
	    		result = u;
	    		return result.acciones;
	    	}
	    	
	    	nodos_expandidos++;
	    	
	    	ArrayList<NodoAStar> sucesores = new ArrayList<>();
			
			if(grid[(int) (u.posicion.x)][(int) (u.posicion.y - 1)].isEmpty() 
					|| (u.posicion.x == objetivo.posicion.x && u.posicion.y - 1 == objetivo.posicion.y)) {
				
				NodoAStar hijoArriba = new NodoAStar(u.posicion.copy(), objetivo.posicion.copy());
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
				NodoAStar hijoAbajo = new NodoAStar(u.posicion.copy(), objetivo.posicion.copy());
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
				NodoAStar hijoIzquierda = new NodoAStar(u.posicion.copy(), objetivo.posicion.copy());
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
				NodoAStar hijoDerecha = new NodoAStar(u.posicion.copy(), objetivo.posicion.copy());
				hijoDerecha.padre = u;
				hijoDerecha.acciones = (ArrayList<ACTIONS>) (u.acciones.clone());
				hijoDerecha.posicion.x++;
				hijoDerecha.acciones.add(Types.ACTIONS.ACTION_RIGHT);
				hijoDerecha.actualizar_coste_camino();
				hijoDerecha.actualizar_heuristica();
				sucesores.add(hijoDerecha);
			}
			
			for(NodoAStar sucesor: sucesores) {
				
				if(estaEnCerrados[(int) (sucesor.posicion.y)][(int) (sucesor.posicion.x)]) {
					if(matriz_costes[(int) (sucesor.posicion.y)][(int) (sucesor.posicion.x)] > sucesor.coste_camino) {
						matriz_costes[(int) (sucesor.posicion.y)][(int) (sucesor.posicion.x)] = (int)sucesor.coste_camino;
						cerrados.remove(sucesor);
						estaEnCerrados[(int) (sucesor.posicion.y)][(int) (sucesor.posicion.x)] = false;
						abiertos.add(sucesor);
						estaEnAbiertos[(int) (sucesor.posicion.y)][(int) (sucesor.posicion.x)] = true;
					}
				}
				else if(!estaEnCerrados[(int) (sucesor.posicion.y)][(int) (sucesor.posicion.x)] && !estaEnAbiertos[(int) (sucesor.posicion.y)][(int) (sucesor.posicion.x)]){
			    	matriz_costes[(int) (sucesor.posicion.y)][(int) (sucesor.posicion.x)] = (int)sucesor.coste_camino;
					abiertos.add(sucesor);
					estaEnAbiertos[(int) (sucesor.posicion.y)][(int) (sucesor.posicion.x)] = true;
				}
				else if(estaEnAbiertos[(int) (sucesor.posicion.y)][(int) (sucesor.posicion.x)]) {
					if(matriz_costes[(int) (sucesor.posicion.y)][(int) (sucesor.posicion.x)] > sucesor.coste_camino) {
						matriz_costes[(int) (sucesor.posicion.y)][(int) (sucesor.posicion.x)] = (int)sucesor.coste_camino;
						abiertos.remove(sucesor);
						abiertos.add(sucesor);
					}
				}
				
			}
			
			if(nodos_en_memoria < abiertos.size() + cerrados.size()) {
				nodos_en_memoria = abiertos.size() + cerrados.size();
			}
	    	
	    }
	}

}
