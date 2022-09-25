/**
 * @file Imagen.h
 * @brief Fichero de cabecera 
 * 
 *
 */

#ifndef IMAGEN
#define IMAGEN

typedef unsigned char byte; 

class Imagen{

  private:
  /**
   * @page repConjunto Rep del TDA Imagen
   * 
   * @section invConjunto Invariate de la representacion
   * 
   * El invariante es rep.filas y rep.cols  deben ser mayores que 0
   * y rep.img[i][j] debe estar comprendido entre 0 y 255 
   * 
   * 
   * @section faConjunto Funcion de abstraccion
   * 
   * Un objeto valido @e rep del TDA Imagen representa el valor
   * 
   * (rep.filas, rep.cols, rep.img)
   */	  
			
    int filas;	/**< filas de la matriz*/
    int cols;	/**< columnas de la matriz*/	
    byte **img;	/**< array de 2 dimensiones*/
	
	/**
	 * @brief Reserva memoria dinamica para la matriz y actualiza
	 * los atributos filas y cols
	 *  
	 * @param f filas de la matriz
	 * @param c columnas de la matriz
	 * 
	 * @pre f y c deben ser valores mayores que 0
	 * 
	 * @return void
	 * 
	 * @pos si se ha tenido exito, se crea una matriz dinamica, cuya memoria sera liberada
	 * automaticamente por el destructor de la clase
	 */
	void allocate(const int f, const int c);
	
	/**
	 * @brief libera la memoria asociada a una matriz dinamica
	 * 
	 * @pre si la matriz no tiene memoria reservada aun, no hace nada 
	 * 
	 * @return void
	 * 
	 * @pos si se ha tenido exito, la memoria de la matriz quedaria liberada y los atributos
	 * de una Imagen serian reseteados a valores por defecto
	 */
	void deallocate();
	
	/**
	 * @brief copia los valores de una matriz pasada como parametro en la del 
	 * objeto implicito
	 * 
	 * @param imagen imagen de la que se va a copiar los datos en el objeto implicito
	 * 
	 * @return void
	 */
	void copy(const Imagen &);

  public:
	
	/**
	 * @brief Constructor por defecto
	 * 
	 * Inicializa los atributos de un objeto imagen a valores por defecto
	 * 
	 * @pos si se ha tenido exito, tendremos un objeto creado sin memoria dinamica
	 * reservada, simplemente inicializado a valores por defecto
	 */
	Imagen();
	
	/**
	 * @brief Constructor con parametros
	 * 
	 * Constructor que a parte de crear dicho objeto, reserva la cantidad de memoria dinamica
	 * segun los parametros pasados como parametros 
	 * 
	 * @param f filas de la matriz
	 * @param c columnas de la matriz
	 * 
	 * @pre f y c deben ser valores mayores que 0
	 * 
	 * @pos si se ha tenido exito, tendremos un objeto creado con memoria dinamica
	 * asociada a este
	 */
    Imagen(int f, int c);
	
	/**
	 * @brief Constructor de copia
	 * 
	 * Constructor que crea un objeto siendo este una copia exacta de el pasado
	 * como parametro, salvo que cada uno tiene un espacio reservado en el 
	 * heap diferente del otro, aunque con los mismos valores.
	 * 
	 * @param imagen Imagen de la que se va a hacer una copia
	 */
    Imagen(const Imagen & imagen);
    
	/**
	 * @brief Destructor de objetos de la clase
	 * 
	 * Se encarga de liberar la memoria asociada a un objeto al momento de su
	 * destruccion
	 * 
	 * @pos si se ha tenido exito, se liberara la memoria asociada a un objeto de la
	 * clase, tras lo cual sera destruido pues es ese momento cuando el destructor
	 * entra en accion
	 */
	~Imagen();
	
	/**
	 * @brief Sobrecarga del operador de asignacion
	 * 
	 * @param origen imagen que se le va a asignar a otra
	 * 
	 * @return devuelve una referencia del objeto implicito
	 */
	Imagen & operator = (const Imagen & origen);
	
	/**
	 * @brief getter del atributo filas
	 * 
	 * @return el atributo filas
	 */
    int num_filas() const;
	
	/**
	 * @brief getter del atributo columnas
	 * 
	 * @return el atributo cols
	 */
    int num_columnas() const;
	
	/**
	 * @brief setter de una posicion de la matriz
	 * 
	 * @param f coordenada Y de la posicion
	 * @param c coordenada X de la posicion
	 * @param valor valor a introducir en dicha posicion
	 * 
	 * @pre f y c deben estar en el rango que abarca la matriz, 
	 * y valor debe ser una valor comprendido entre 0-255
	 * 
	 * @return void
	 * 
	 * @pos Si se ha tenido exito, dicha posicion es modificada
	 */
    void asigna_pixel(const int f, const int c, byte valor);
	
	/**
	 * @brief getter de una posicion de la matriz
	 * 
	 * @param f coordenada Y de la posicion
	 * @param c coordenada X de la posicion
	 * 
	 * @pre f y c deben estar en el rango que abarca la matriz
	 * 
	 * @return el valor de dicha posicion
	 */
    byte valor_pixel(const int f, const int c) const;  
};

#endif

