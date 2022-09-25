package civitas;

import GUI.Dado;
import java.util.ArrayList;

public class Jugador implements Comparable<Jugador>{//TESTED
  
  protected static int CasasMax = 4;
  protected static int CasasPorHotel = 4;
  protected static int HotelesMax = 4;
  protected static float PasoPorSalida = 1000f;
  protected static float PrecioLibertad = 200f;
  private static float SaldoInicial = 7500f;
  
  protected boolean encarcelado;
  private String nombre;
  private int numCasillaActual;
  private boolean puedeComprar;
  private float saldo;
  
  //Atributos de referencia
  private ArrayList<TituloPropiedad> propiedades;
  private Sorpresa salvoconducto;
  
  
  Jugador(String nombre){
		encarcelado = false;
		this.nombre = nombre;
		numCasillaActual = 0;  //Casilla de inicio.
		puedeComprar = true;
		saldo = SaldoInicial;
		propiedades = new ArrayList<>();
		salvoconducto = null;
  }
  
  protected Jugador(Jugador otro){
		this.encarcelado = otro.encarcelado;
		this.nombre = otro.nombre;
		this.numCasillaActual = otro.numCasillaActual;
		this.puedeComprar = otro.puedeComprar;
		this.saldo = otro.saldo;
		this.propiedades = otro.propiedades;
		this.salvoconducto = otro.salvoconducto;
  }
  
  protected boolean debeSerEncarcelado(){ //TESTED
		boolean esEncarcelado = false;
	
		if(!encarcelado){
			if(!tieneSalvoconducto())
				esEncarcelado = true;
			else{
				perderSalvoconducto();
				Diario.getInstance().ocurreEvento("Jugador " + nombre + " se libra de la carcel "
				                          + " utilizando carta Salvoconducto.");
			}
		}
	
		return esEncarcelado;
  }
  
  boolean encarcelar(int numCasillaCarcel){ //TESTED
		if(debeSerEncarcelado()){
			moverACasilla(numCasillaCarcel);
			encarcelado = true;
			Diario.getInstance().ocurreEvento("Jugador " + nombre + " encarcelado.");
		}
	
		return encarcelado;
  }
  
  boolean obtenerSalvoconducto(Sorpresa sorpresa){
		boolean salvoconductoObtenido = false;
	
		if(!encarcelado){
			salvoconducto = sorpresa;
			salvoconductoObtenido = true;
		}  
	
		return salvoconductoObtenido;
  }
  
  private void perderSalvoconducto(){ //TESTED
		salvoconducto.usada();
		salvoconducto = null;
  }
  
  boolean tieneSalvoconducto(){ //TESTED
		return salvoconducto != null;
  }
  
  boolean puedeComprarCasilla(){
		if(encarcelado)
			puedeComprar = false;
		else
			puedeComprar = true;
	
		return puedeComprar;
  }
  
  boolean paga(float cantidad){ //TESTED
		boolean resultado = modificarSaldo(cantidad * -1);
	
		return resultado;
  }
  
  boolean pagaImpuesto(float cantidad){ //TESTED
	
		boolean sePaga = false;
	
		if(!encarcelado)
			sePaga = paga(cantidad);
	
		return sePaga;
  }
  
  boolean pagaAlquiler(float cantidad){ //TESTED
		boolean sePaga = false;
	
		if(!encarcelado)
			sePaga = paga(cantidad);
	
		return sePaga;
  }
  
  boolean recibe(float cantidad){ //TESTED
		boolean seRecibe = false;
	
		if(!encarcelado)
			seRecibe = modificarSaldo(cantidad);
	
		return seRecibe;
  }
  
  boolean modificarSaldo(float cantidad){ //TESTED
		saldo += cantidad;
		Diario.getInstance().ocurreEvento("Saldo de " + nombre + " modificado en " + cantidad + " unidades.");
	
		return true;
  }
  
  boolean moverACasilla(int numCasilla){ //TESTED
		boolean movCompletado = false;
	
		if(!encarcelado){
			movCompletado = true;
			numCasillaActual = numCasilla;
			puedeComprar = false;
			Diario.getInstance().ocurreEvento(nombre + " se ha movido a la casilla " + numCasillaActual);
		}
	
		return movCompletado;
  }
  
