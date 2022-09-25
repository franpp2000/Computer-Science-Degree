package tracks.singlePlayer.evaluacion.src_PERTINEZ_PEREA_FRANCISCO;

import java.util.ArrayList;
import core.game.Observation;
import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types;
import ontology.Types.ACTIONS;
import tools.ElapsedCpuTimer;
import tools.Vector2d;

public class AgenteBFS extends AbstractPlayer{
	
	Vector2d fescala;
	Vector2d portal;
	boolean estado[][];
	ArrayList<Observation> grid[][];
	ArrayList<ACTIONS> plan;
	int nodos_expandidos = 0;
	int nodos_en_memoria = 0;
	
	public AgenteBFS(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		plan = new ArrayList<>();
		
		//Calculamos el factor de escala entre mundos (pixeles -> grid)
        fescala = new Vector2d(stateObs.getWorldDimension().width / stateObs.getObservationGrid().length , 
        		stateObs.getWorldDimension().height / stateObs.getObservationGrid()[0].length);      
        
        estado = new boolean[(int) (stateObs.getWorldDimension().height / fescala.y)][(int) (stateObs.getWorldDimension().width / fescala.x)];
        grid = stateObs.getObservationGrid();
        
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
        	Nodo inicial = new Nodo(avatar.copy());
        	Nodo objetivo = new Nodo(portal.copy());
        	
        	
        	long tInicio = System.nanoTime();
        	plan = BFS(inicial, objetivo);
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
	
	public ArrayList<ACTIONS> BFS(Nodo inicial, Nodo objetivo) {
		ArrayList<ACTIONS> result = new ArrayList<>(); 
		ArrayList<Nodo> q = new ArrayList<>();
		estado[(int) (inicial.posicion.y)][(int) (inicial.posicion.x)] = true;
		nodos_en_memoria++;
		inicial.padre = null;
		
		q.add(inicial);
		
		while(!q.isEmpty()){
			nodos_expandidos++;
			Nodo u = q.get(0);
			q.remove(0);
			
			if(u.posicion.x == objetivo.posicion.x && u.posicion.y == objetivo.posicion.y) {
				result = u.acciones;
				return result;
			}
			
			ArrayList<Nodo> sucesores = new ArrayList<>();
			
			if(grid[(int) (u.posicion.x)][(int) (u.posicion.y - 1)].isEmpty() 
					|| (u.posicion.x == objetivo.posicion.x && u.posicion.y - 1 == objetivo.posicion.y)) {
				
				Nodo hijoArriba = new Nodo(u.posicion.copy());
				hijoArriba.acciones = (ArrayList<ACTIONS>) (u.acciones.clone());
				hijoArriba.posicion.y--;
				hijoArriba.acciones.add(Types.ACTIONS.ACTION_UP);
				sucesores.add(hijoArriba);
			}
        
			if(grid[(int) (u.posicion.x)][(int) (u.posicion.y + 1)].isEmpty() 
					|| (u.posicion.x == objetivo.posicion.x && u.posicion.y + 1 == objetivo.posicion.y)) {
				Nodo hijoAbajo = new Nodo(u.posicion.copy());
				hijoAbajo.acciones = (ArrayList<ACTIONS>) (u.acciones.clone());
				hijoAbajo.posicion.y++;
				hijoAbajo.acciones.add(Types.ACTIONS.ACTION_DOWN);
				sucesores.add(hijoAbajo);
			} 
        		
			
			if(grid[(int) (u.posicion.x - 1)][(int) (u.posicion.y)].isEmpty() 
					|| (u.posicion.x - 1 == objetivo.posicion.x && u.posicion.y == objetivo.posicion.y)) {
				Nodo hijoIzquierda = new Nodo(u.posicion.copy());
				hijoIzquierda.acciones = (ArrayList<ACTIONS>) (u.acciones.clone());
				hijoIzquierda.posicion.x--;
				hijoIzquierda.acciones.add(Types.ACTIONS.ACTION_LEFT);
				sucesores.add(hijoIzquierda);
			} 
			
			if(grid[(int) (u.posicion.x + 1)][(int) (u.posicion.y)].isEmpty() 
					|| (u.posicion.x + 1 == objetivo.posicion.x && u.posicion.y == objetivo.posicion.y)) {
				Nodo hijoDerecha = new Nodo(u.posicion.copy());
				hijoDerecha.acciones = (ArrayList<ACTIONS>) (u.acciones.clone());
				hijoDerecha.posicion.x++;
				hijoDerecha.acciones.add(Types.ACTIONS.ACTION_RIGHT);
				sucesores.add(hijoDerecha);
			}
			
			
			for(int i = 0; i < sucesores.size(); i++) {
				if(estado[(int) (sucesores.get(i).posicion.y)][(int) (sucesores.get(i).posicion.x)] == false) {
					nodos_en_memoria++;
					estado[(int) (sucesores.get(i).posicion.y)][(int) (sucesores.get(i).posicion.x)] = true;
					sucesores.get(i).padre = u;
					q.add(sucesores.get(i));
				}
			}
			
		}
		
		return result;
	}
	
}