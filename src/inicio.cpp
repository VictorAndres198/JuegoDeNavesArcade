#include "funciones.h"

void Inicializar(){
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Fondo negro
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 20.0, -20.0, 20.0, -1.0, 1.0);
    generarEstrellas();  // Generar las estrellas al iniciar
    // Inicializar todos los disparos como inactivos
    for (int i = 0; i < MAX_DISPAROS; ++i) {
        disparos[i].activo = false;
    }
}

void Dibujar(){
    glClear(GL_COLOR_BUFFER_BIT);
    //planoCartesiano();
    dibujarEstrellas();
    naveespacial();
    asteroide();
    dibujarDisparos();
    // Dibujar puntaje
    glColor3f(1.0f, 1.0f, 1.0f);  // Color blanco
    glRasterPos2f(-18.0f, 18.0f);  // Posición del texto
    string puntajeStr = "Puntaje: " + to_string(puntaje);
    for (char c : puntajeStr) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);  // Fuente y tamaño del texto
    }

    // Dibujar vidas
    string vidasStr = "Vidas: " + to_string(vidas);
    glRasterPos2f(10.0f, 18.0f);  // Posición del texto
    for (char c : vidasStr) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);  // Fuente y tamaño del texto
    }

    glFlush();
}