  private boolean puedoGastar(float precio){
		boolean resultado = false;
	
		if(!encarcelado)
			resultado = (saldo >= precio);
	
		return resultado;
  }
  
  boolean vender(int ip){
		boolean vendido = false;
	
		if(!encarcelado && existeLaPropiedad(ip))
			vendido = propiedades.get(ip).vender(this);
	  
    if(vendido){
			Diario.getInstance().ocurreEvento(nombre + " vende la propiedad " + propiedades.get(ip).getNombre());
			propiedades.remove(ip);
		}	
	
		return vendido;
  }
  
  boolean tieneAlgoQueGestionar(){
		return !propiedades.isEmpty();
  }
  
  private boolean puedeSalirCarcelPagando(){
		return saldo >= PrecioLibertad;
  }
  
  boolean salirCarcelPagando(){
		boolean saleCarcel = false;
	
		if(encarcelado && puedeSalirCarcelPagando())
		{
			saleCarcel = true;
			paga(PrecioLibertad);
			encarcelado = false;
			Diario.getInstance().ocurreEvento(nombre + " ha sido puesto en libertad pagando");
		}
	
		return saleCarcel;
  }
  
  boolean salirCarcelTirando(){
		boolean saleCarcel = Dado.getInstance().salgoDeLaCarcel();
	
		if(encarcelado && saleCarcel){
			saleCarcel = true;
			encarcelado = false;
			Diario.getInstance().ocurreEvento(nombre + " ha salido de la cárcel tirando el dado");
		}
	
		return saleCarcel;
  }
  
  boolean pasaPorSalida(){
		modificarSaldo(PasoPorSalida);
		Diario.getInstance().ocurreEvento(nombre + " ha pasado por la salida");
	
		return true;
  }
  
  @Override
  public int compareTo(Jugador otro){
		/*
			  Si a < b retorna -1
				Si a = b retorna  0
				Si a > b retorna  1
				Si a y b no son comparables retorna null
    */
	
		int resultado = Float.compare(saldo, otro.saldo);
	
		return resultado;
  }
  
  boolean cancelarHipoteca(int ip){
		boolean result = false;
	
		if(!encarcelado && existeLaPropiedad(ip)){
			TituloPropiedad propiedad = propiedades.get(ip);
			float cantidad = propiedad.getImporteCancelarHipoteca();
		
			if(puedoGastar(cantidad))
				result = propiedad.cancelarHipoteca(this);
		  
			if(result)
				Diario.getInstance().ocurreEvento("El jugador " + nombre +  " cancela la hipoteca de la propiedad " + ip); 
		}
	
		return result;
  }
  
  boolean comprar(TituloPropiedad titulo){
		boolean result = false;
	
		if(!encarcelado && puedeComprar){
			float precio = titulo.getPrecioCompra();
	  
			if(puedoGastar(precio))
				result = titulo.comprar(this);
	  
			if(result){
				propiedades.add(titulo);
				Diario.getInstance().ocurreEvento("El jugador" + nombre + " compra la propiedad " + titulo.toString());
			}
		
			puedeComprar = false;
		}
	
		return result;
  }
  
  boolean construirHotel(int ip){
		boolean result = false;
	
		if(!encarcelado && existeLaPropiedad(ip)){
			TituloPropiedad propiedad = propiedades.get(ip);
			boolean puedoEdificarHotel = puedoEdificarHotel(propiedad);
	  
			if(puedoEdificarHotel){
				result = propiedad.construirHotel(this);
				propiedad.derruirCasas(CasasPorHotel, this);
				Diario.getInstance().ocurreEvento("El jugador "+nombre+ " construye hotel en la propiedad "+ip);
			}
		}
	
		return result;
  }
  
  boolean construirCasa(int ip){
		boolean result = false;
		
		if(!encarcelado && existeLaPropiedad(ip)){
			TituloPropiedad propiedad = propiedades.get(ip);
			boolean puedoEdificarCasa = puedoEdificarCasa(propiedad);
			
			if(puedoEdificarCasa)
				result = propiedad.construirCasa(this);
			
			if(result)
				Diario.getInstance().ocurreEvento("El jugador " + nombre + " construye casa en la propiedad "+ ip);
		}
		
		return result;
  }
  
