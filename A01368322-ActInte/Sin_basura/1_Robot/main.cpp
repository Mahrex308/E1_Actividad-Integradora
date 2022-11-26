/*
|--------------------------------------------------------------|
|              Actividad Integradora 1 - 1 Robot               |
|                                                              |
|   Creado por:                                                |
|       Marino Olvera Camacho           A01368322              |
|--------------------------------------------------------------|
*/

#include <GL/glut.h>
#include <stdlib.h>
#include <random>
#include <iomanip>

#include "Cubo.h"
#include <string> 



//Variables dimensiones de la pantalla
int WIDTH=500;
int HEIGTH=500;
//Variables para establecer los valores de gluPerspective
float FOVY=60.0;
float ZNEAR=0.01;
float ZFAR=900.0;
//Variables para definir la posicion del observador
//gluLookAt(EYE_X,EYE_Y,EYE_Z,CENTER_X,CENTER_Y,CENTER_Z,UP_X,UP_Y,UP_Z)
float EYE_X=300.0;
float EYE_Y=200.0;
float EYE_Z=300.0;
float CENTER_X=0;
float CENTER_Y=0;
float CENTER_Z=0;
float UP_X=0;
float UP_Y=1;
float UP_Z=0;
//Variables para dibujar los ejes del sistema
float X_MIN=-500;
float X_MAX=500;
float Y_MIN=-500;
float Y_MAX=500;
float Z_MIN=-500;
float Z_MAX=500;
//Size del tablero
int DimBoard = 200;
// Localizacion de los nodos
float LocNodos[16][2];
int NodeSeq[16] = {0,1,2,3,7,6,5,4,8,9,10,11,15,14,13,12}; //8,9,10,11,15,14,13,12
// int NodeSeq2[16] = {15,14,13,12,8,9,10,11}; //7,6,5,4,0,1,2,3
int nextNode = 0;
// int nextNode2 = 15;

bool finished = false;

Cubo c1(DimBoard, 1.5, -200, -200);
// Cubo c2(DimBoard, 1.5, 200, 200);
// Cubo c2(DimBoard, 0.0);
// Cubo c3(DimBoard, 0.2);


void drawAxis()
{
     glLineWidth(3.0);
     //X axis in red
     glColor3f(1.0f,0.0f,0.0f);
     glBegin(GL_LINES);
       glVertex3f(X_MIN,0.0,0.0);
       glVertex3f(X_MAX,0.0,0.0);
     glEnd();
     //Y axis in green
     glColor3f(0.0f,1.0f,0.0f);
     glBegin(GL_LINES);
       glVertex3f(0.0,Y_MIN,0.0);
       glVertex3f(0.0,Y_MAX,0.0);
     glEnd();
     //Z axis in blue
     glColor3f(0.0f,0.0f,1.0f);
     glBegin(GL_LINES);
       glVertex3f(0.0,0.0,Z_MIN);
       glVertex3f(0.0,0.0,Z_MAX);
     glEnd();
     glLineWidth(1.0);
 }

void drawString(int x, int y, int z, const char* text) {
  
  glColor3f(1.0f, 1.0f, 1.0f);
  
  // glColor3f(1.0f, 1.0f, 1.0f);
  // glEnable(GL_TEXTURE_3D);
  // Render the text
  glRasterPos3i(x, y, z);
  string s = text;
  void * font = GLUT_BITMAP_9_BY_15;
  for (string::iterator i = s.begin(); i != s.end(); ++i){
    char c = *i;
    glutBitmapCharacter(font, c);
  }
}



 void init()
{


  float cx = -150;
  float cy = -150;

  for (int i = 0; i < 16; i++){

  	LocNodos[i][0] = cx;
  	LocNodos[i][1] = cy;
  	cx += 100;
  	if(cx > 150){
  		cx = -150;
  		cy += 100;
  	}
  }
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOVY, (GLfloat)WIDTH/HEIGTH, ZNEAR, ZFAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(EYE_X,EYE_Y,EYE_Z,CENTER_X,CENTER_Y,CENTER_Z,UP_X,UP_Y,UP_Z);
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    srand(time(nullptr));
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //drawAxis();
    glColor3f(0.5, 0.5, 0.5);
    //Floor
    glBegin(GL_QUADS);
        glVertex3d(-DimBoard, 0.0, -DimBoard);
        glVertex3d(-DimBoard, 0.0, DimBoard);
        glVertex3d(DimBoard, 0.0, DimBoard);
        glVertex3d(DimBoard, 0.0, -DimBoard);
    glEnd();

  for (int i = 0; i < 16; i++){
    std::string s = std::to_string(i);
    char const *pchar = s.c_str();
    drawString(LocNodos[i][0],10,LocNodos[i][1], pchar);
  }

    

    c1.draw();
    //c2.draw();
    //c3.draw();

    nextNode = c1.update(LocNodos, NodeSeq, nextNode);
    if (nextNode == 4){
      finished = true;
    }

    if (nextNode == 0 && finished)
    {
      abort();
    }
    
    
    /*
    nextNode2 = c2.update(LocNodos, NodeSeq2, nextNode2);
    if (nextNode2 == 11)
    {
      finished = true;
    }

    if (nextNode == 0 && finished)
    {
      abort();
    }
    */

    //c3.update(LocNodos);

    glutSwapBuffers();
}

void idle()
{
     display();
}

void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {//SOLID
    case 's':
    case 'S':
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            glShadeModel(GL_FLAT);
      break;
    //INTERPOL
    case 'i':
    case 'I':
            glShadeModel(GL_SMOOTH);
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      break;

    case 'w':
    case 'W':
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      break;

    case 27:   // escape
      exit(0);
      break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(WIDTH, HEIGTH);
  glutCreateWindow("Actividad Integradora 1");
  init();
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutKeyboardFunc(keyboard);
  glutMainLoop();




  return 0;
}

