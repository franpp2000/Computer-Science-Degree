//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B2.h"
#include "file_ply_stl.hpp"



//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
  int i;
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glColor3f(r,g,b);
  glBegin(GL_TRIANGLES);

  for (i=0;i<caras.size();i++){
	  glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	  glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	  glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();


}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
  int i;
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

  glBegin(GL_TRIANGLES);
  for (i=0;i<caras.size();i++){
	  if(i % 2 == 0)
		  glColor3f(r2,g2,b2);
	  else
		  glColor3f(r1,g1,b1);

	  glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	  glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	  glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
  glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
	}
}

//*************************************1 + num_a************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
  //vertices
	vertices.resize(8);
	vertices[0].x = 0; vertices[0].y = 0; vertices[0].z = tam;
	vertices[1].x = tam; vertices[1].y = 0; vertices[1].z = tam;
	vertices[2].x = tam; vertices[2].y = 0; vertices[2].z = 0;
	vertices[3].x = 0; vertices[3].y = 0; vertices[3].z = 0;
	vertices[4].x = 0; vertices[4].y = tam; vertices[4].z = tam;
	vertices[5].x = tam; vertices[5].y = tam; vertices[5].z = tam;
	vertices[6].x = tam; vertices[6].y = tam; vertices[6].z = 0;
	vertices[7].x = 0; vertices[7].y = tam; vertices[7].z = 0;

	// triangulos
	caras.resize(12);
	caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
	caras[1]._0=1;caras[1]._1=5;caras[1]._2=4;
	caras[2]._0=1;caras[2]._1=2;caras[2]._2=5;
	caras[3]._0=2;caras[3]._1=6;caras[3]._2=5;
	caras[4]._0=3;caras[4]._1=2;caras[4]._2=6;
	caras[5]._0=3;caras[5]._1=6;caras[5]._2=7;
	caras[6]._0=0;caras[6]._1=3;caras[6]._2=7;
	caras[7]._0=0;caras[7]._1=7;caras[7]._2=4;
	caras[8]._0=0;caras[8]._1=1;caras[8]._2=3;
	caras[9]._0=1;caras[9]._1=2;caras[9]._2=3;
	caras[10]._0=4;caras[10]._1=5;caras[10]._2=6;
	caras[12]._0=4;caras[11]._1=6;caras[11]._2=7;

}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
   // leer lista de coordenadas de vértices y lista de indices de vértices
 
}



int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car, i;

vector<float> ver_ply ;
vector<int>   car_ply ;
 
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

vertices.resize(n_ver);

for(i = 0; i < n_ver; i++){
  vertices[i].x = ver_ply[3 * i];
  vertices[i].y = ver_ply[3 * i + 1];
  vertices[i].z = ver_ply[3 * i + 2];
}

caras.resize(n_car);

for(i = 0; i < n_car; i++){
  caras[i]._0 = car_ply[3 * i];
  caras[i]._1 = car_ply[3 * i + 1];
  caras[i]._2 = car_ply[3 * i + 2];
}


