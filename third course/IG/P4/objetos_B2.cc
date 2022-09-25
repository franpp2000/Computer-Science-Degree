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
  glPointSize(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawArrays(GL_POINTS,0,vertices.size());
/*
int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
*/
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
  b_normales_caras=false;
  b_normales_vertices=false;

  ambiente_difusa = _vertex4f(1.0,1.0,1.0,1.0);  //coeficiente ambiente y difuso
  especular = _vertex4f(1.0,1.0,1.0,1.0);        //coeficiente especular
  brillo=40;                                   //exponente del brillo 
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);
/*
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
*/
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
// dibujar en modo iluminación plano
//*************************************************************************

void _triangulos3D::draw_iluminacion_plana( )
{
int i;
if (b_normales_caras==false) 
  calcular_normales_vertices();

glEnable (GL_LIGHTING);
glShadeModel(GL_FLAT);  //GL_SMOOTH
glEnable(GL_NORMALIZE);

glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *) &ambiente_difusa);
glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *) &especular);
glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,brillo);

glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glNormal3fv((GLfloat *) &normales_caras[i]);
  glVertex3fv((GLfloat *) &vertices[caras[i]._0]);     
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
glDisable(GL_LIGHTING);
}

//*************************************************************************
// dibujar en modo iluminación suave
//*************************************************************************

void _triangulos3D::draw_iluminacion_suave(){
int i;
if (b_normales_vertices==false) 
  calcular_normales_vertices();

glEnable (GL_LIGHTING);
glShadeModel(GL_SMOOTH);  //GL_SMOOTH
glEnable(GL_NORMALIZE);

glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *) &ambiente_difusa);
glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *) &especular);
glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,brillo);

glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glNormal3fv((GLfloat*) &normales_vertices[caras[i]._0]);
  glVertex3fv((GLfloat *) &vertices[caras[i]._0]); 
  glNormal3fv((GLfloat*) &normales_vertices[caras[i]._1]);    
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
  glNormal3fv((GLfloat*) &normales_vertices[caras[i]._2]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
  
	}
glEnd();
glDisable(GL_LIGHTING);
}

//*************************************************************************
// Calculo de normales a las caras
//*************************************************************************

void _triangulos3D::calcular_normales_caras()
{  
_vertex3f a1, a2, n;
normales_caras.resize(caras.size());
for(int i=0; i<caras.size(); i++){
	// obtener dos vectores en el triángulo y calcular el producto vectorial
	a1=vertices[caras[i]._1]-vertices[caras[i]._0];
       	a2=vertices[caras[i]._2]-vertices[caras[i]._0];
        n=a1.cross_product(a2);
	// modulo
	float m=sqrt(n.x*n.x+n.y*n.y+n.z*n.z);
	// normalización
    	normales_caras[i]= _vertex3f(n.x/m, n.y/m, n.z/m);
	}
  
b_normales_caras=true;
}

//*************************************************************************
// Calculo de normales a los vertices
//*************************************************************************
void _triangulos3D::calcular_normales_vertices(){
  if(!b_normales_vertices){
    calcular_normales_caras();
  }

  normales_vertices.resize(vertices.size());

  for(int i = 0; i < vertices.size(); i++){
    normales_vertices[i] = _vertex3f(0.0, 0.0, 0.0);
  }

  for(int i = 0; i < caras.size(); i++){
    normales_vertices[caras[i]._0] += normales_caras[i];
    normales_vertices[caras[i]._1] += normales_caras[i];
    normales_vertices[caras[i]._2] += normales_caras[i];
  }

  for(int i = 0; i < vertices.size(); i++){
    normales_vertices[i].normalize();
  }

  b_normales_vertices = true;
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
  case SOLID_ILLUMINATED_FLAT:draw_iluminacion_plana( );break;
  case SOLID_ILLUMINATED_GOURAUD:draw_iluminacion_suave();break;
	}
}


//*************************************1 + num_a************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
  //vertices
  vertices.resize(8);
  vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
  vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
  vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
  vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;
  vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
  vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
  vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
  vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

  // triangulos
  caras.resize(12);
  caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
  caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
  caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
  caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
  caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
  caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
  caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
  caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
  caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
  caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
  caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
  caras[11]._0=1;caras[11]._1=5;caras[11]._2=4;

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
      caras.push_back(_vertex3i((indice + 1),indice, (indice + num_vert_perfil)%mod ));
      //cara superior
      caras.push_back(_vertex3i((indice + 1 + num_vert_perfil)%mod,(indice + 1) ,(indice + num_vert_perfil)%mod));
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
      caras.push_back(_vertex3i(i, vertices.size() - 1, (i + num_vert_perfil)%mod));
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
      caras.push_back(_vertex3i(i,(i + num_vert_perfil)%mod, vertices.size() - 1 ));
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
  perfil.push_back(_vertex3f(0.0, h, 0.0));
  perfil.push_back(_vertex3f(r, h, 0.0));
  perfil.push_back(_vertex3f(r, 0.0, 0.0));
  perfil.push_back(_vertex3f(0.0, 0.0, 0.0));
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
/*
  normales_vertices.resize(vertices.size());

  for(int i = 0; i < caras.size(); i++){
    normales_vertices[caras[i]._0] = vertices[caras[i]._0];
    normales_vertices[caras[i]._1] = vertices[caras[i]._1];
    normales_vertices[caras[i]._2] = vertices[caras[i]._2];
  }

  b_normales_vertices = true;
*/
}

//************************************************************************
// objeto articulado: retroexcavadora
//************************************************************************
_rueda::_rueda()
{
  altura=0.22;
  giro_ruedas = 0.0;
};

