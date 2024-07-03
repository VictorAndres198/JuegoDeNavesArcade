#ifndef SRC_FUNCIONES_H_
#define SRC_FUNCIONES_H_

#include <iostream>
#include <vector>
#include <GL/glut.h>

using namespace std;

void Inicializar();
void planoCartesiano();
void traslado(int, int, int);
void Dibujar();
void naveespacial();
void asteroide();
/*
void Disparo(unsigned char key, int x, int y);
void CrearProyectil();
void MoverProyectiles();
void CrearAsteroide();
void MoverAsteroides();
//void DibujarExplosión(float x, float y);
//void CheckCollisions();

struct Proyectil {
    float x, y;
};

struct Asteroide {
    float x, y;
    float angulo;
};

extern vector<Proyectil> proyectiles;
extern vector<Asteroide> asteroides;
*/
#endif
