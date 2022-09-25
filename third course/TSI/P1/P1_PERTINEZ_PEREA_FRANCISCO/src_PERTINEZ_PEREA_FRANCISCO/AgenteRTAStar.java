package tracks.singlePlayer.evaluacion.src_PERTINEZ_PEREA_FRANCISCO;

import java.util.ArrayList;
import java.util.Comparator;

import core.game.Observation;
import core.game.StateObservation;
import core.player.AbstractPlayer;
import ontology.Types;
import ontology.Types.ACTIONS;
import tools.ElapsedCpuTimer;
import tools.Pair;
import tools.Vector2d;

public class AgenteRTAStar extends AbstractPlayer{
	
	Vector2d fescala;
	Vector2d portal;
	int heuristicas[][];
	int nodos_expandidos = 0;
	int nodos_en_memoria = 0;
	long tiempoTotalEnMiliSegundos;
	
	public AgenteRTAStar(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		//Calculamos el factor de escala entre mundos (pixeles -> grid)
        fescala = new Vector2d(stateObs.getWorldDimension().width / stateObs.getObservationGrid().length , 
        		stateObs.getWorldDimension().height / stateObs.getObservationGrid()[0].length);      
      
        //Se crea una lista de observaciones de portales, ordenada por cercania al avatar
        ArrayList<Observation>[] posiciones = stateObs.getPortalsPositions(stateObs.getAvatarPosition());
        
        heuristicas = new int[(int) (stateObs.getWorldDimension().height / fescala.y)][(int) (stateObs.getWorldDimension().width / fescala.x)];

        for(int i = 0; i < (int) (stateObs.getWorldDimension().height / fescala.y); i++) {
        	for(int j = 0; j < (int) (stateObs.getWorldDimension().width / fescala.x); j++) {
        		heuristicas[i][j] = -1;
        	}
        }
        
        //Seleccionamos el portal mas proximo
        portal = posiciones[0].get(0).position;
        portal.x = Math.floor(portal.x / fescala.x);
        portal.y = Math.floor(portal.y / fescala.y);
	}
	