void _rueda::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
  glPushMatrix();
  glScalef(1.0,0.22,0.2);

  base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.12,0.12,0.22);
  glTranslatef(-4.0,0.0,-0.5);
  glRotatef(90.0,1,0,0);
  glRotatef(giro_ruedas,0,1,0);
  cilindro.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.12,0.12,0.22);
  glTranslatef(-2.0,0.0,-0.5);
  glRotatef(90.0,1,0,0);
  glRotatef(giro_ruedas,0,1,0);
  cilindro.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.12,0.12,0.22);
  glTranslatef(0.0,0.0,-0.5);
  glRotatef(90.0,1,0,0);
   glRotatef(giro_ruedas,0,1,0);
  cilindro.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.12,0.12,0.22);
  glTranslatef(2.0,0.0,-0.5);
  glRotatef(90.0,1,0,0);
   glRotatef(giro_ruedas,0,1,0);
  cilindro.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glScalef(0.12,0.12,0.22);
  glTranslatef(4.0,0.0,-0.5);
  glRotatef(90.0,1,0,0);
   glRotatef(giro_ruedas,0,1,0);
  cilindro.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  base.ambiente_difusa = _vertex4f(0.8, 0.5, 0.1, 1.0);
  cilindro.ambiente_difusa = _vertex4f(0.2,0.9,0.1,1.0);
}

//************************************************************************
_conecta_ruedas_cabina::_conecta_ruedas_cabina(){
}

void _conecta_ruedas_cabina::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
  glPushMatrix();
  glScalef(0.20,0.12,0.35);
  base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0,0.06,0.0);
  glScalef(0.08,0.12,0.10);
  pilar.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
}

//************************************************************************

_cabina::_cabina()
{
  altura=0.58;
  anchura=0.55;
};

void _cabina::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
  GLfloat bronze_difuso[] = {0.714, 0.4284, 0.18144,1.0},
          bronze_especular[] = {0.393548, 0.271906, 0.166721, 1.0},
          bronze_brillo[] = {25.6};

  glMaterialfv(GL_FRONT,GL_DIFFUSE,bronze_difuso);
  glMaterialfv(GL_FRONT,GL_SPECULAR,bronze_especular);
  glMaterialfv(GL_FRONT,GL_SHININESS,bronze_brillo);

  glPushMatrix();
  glScalef(0.65,0.45,0.45);
  base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.32,0,0);
  glRotatef(90.0,0,0,1);
  glScalef(0.45,0.5,0.46);
  parte_trasera1.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
  
}

//****************************************************************
_piloto::_piloto(){
}

void _piloto::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
  glPushMatrix();
  glScalef(0.02,0.08,0.02);
  base.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
   glTranslatef(0.0,0.1,0.0);
  glScalef(0.03,0.06,0.03);
  faro.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
}

//*********************************************************************
_brazo1::_brazo1(){
}

void _brazo1::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
  glPushMatrix();
  glTranslatef(-0.137,0.8,0.0);
  glRotatef(65.0,0,0,1);
  glScalef(0.60,0.13,0.09);
  parte1.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.12,0.26,0.0);
  glRotatef(-65.0,0,0,1);
  glScalef(0.70,0.13,0.09);
  parte2.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
}

//***************************************************

_brazo2::_brazo2(){
  
}

void _brazo2::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
  glPushMatrix();
  glTranslatef(0.37,-0.17,0.0);
  glRotatef(-25.0,0,0,1);
  glScalef(0.90,0.13,0.1);
  parte.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
}

//****************************************************************************
_pala::_pala(){

}

void _pala::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
  glPushMatrix();
  glTranslatef(-0.055,-0.11,0.0);
  glRotatef(63.0,0,0,1);
  glScalef(0.3,0.07,0.5);
  cubo1.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.16,-0.1,0.0);
  glRotatef(-30.0,0,0,1);
  glScalef(0.3,0.07,0.5);
  cubo2.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();
}

_retroexcavadora::_retroexcavadora()
{
  giro_cabina=0.0;
  giro_brazo1=0.0;
  giro_brazo2=0.0;
  giro_pala=0.0;
  movimiento=0.0;

  giro_brazo1_max = 15;
  giro_brazo1_min = -35;
  giro_brazo2_max = 40;
  giro_brazo2_min = -30;
  giro_pala_max = 40;
  giro_pala_min = -35;
  movimiento_max=3;
  movimiento_min=-3;
};

void _retroexcavadora::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
glTranslatef(movimiento,0.0,0.0);
glPushMatrix();

  glPushMatrix();
  glTranslatef(0.0,0.0,-cabina.anchura/2);
  chasis.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0,0.0,0.0);
  conecta_ruedas_cabina.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.0,0.0,cabina.anchura/2);
  chasis.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glRotatef(giro_cabina,0,1,0);
  glPushMatrix();
  glTranslatef(0.0,(chasis.altura+cabina.altura)/2.0,0.1);
  cabina.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.2,0.3,-0.18);
  glRotatef(giro_brazo1,0,0,1);
    glPushMatrix();
    
    brazo1.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.15 - 0.2,1.32 -0.3,-0.18 + 0.18);
    glRotatef(giro_brazo2,0,0,1);
    brazo2.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  

    glPushMatrix();
    glTranslatef(1.1 - 0.2 - 0.15,1.3 - 0.3 - 1.32,-0.35 + 0.18 + 0.18);
    glRotatef(giro_pala,0,0,1);
    pala.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();
    glPopMatrix();
  glPopMatrix();
  
   glPushMatrix();
  glTranslatef(0.27,0.625,0.3);
  piloto.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
  glPopMatrix();

glPopMatrix();

};

