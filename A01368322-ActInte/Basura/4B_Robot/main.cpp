/*
|--------------------------------------------------------------|
|        Actividad Integradora 1 - 4 Robots (Basura)           |
|                                                              |
|   Creado por:                                                |
|       Marino Olvera Camacho           A01368322              |
|--------------------------------------------------------------|
*/

#include <GL/glut.h>
#include <stdlib.h>
#include <random>
#include <iomanip>
#include <iostream>
#include <algorithm>

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

int NodeSeq[16] = {0,1,2,3}; //8,9,10,11,15,14,13,12
int NodeSeq2[16] = {15,14,13,12}; //7,6,5,4,0,1,2,3
int NodeSeq3[16] = {7,6,5,4};
int NodeSeq4[16] = {8,9,10,11};

int nextNode = 0;
int nextNode2 = 15;
int nextNode3 = 7;
int nextNode4 = 8;

// Cambio
bool clean = false;
vector<int> trashes(16,0);
vector<int> nodeVisitedSeq;
// Cambio

bool finished = false;

Cubo c1(DimBoard, 1.5, -200, -200);
Cubo c2(DimBoard, 1.5, 200, 200);
Cubo c3(DimBoard, 1.5, 200, -100);
Cubo c4(DimBoard, 1.5, -200, 100);

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



void init(){


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

// Cambio
void generateTrashes() {
  
  //for(int i = 0; i < int(trashes.size()); i++) {
    
    int trash = 1;
    trashes[0] = trash;
    trashes[1] = trash;
    trashes[2] = trash;
    trashes[3] = trash;
    trashes[4] = trash;
    trashes[5] = trash;
    trashes[6] = trash;
    trashes[7] = trash;
    trashes[8] = trash;
    trashes[9] = trash;
    trashes[10] = trash;
    trashes[11] = trash;
    trashes[12] = trash;
    trashes[13] = trash;
    trashes[14] = trash;
    trashes[15] = trash;

    cout << trash;

  //}
  cout << endl;
}

bool isInTrashes(int nodeNumber) {

  if(trashes[nodeNumber] == 1) {
    return true;
  } else  {
    return false;
  }

}
// Cambio

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

    // Cambio
    if (trashes[i] == 1) {
      drawString(LocNodos[i][0], 30, LocNodos[i][1], "*");
    }
    // Cambio
  }

    

    c1.draw();
    c2.draw();
    c3.draw();
    c4.draw();
    //c3.draw();

    nextNode = c1.update(LocNodos, NodeSeq, nextNode);
    if (nextNode == 4){
      finished = true;
    }
    if (nextNode3 == 0 && finished)
    {
      abort();
    }
    
    
    nextNode2 = c2.update(LocNodos, NodeSeq2, nextNode2);
    if (nextNode2 == 15)
    {
      finished = true;
    }
    

    nextNode3 = c3.update(LocNodos, NodeSeq3, nextNode3);
    if (nextNode3 == 7)
    {
      finished = true;
    }
    

    nextNode4 = c4.update(LocNodos, NodeSeq4, nextNode4);
    if (nextNode3 == 11)
    {
      finished = true;
    }
    

    // Cambio
    if(trashes.size() > 0) {
      if(isInTrashes(nextNode)) {
        trashes[nextNode] = 0;
      } else if(isInTrashes(nextNode2)) {
        trashes[nextNode2] = 15;
      } else if(isInTrashes(nextNode3)){
        trashes[nextNode3] = 7;
      } else if(isInTrashes(nextNode4)){
        trashes[nextNode4] = 11;
      }
    }  

    
    // Cambio

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
  generateTrashes();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(WIDTH, HEIGTH);
  glutCreateWindow("Actividad Integradora - 4 Robots (Basura)");
  init();
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutKeyboardFunc(keyboard);
  glutMainLoop();

  return 0;
}

