#ifndef SRC_FUNCIONES_H_
#define SRC_FUNCIONES_H_

#include <iostream>
#include <GL/glut.h>  // Incluir GLUT para OpenGL

using namespace std;



const int MAX_DISPAROS = 10;  // Definir MAX_DISPAROS como una constante
struct Disparo {
    float x, y;
    float velocidad;
    bool activo;

    Disparo() : x(0.0f), y(0.0f), velocidad(0.5f), activo(false) {}
};
extern Disparo disparos[MAX_DISPAROS];  // Declarar el arreglo de disparos como externo


void Inicializar();
void planoCartesiano();
void traslado(int, int, int);
void Dibujar();
void naveespacial();
void asteroide();
// Prototipo de la función de actualización del asteroide
void actualizarAsteroide(int valor);
void generarAsteroide();
void teclado(unsigned char key, int x, int y);  // Declaración de teclado
void dibujarDisparos();
void actualizarDisparos(int valor);
#endif
