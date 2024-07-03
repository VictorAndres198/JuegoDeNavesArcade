#include "funciones.h"

void Inicializar(){
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Fondo negro
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 20.0, -20.0, 20.0, -1.0, 1.0);
    // Inicializar todos los disparos como inactivos
    for (int i = 0; i < MAX_DISPAROS; ++i) {
        disparos[i].activo = false;
    }
}

void Dibujar(){
    glClear(GL_COLOR_BUFFER_BIT);
    planoCartesiano();
    naveespacial();
    asteroide();
    dibujarDisparos();
    glFlush();
}
