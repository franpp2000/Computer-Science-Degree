#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>



void Ejes (int width)
{   
    glLineWidth(width);
    glBegin(GL_LINES);
       glColor3f(1.0,0.0,0.0);
       glVertex3f(-1.0,0.0,0.0);
       glVertex3f(1.0,0.0,0.0);
       glColor3f(0.0,1.0,0.0);
       glVertex3f(0.0,-1.0,0.0);
       glColor3f(1.0,1.0,0.0);
       glVertex3f(0.0,1.0,0.0);   
    glEnd();
   
       
}

void Circle (GLfloat radio, GLfloat cx, GLfloat cy, GLint n, GLenum modo)
{
   int i;

   if (modo==GL_LINE) 
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   else if (modo==GL_FILL) 
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   else 
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

   glBegin( GL_POLYGON );
      for (i=0;i<n;i++)
         glVertex2f( cx+radio*cos(2.0*M_PI*i/n), cy+radio*sin(2.0*M_PI*i/n));
   glEnd();
}

void Monigote ()
{
  
 
// cara
   glLineWidth(1);
   glColor3f(1.0,0.8,0.6);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd(); 

   glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd(); 

   // oreja derecha
   glColor3f(1.0,0.8,0.6);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(0.2,0.18,0.0);
      glVertex3f(0.30,0.18,0.0);
      glVertex3f(0.30,0.42,0.0);
      glVertex3f(0.2,0.42,0.0);
   glEnd();

   glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
      glVertex3f(0.2,0.18,0.0);
      glVertex3f(0.30,0.18,0.0);
      glVertex3f(0.30,0.42,0.0);
      glVertex3f(0.2,0.42,0.0);
   glEnd();

   // oreja izquierda
   glColor3f(1.0,0.8,0.6);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.30,0.18,0.0);
      glVertex3f(-0.2,0.18,0.0);
      glVertex3f(-0.2,0.42,0.0);
      glVertex3f(-0.30,0.42,0.0);
   glEnd();
   
   glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
      glVertex3f(-0.30,0.18,0.0);
      glVertex3f(-0.2,0.18,0.0);
      glVertex3f(-0.2,0.42,0.0);
      glVertex3f(-0.30,0.42,0.0);
   glEnd();

   // ala sombrero
   glColor3f(0,0,0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.3,0.55,0.0);
      glVertex3f(0.3,0.55,0);
      glVertex3f(0.3,0.67,0.0);
      glVertex3f(-0.3,0.67,0.0);
   glEnd(); 

   glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
      glVertex3f(-0.3,0.55,0.0);
      glVertex3f(0.3,0.55,0);
      glVertex3f(0.3,0.67,0.0);
      glVertex3f(-0.3,0.67,0.0);
   glEnd(); 

   // copa sombrero
   glColor3f(0,0,0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.67,0.0);
      glVertex3f(0.2,0.67,0.0);
      glVertex3f(0.2,0.90,0.0);
      glVertex3f(-0.2,0.90,0.0);
   glEnd(); 

   glColor3f(0.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.67,0.0);
      glVertex3f(0.2,0.67,0.0);
      glVertex3f(0.2,0.90,0.0);
      glVertex3f(-0.2,0.90,0.0);
   glEnd();

   // ojo derecho
   glColor3f(0.0,0.0,1.0);
   Circle(0.050, 0.08, 0.42, 20,GL_FILL);

   // ojo izquierdo
   glColor3f(0.0,0.0,1.0);
   Circle(0.050, -0.08, 0.42, 20,GL_FILL);

   // nariz
   glColor3f(1.0,0.0,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.08,0.23,0.0);
      glVertex3f(0.08,0.23,0.0);
      glVertex3f(0.0,0.35,0.0);
   glEnd(); 

   // boca
   glColor3f(1.0,0.6,0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.11,0.09,0.0);
      glVertex3f(0.11,0.09,0.0);
      glVertex3f(0.11,0.15,0.0);
      glVertex3f(-0.11,0.15,0.0);
   glEnd();

   glColor3f(1.0,0.6,0.0);
   Circle(0.028, 0.1, 0.12, 20,GL_FILL); 

   glColor3f(1.0,0.6,0.0);
   Circle(0.028, -0.1, 0.12, 20,GL_FILL); 

}


static void Init( )
{

   glShadeModel( GL_FLAT);
}


static void Reshape( int width, int height )
{
    glViewport(0, 0, (GLint)width, (GLint)height);
    glOrtho (-1.0, 1.0,-1.0, 1.0, -10, 10.0);
}

static void Display( )
{

  glClearColor(0.5,0.5,0.5,0.0);
  glClear( GL_COLOR_BUFFER_BIT );
   
  
   
   Ejes(6);
   Monigote();
   
   glFlush();
}


static void Keyboard(unsigned char key, int x, int y )
{
 
  if (key==27)
      exit(0);

}


int main( int argc, char **argv )
{
   glutInit(&argc,argv);
   glutInitDisplayMode( GLUT_RGB );

   glutInitWindowPosition( 20, 100 );
   glutInitWindowSize(500, 500 );
   glutCreateWindow("Practica 0 IG");


   Init();

   glutReshapeFunc(Reshape);
   glutDisplayFunc(Display);
   glutKeyboardFunc(Keyboard);
  
   glutMainLoop( );

   return 0;
}