return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num_instancias_perfil)
{
  int i,j;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_vert_perfil;

  // tratamiento de los vértices

  num_vert_perfil = perfil.size();

  // salvamos los vertices extremos en caso de que x = 0 para que no se creen puntos y caras degeneradas
  _vertex3f vert_perf_inicial(0.0, perfil[0].y, 0.0), vert_perf_final(0.0, perfil[num_vert_perfil - 1].y, 0.0);

  if (fabs(perfil[0].x) == 0.0){
    perfil.erase(perfil.begin());
    num_vert_perfil = perfil.size();
  }

  if (fabs(perfil[num_vert_perfil - 1].x) == 0.0){
    perfil.pop_back();
    num_vert_perfil = perfil.size();
  }

  // colocamos los vertices del perfil de abajo a arriba en el caso de que no lo estén
  bool ajuste = false;

  if(fabs(perfil[0].y) > perfil[1].y){
    ajuste = true;
    vector<_vertex3f> aux;

    for(i = num_vert_perfil - 1; i >= 0; i--){
      aux.push_back(perfil[i]);
    }

    perfil = aux;
  }


  for (j = 0; j < num_instancias_perfil; j++)
  {
    for (i = 0; i < num_vert_perfil; i++)
    {
      vertice_aux.x=perfil[i].x * cos(2.0 * M_PI * j / (1.0 * num_instancias_perfil)) +
                      perfil[i].z * sin(2.0 * M_PI * j / (1.0 * num_instancias_perfil));
      vertice_aux.z=-perfil[i].x * sin(2.0 * M_PI * j / (1.0 * num_instancias_perfil)) +
                      perfil[i].z * cos(2.0 * M_PI * j / (1.0 * num_instancias_perfil));
      vertice_aux.y=perfil[i].y;
      
      vertices.push_back(vertice_aux);
    }
  }

  // tratamiento de las caras 
  int indice = 0;
  int mod = vertices.size();

  // caras laterales
  for(j = 0; j < num_instancias_perfil; j++){
    for(i = 0; i < num_vert_perfil - 1; i++){
      indice = (j * num_vert_perfil + i);
      // cara inferior
      caras.push_back(_vertex3i(indice, (indice + 1), (indice + num_vert_perfil)%mod ));
      //cara superior
      caras.push_back(_vertex3i((indice + 1), (indice + 1 + num_vert_perfil)%mod ,(indice + num_vert_perfil)%mod));
    }
  }
  
  // tapa inferior
  if (fabs(perfil[0].x) > 0.0)
  {
    if (ajuste)
      vertices.push_back(vert_perf_final);
    else
      vertices.push_back(vert_perf_inicial);

    for(int i = 0; i < vertices.size(); i +=  num_vert_perfil){
      caras.push_back(_vertex3i(vertices.size() - 1, i, (i + num_vert_perfil)%mod));
    }
  }
  
  // tapa superior
  if (fabs(perfil[num_vert_perfil-1].x) > 0.0)
  {
    if (ajuste)
      vertices.push_back(vert_perf_inicial);
    else
      vertices.push_back(vert_perf_final);

    for(int i = num_vert_perfil - 1; i < vertices.size(); i +=  num_vert_perfil){
      caras.push_back(_vertex3i((i + num_vert_perfil)%mod,i, vertices.size() - 1 ));
    }
  }
  
}

//************************************************************************
// Clase cono
//************************************************************************
_cono::_cono(int num_instancias_perfil, float h, float r){
  // Montamos el perfil de la figura
  vector<_vertex3f> perfil;
  perfil.push_back(_vertex3f(0.0, 0.0, 0.0));
  perfil.push_back(_vertex3f(r, 0.0, 0.0));
  perfil.push_back(_vertex3f(0.0, h, 0.0));

  // funcion de revolucion
  parametros(perfil, num_instancias_perfil);
}

//************************************************************************
// Clase cilindro
//************************************************************************
_cilindro::_cilindro(int num_instancias_perfil, float h, float r){

  // Montamos el perfil de la figura
  vector<_vertex3f> perfil;
  perfil.push_back(_vertex3f(0.0, 0.0, 0.0));
  perfil.push_back(_vertex3f(r, 0.0, 0.0));
  perfil.push_back(_vertex3f(r, h, 0.0));
  perfil.push_back(_vertex3f(0.0, h, 0.0));
  
  // funcion de revolucion
  parametros(perfil, num_instancias_perfil);
}

//************************************************************************
// Clase esfera
//************************************************************************
_esfera::_esfera(int num_instancias_perfil, int num_vert_perfil, float r){
  // Montamos el perfil de la figura
  vector<_vertex3f> perfil;
  
  // Creamos el angulo
  double angulo = M_PI/num_vert_perfil;
  
  //Vertice superio
  perfil.push_back(_vertex3f(0.0, r, 0.0));
  
  //Vertices intermedios
  for(int i = 1; i < num_vert_perfil; i++){
    perfil.push_back(_vertex3f(r*sin(angulo*i), r*cos(angulo*i), 0.0));
  }

  //Vertice inferior
  perfil.push_back(_vertex3f(0.0, -r, 0.0));

  parametros(perfil, num_instancias_perfil);
}
