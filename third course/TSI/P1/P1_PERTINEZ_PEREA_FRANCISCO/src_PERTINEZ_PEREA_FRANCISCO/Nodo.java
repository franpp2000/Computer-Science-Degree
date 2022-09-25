package tracks.singlePlayer.evaluacion.src_PERTINEZ_PEREA_FRANCISCO;

import java.awt.Desktop.Action;
import java.util.ArrayList;

import core.game.Observation;
import core.game.StateObservation;
import ontology.Types.ACTIONS;
import tools.Vector2d;

public class Nodo {
	Vector2d posicion;
	public Nodo padre;
	public ArrayList<ACTIONS> acciones;
	
    public Nodo(Vector2d pos) {
    	posicion = pos;
    	padre = null;
    	acciones = new ArrayList<>();
    }
}