	@Override
	public ACTIONS act(StateObservation stateObs, ElapsedCpuTimer elapsedTimer) {
		
		long tInicio = System.nanoTime();
		
        //Posicion del avatar
        Vector2d avatar =  new Vector2d(stateObs.getAvatarPosition().x / fescala.x, 
        		stateObs.getAvatarPosition().y / fescala.y);
        
        ArrayList<Pair<String, Integer>> sucesores = new ArrayList<>();
        
        
        //Probamos las cuatro acciones y calculamos la distancia del nuevo estado al portal.
        Vector2d newPos_up, 
        		newPos_down, 
        		newPos_left, 
        		newPos_right;
        
        int CnewPos_up = 1, 
        	CnewPos_down = 1, 
        	CnewPos_left = 1, 
        	CnewPos_right = 1;
        
        nodos_expandidos++;
        
        if (stateObs.getObservationGrid()[(int)avatar.x][(int)avatar.y-1].isEmpty() 
        		|| (avatar.x == portal.x && avatar.y - 1 == portal.y)) {
        	
        	if(avatar.x - 1 == portal.x && avatar.y == portal.y) {
        		System.out.println("Runtime: " + tiempoTotalEnMiliSegundos + " ms");
            	System.out.println("Tamaño de la ruta: " + (nodos_expandidos));
            	System.out.println("Número de nodos expandidos: " + nodos_expandidos);
            	System.out.println("Máximo número de nodos en memoria: " + nodos_en_memoria);
        	}
        	
        	newPos_up = new Vector2d(avatar.x, avatar.y-1);
        	
        	if(heuristicas[(int)newPos_up.y][(int)newPos_up.x] != -1) {
        		CnewPos_up += heuristicas[(int)newPos_up.y][(int)newPos_up.x];
        	}
        	else {
        		CnewPos_up += Math.abs(newPos_up.x - portal.x) + Math.abs(newPos_up.y-portal.y);
        	}
        	
        	sucesores.add(new Pair<String, Integer>("UP", CnewPos_up));
        }
        if (stateObs.getObservationGrid()[(int)avatar.x][(int)avatar.y+1].isEmpty()
        		|| (avatar.x == portal.x && avatar.y + 1 == portal.y)) {
        	
        	if(avatar.x == portal.x && avatar.y + 1 == portal.y) {
        		System.out.println("Runtime: " + tiempoTotalEnMiliSegundos + " ms");
            	System.out.println("Tamaño de la ruta: " + (nodos_expandidos));
            	System.out.println("Número de nodos expandidos: " + nodos_expandidos);
            	System.out.println("Máximo número de nodos en memoria: " + nodos_en_memoria);
        	}
        	
        	newPos_down = new Vector2d(avatar.x, avatar.y+1);
        	
        	if(heuristicas[(int)newPos_down.y][(int)newPos_down.x] != -1) {
        		CnewPos_down += heuristicas[(int)newPos_down.y][(int)newPos_down.x];
        	}
        	else {
        		CnewPos_down += Math.abs(newPos_down.x - portal.x) + Math.abs(newPos_down.y-portal.y);
        	}
        	
        	sucesores.add(new Pair<String, Integer>("DOWN", CnewPos_down));
        	
        }
        if (stateObs.getObservationGrid()[(int)avatar.x - 1][(int)avatar.y].isEmpty() 
        		|| (avatar.x - 1 == portal.x && avatar.y == portal.y)) {
        	
        	if(avatar.x - 1 == portal.x && avatar.y == portal.y) {
        		System.out.println("Runtime: " + tiempoTotalEnMiliSegundos + " ms");
            	System.out.println("Tamaño de la ruta: " + (nodos_expandidos));
            	System.out.println("Número de nodos expandidos: " + nodos_expandidos);
            	System.out.println("Máximo número de nodos en memoria: " + nodos_en_memoria);
        	}
        	
        	newPos_left = new Vector2d(avatar.x - 1, avatar.y);
        	
        	
        	if(heuristicas[(int)newPos_left.y][(int)newPos_left.x] != -1) {
        		CnewPos_left += heuristicas[(int)newPos_left.y][(int)newPos_left.x];
        	}
        	else {
        		CnewPos_left += Math.abs(newPos_left.x - portal.x) + Math.abs(newPos_left.y-portal.y);
        	}
        	
        	sucesores.add(new Pair<String, Integer>("LEFT", CnewPos_left));
        	
        }
        if (stateObs.getObservationGrid()[(int)avatar.x + 1][(int)avatar.y].isEmpty()
        		|| (avatar.x + 1 == portal.x && avatar.y == portal.y)) {
        	
        	if(avatar.x + 1 == portal.x && avatar.y == portal.y) {
        		System.out.println("Runtime: " + (tiempoTotalEnMiliSegundos/1000000.0f) + " ms");
            	System.out.println("Tamaño de la ruta: " + (nodos_expandidos));
            	System.out.println("Número de nodos expandidos: " + nodos_expandidos);
            	System.out.println("Máximo número de nodos en memoria: " + nodos_en_memoria);
        	}
        	
        	newPos_right = new Vector2d(avatar.x + 1, avatar.y);
        	
        	if(heuristicas[(int)newPos_right.y][(int)newPos_right.x] != -1) {
        		CnewPos_right += heuristicas[(int)newPos_right.y][(int)newPos_right.x];
        	}
        	else {
        		CnewPos_right += Math.abs(newPos_right.x - portal.x) + Math.abs(newPos_right.y-portal.y);
        	}
        	
        	sucesores.add(new Pair<String, Integer>("RIGHT", CnewPos_right));
        }
        
        sucesores.sort(new Comparator<Pair<String, Integer>>() {
            @Override
            public int compare(Pair<String, Integer> o1, Pair<String, Integer> o2) {
                if(o1.second.compareTo(o2.second) == 0) {
                	return o1.first.compareTo(o2.first);
                }
                return o1.second.compareTo(o2.second);
            }
        });
        
        Pair<String, Integer> segundo;
        
        if(sucesores.size() > 1) {
        	segundo = sucesores.get(1);
        }
        else {
        	segundo = sucesores.get(0);
        }
        
        if(heuristicas[(int)avatar.y][(int)avatar.x] < segundo.second) {
        	if(heuristicas[(int)avatar.y][(int)avatar.x] == -1)
        		nodos_en_memoria++;
        	
        	heuristicas[(int)avatar.y][(int)avatar.x] = segundo.second;
        }
        
        Pair<String, Integer> primero = sucesores.get(0);
        
        long tFin = System.nanoTime();
    	tiempoTotalEnMiliSegundos += (tFin - tInicio);
    	
        if(primero.first == "UP") {
        	return Types.ACTIONS.ACTION_UP;
        }
        else if(primero.first == "DOWN") {
        	return Types.ACTIONS.ACTION_DOWN;
        }
        else if(primero.first == "LEFT") {
        	return Types.ACTIONS.ACTION_LEFT;
        }
        else if(primero.first == "RIGHT") {
        	return Types.ACTIONS.ACTION_RIGHT;
        }
        
        return Types.ACTIONS.ACTION_NIL;
        		
	}
}
