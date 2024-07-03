#ifndef SRC_FUNCIONES_H_
#define SRC_FUNCIONES_H_

#include <iostream>
#include <GL/glut.h>


using namespace std;

void Inicializar();
void planoCartesiano();
void traslado(int, int, int);
void Dibujar();
void naveespacial();
void asteroide();
// Prototipo de la función de actualización del asteroide
void actualizarAsteroide(int valor);
void generarAsteroide();
#endif