  boolean hipotecar(int ip){
		boolean result = false;
	
		if(!encarcelado && existeLaPropiedad(ip)){
			TituloPropiedad propiedad = propiedades.get(ip);
			result = propiedad.hipotecar(this);
	  
			if(result)
				Diario.getInstance().ocurreEvento("El jugador " + nombre + " hipoteca la propiedad " + ip);
		}
	
		return result;
  }
  
  int cantidadCasasHoteles(){
		int numCasasHoteles = 0;
	
		for(int i = 0; i < propiedades.size(); i++)
			numCasasHoteles += propiedades.get(i).cantidadCasasHoteles();
	
		return numCasasHoteles;
  }
  
  boolean enBancarrota(){
		return (saldo < 0);
  }
  
  
  private boolean existeLaPropiedad(int ip){
		boolean existe = false;
	
		if(!propiedades.isEmpty() && ip >= 0 && ip < propiedades.size())
			existe = true;
	
		return existe;
  }
  
  private int getCasasMax(){
		return CasasMax;
  }
  
  int getCasasPorHotel(){
		return CasasPorHotel;
  }
  
  private int getHotelesMax(){
		return HotelesMax;
  }
  
  public String getNombre(){
		return nombre;
  }
  
  int getNumCasillaActual(){
		return numCasillaActual;
  }
  
  private float getPrecioLibertad(){
		return PrecioLibertad;
  }
  
  private float getPremioPasoSalida(){
		return PasoPorSalida;
  }
	
  //VISIBILIDAD CAMBIADA PARA PODER USARLO EN EL OTRO MODULO
  public ArrayList<TituloPropiedad> getPropiedades(){
		return propiedades;
  }
  
  boolean getPuedeComprar(){
		return puedeComprar;
  }
  
  public float getSaldo(){
		return saldo;
  }
  
  public boolean isEncarcelado(){
		return encarcelado;
  }
  
  private boolean puedoEdificarCasa(TituloPropiedad propiedad){
		boolean result = false;
		float precio = propiedad.getPrecioEdificar();
		
		if(puedoGastar(precio) && propiedad.getNumCasas() < CasasMax)
			result = true;
		
		return result;
  }
  
  private boolean puedoEdificarHotel(TituloPropiedad propiedad){
		boolean result = false;
		float precio = propiedad.getPrecioEdificar();
	
		if(puedoGastar(precio) && propiedad.getNumHoteles() < HotelesMax && propiedad.getNumCasas() >= CasasPorHotel)
			result = true;
	
		return result;
  }
  
  @Override
  public String toString(){
		String datos = "Nombre: " + nombre + 
				   "\nSaldo: " + saldo + 
			       "\nEncarcelado: " + encarcelado +
                   "\nCasilla actual: " + numCasillaActual +
                   "\nPuede comprar: " + puedeComprar +
                   "\nSalvoconducto: " + tieneSalvoconducto();
        
    return datos;
  }
   
  public static void main(String [] args){
  
	Jugador j = new Jugador("Juan");
	Jugador p = new Jugador(j);
  /*	
	System.out.println(p.toString());
	
	j.encarcelar(0);
	System.out.println(Diario.getInstance().leerEvento());
	
	
	for(int i = 0; i < 20; i++){
	  j.salirCarcelTirando();
      System.out.println(Diario.getInstance().leerEvento());
	  if(!j.encarcelado)
	    j.encarcelado = true;
	}
	
	TituloPropiedad t = new TituloPropiedad("Cartuja", 32.0f, 23, 75.0f, 13.0f, 33);
	
	System.out.println(j.tieneAlgoQueGestionar());
	j.getPropiedades().add(t);
	System.out.println(j.tieneAlgoQueGestionar());
	
	j.encarcelado = true;
	
	j.salirCarcelPagando();
	System.out.println(Diario.getInstance().leerEvento());
	System.out.println(Diario.getInstance().leerEvento());
	System.out.println(j.saldo);
	
	j.vender(0);
	System.out.println(Diario.getInstance().leerEvento());
	System.out.println(Diario.getInstance().leerEvento());
  */	
	//j.modificarSaldo(-7000f);
	
	System.out.println( j.compareTo(p));
  }  
}
