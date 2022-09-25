package GUI;

import civitas.CivitasJuego;
import java.util.ArrayList;

public class TestP5 {
    
    public static void main(String[] args){
        CivitasView vista = new CivitasView();
        Dado.createInstance(vista);
        Dado.getInstance().setDebug(true);
        CapturaNombres capturaNombres = new CapturaNombres(vista, true);
        ArrayList<String> nombres = capturaNombres.getNombres();
        CivitasJuego juego = new CivitasJuego(nombres);
        Controlador controlador = new Controlador(juego,vista);
        vista.setCivitasJuego(juego); //UNIMOS EL JUEGO CON LA VISTA
        //controlador.juega();

        
        
    }
    
}
