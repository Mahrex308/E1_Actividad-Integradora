// Cubo.cpp
#include "Cubo.h"
#include <bits/stdc++.h>


Cubo::Cubo(int dim, float vel, float initialXPos, float initialZPos)
{
    DimBoard = dim;
    //srand(time(nullptr));
    int c;

    //Se inicializa una posicion aleatoria dentro del tablero
    Position[0] = initialXPos;
    Position[2] = initialZPos;
    //Se inicializa el vector de direccion con un valor aleatorio
    Direction[0] = rand();
    Direction[1] = rand();
    Direction[2] = rand();
    //Se normaliza el vector de direccion
    float m = sqrt(Direction[0]*Direction[0] + Direction[1]*Direction[1] + Direction[2]*Direction[2]);
    m += 0.000001;
    Direction[0] /= m;
    Direction[1] /= m;
    Direction[2] /= m;
    //se multiplica el vector de direccion por la magnitud de la velocidad
    Direction[0] *= vel;
    Direction[1] *= vel;
    Direction[2] *= vel;

    cout << " X=" << Position[0] << "\t Y= " << Position[2] << " dX=" << Direction[0] << "\t dY= " << Direction[2] << endl;
}

Cubo::~Cubo()
{
    //dtor
}

void Cubo::draw()
{
    glPushMatrix();
    glTranslatef(Position[0], Position[1], Position[2]);
    glScaled(5,5,5);
    //Se dibuja el cubo
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertexCoords);
    glColorPointer(3, GL_FLOAT, 0, vertexColors);
    glDrawElements(GL_QUADS,24,GL_UNSIGNED_INT,elementArray);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glPopMatrix();
}

float dist2Node(float Position[3], int targetNode, float LocNodos[16][2]){
    float dx = LocNodos[targetNode][0] - Position[0];
    float dy = LocNodos[targetNode][1] - Position[2];
    return  sqrt(dx * dx + dy * dy);
}

int findIdxNode(int targetNode, int NodeSeq[16]){
    for (int i = 0; i < 16; i++){ 
        if(targetNode == NodeSeq[i]){
            return i;
        }
    }
    return 0;
}

void L2Norm(float Direction[3]){
    float m = sqrt(Direction[0]*Direction[0] + Direction[1]*Direction[1] + Direction[2]*Direction[2]);
    m += 0.00001;
    Direction[0] /= m;
    Direction[1] /= m;
    Direction[2] /= m;
}

void NodeDirection(int targetNode, float LocNodos[16][2], float Direction[3], float Position[3]){
    Direction[0] = LocNodos[targetNode][0]-Position[0];
    Direction[2] = LocNodos[targetNode][1]-Position[2];
    L2Norm(Direction);
}



int Cubo::update(float LocNodos[16][2], int NodeSeq[16], int nextNode)
{

    NodeDirection(nextNode, LocNodos, Direction, Position);
    float dist = dist2Node(Position, nextNode, LocNodos);

    
    


    if(dist < 0.5){
        int idx = findIdxNode(nextNode, NodeSeq);
        idx ++;
        if(idx == 16){
            idx = 0;
        }
        nextNode = NodeSeq[idx];
    }

    Position[0] += Direction[0];
    Position[2] += Direction[2];

    //cout.width(7);

    //cout << " X=" << Position[0] << "\t Y= " << Position[2] << "\t nNode: "<< nextNode << "\t Distance: " << dist << endl;

    return nextNode;
}