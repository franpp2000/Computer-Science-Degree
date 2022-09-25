package tracks.singlePlayer.evaluacion.src_PERTINEZ_PEREA_FRANCISCO;

import java.util.ArrayList;

import ontology.Types.ACTIONS;
import tools.Vector2d;

public class NodoIDAStar implements Comparable<NodoIDAStar>{
	double distancia_objetivo;
	double coste_camino;
	NodoIDAStar padre = null;
	ArrayList<ACTIONS> acciones = new ArrayList<ACTIONS>();
	Vector2d posicion;
	Vector2d portal;
	
	public NodoIDAStar(Vector2d pos, Vector2d port) {
		posicion = pos;
		portal = port;
	}
	
	@Override
	public int compareTo(NodoIDAStar otro) {
		if(distancia_objetivo < otro.distancia_objetivo) {
			return -1;
		}
		else if(distancia_objetivo > otro.distancia_objetivo) {
			return 1;
		}
		
		return 0;
	}
	
	public void actualizar_heuristica(){
        distancia_objetivo = Math.abs(posicion.x - portal.x) + Math.abs(posicion.y - portal.y);
    }
	
	public void actualizar_coste_camino() {
		coste_camino = acciones.size();
	}
	
	@Override
	public boolean equals(Object otro)
    {
		NodoIDAStar o = (NodoIDAStar)otro;
        return posicion.x == o.posicion.x && posicion.y == o.posicion.y;
    }

}
