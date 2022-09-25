//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

vector<_vertex3i> caras;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void  parametros(vector<_vertex3f> perfil1, int num1);

vector<_vertex3f> perfil; 
int num;
};

//************************************************************************
// Clase cono
//************************************************************************
class _cono: public _rotacion{
	public:
		_cono(int num_instancias_perfil = 20, float h = 1.0, float r = 1.0);
};

//************************************************************************
// Clase cilindro
//************************************************************************
class _cilindro: public _rotacion
{
	public:
		_cilindro(int num_instancias_perfil = 20, float h = 1.0, float r = 1.0);
};

//************************************************************************
// Clase cilindro
//************************************************************************
class _esfera: public _rotacion
{
	public:
		_esfera(int num_instacias_perfil = 15, int num_vert_perfil = 20, float r = 1.0);
};

//************************************************************************
// objeto articulado: retroexcavadora
//************************************************************************

class _rueda: public _triangulos3D
{
	public:
		_rueda();
	void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	float altura;
	float giro_ruedas;

	protected:
	_cilindro  cilindro;
	_cubo  base;
};

//************************************************************************

class _conecta_ruedas_cabina: public _triangulos3D
{
public:
       _conecta_ruedas_cabina();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_cubo  base;
_cilindro pilar;
};

//************************************************************************

class _cabina: public _triangulos3D
{
public:
       _cabina();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float altura;
float anchura;

protected:
_cubo  base;
_piramide parte_trasera1;
};

//************************************************************************

class _piloto: public _triangulos3D
{
public:
       _piloto();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_cilindro  base;
_esfera faro;
};

//************************************************************************

class _brazo1: public _triangulos3D
{
public:
       _brazo1();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_cubo parte1;
_cubo parte2;
};

//*************************************************************************
class _brazo2: public _triangulos3D
{
public:
       _brazo2();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_cubo parte;
};

//*************************************************************************
class _pala: public _triangulos3D
{
public:
       _pala();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_cubo  cubo1;
_cubo  cubo2;
};


//************************************************************************

class _retroexcavadora: public _triangulos3D
{
public:
       _retroexcavadora();
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

float giro_cabina;
float giro_brazo1;
float giro_brazo2;
float giro_pala;
float movimiento;

float giro_brazo1_max;
float giro_brazo1_min;
float giro_brazo2_max;
float giro_brazo2_min;
float giro_pala_max;
float giro_pala_min;
float movimiento_max;
float movimiento_min;


_rueda chasis;

protected:
_cabina cabina;
_conecta_ruedas_cabina conecta_ruedas_cabina;
_piloto piloto;
_brazo1 brazo1;
_brazo2 brazo2;
_pala pala;
};


