#include "funciones.h"
#include <cmath>
#include <cstdlib>

// PARTE DEL ASTEROIDE PARA DARLE UNA FORMA FIJA LUEGO DE CREARLO
#include <vector>

struct Vertice {
    float x, y;
};

std::vector<Vertice> verticesAsteroide;
// HASTA ACA ES LA PARTE DEL ASTEROIDE



float mover_x = 0;
float mover_y = -15;



float angulo_asteroide = 0.0f;

float mover_x_asteroide = 10.0f;
float mover_y_asteroide = 20.0f;  // Inicializar el asteroide arriba de la pantalla


float velocidad_y_asteroide = 0.0f;  // Declarar la velocidad de bajada del asteroide

void planoCartesiano(){
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_LINES);
        glVertex2f(-20.0, 0.0);
        glVertex2f(20.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
        glVertex2f(0.0, -20.0);
        glVertex2f(0.0, 20.0);
    glEnd();
}

void traslado(int key, int x, int y){
    switch (key)
    {
        case GLUT_KEY_RIGHT: mover_x += 1.0f; break;
        case GLUT_KEY_LEFT: mover_x -= 1.0f; break;
        case GLUT_KEY_UP: mover_y += 1.0f; break;
        case GLUT_KEY_DOWN: mover_y -= 1.0f; break;
    }
    glutPostRedisplay();
}

void naveespacial() {
    glPushMatrix();
    glTranslatef(mover_x, mover_y, 0);

    // Cuerpo principal más delgado de color azul
    glColor3f(0.2f, 0.3f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(-0.8f, 0.0f);
        glVertex2f(0.8f, 0.0f);
        glVertex2f(0.6f, 3.0f);
        glVertex2f(-0.6f, 3.0f);
    glEnd();

    // Ala izquierda
    glColor3f(0.6f, 0.6f, 0.6f);  // Gris oscuro o plata
    glBegin(GL_TRIANGLES);
        glVertex2f(-2.2f, -0.5f);
        glVertex2f(-0.73f, 1.0f);
        glVertex2f(-0.666f, 2.0f);
    glEnd();

    // Ala derecha
    glBegin(GL_TRIANGLES);
        glVertex2f(2.2f, -0.5f);
        glVertex2f(0.73f, 1.0f);
        glVertex2f(0.666f, 2.0f);
    glEnd();

    // Parte frontal triangular
    glColor3f(0.0f, 0.5f, 1.0f);  // Azul claro brillante
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.6f, 3.0f);
        glVertex2f(0.6f, 3.0f);
        glVertex2f(0.0f, 3.3f);
    glEnd();

    // Propulsor medio
    glColor3f(0.0f, 0.5f, 1.0f);  // Azul claro brillante
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.3f, 0.0f);
        glVertex2f(0.3f, 0.0f);
        glVertex2f(0.0f, -0.5f);
    glEnd();
    // Propulsor derecho
    glBegin(GL_TRIANGLES);
        glVertex2f(0.3f, 0.0f);
        glVertex2f(0.8f, 0.0f);
        glVertex2f(0.55f, -0.5f);
    glEnd();
    // Propulsor izquierdo
    glBegin(GL_TRIANGLES);
         glVertex2f(-0.3f, 0.0f);
         glVertex2f(-0.8f, 0.0f);
         glVertex2f(-0.55f, -0.5f);
    glEnd();


    // Ventana en el centro
    glColor3f(0.7f, 0.9f, 1.0f);  // Azul claro
    glBegin(GL_QUADS);
        glVertex2f(-0.3f, 1.0f);
        glVertex2f(0.3f, 1.0f);
        glVertex2f(0.2f, 2.0f);
        glVertex2f(-0.2f, 2.0f);
    glEnd();

    glPopMatrix();

}




void asteroide(){
    glPushMatrix();
    glTranslatef(mover_x_asteroide, mover_y_asteroide, 0.0f);
    glRotatef(angulo_asteroide, 0.0f, 0.0f, 1.0f);

    glColor3f(0.5f, 0.5f, 0.4f);  // Grisáceo con ligero tinte marrón
    glBegin(GL_POLYGON);
        for (const auto& vertice : verticesAsteroide) {
            glVertex2f(vertice.x, vertice.y);
        }
    glEnd();

    glPopMatrix();
}


void generarAsteroide() {
    verticesAsteroide.clear();

    // Generar una posición aleatoria en el eje x
    mover_x_asteroide = -20.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (20.0f - (-20.0f))));

    // Restablecer la posición inicial del asteroide arriba de la pantalla
    mover_y_asteroide = 20.0f;

    // Generar una velocidad de bajada aleatoria entre 0.15f y 0.3f
    velocidad_y_asteroide = 0.15f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.3f - 0.15f)));

    // Generar los vértices del asteroide
    for(int i = 0; i < 8; ++i) {
        float angle = 2.0f * M_PI * i / 8;
        float radius = 1.0f + (rand() % 100) / 100.0f * 0.5f; // Radio entre 1.0 y 1.5
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        verticesAsteroide.push_back({x, y});
    }
}



void actualizarAsteroide(int valor) {
    // Mover el asteroide hacia abajo con la velocidad calculada
    mover_y_asteroide -= velocidad_y_asteroide;

    // Cuando el asteroide sale de la pantalla, restablecer su posición
    if (mover_y_asteroide < -20.0f) {
        // Regenerar el asteroide y su velocidad
        generarAsteroide();
    }

    // Incrementar el ángulo de rotación del asteroide
    angulo_asteroide += 0.5f;  // Ajusta la velocidad de rotación según lo necesites

    // Volver a dibujar la escena
    glutPostRedisplay();

    // Configurar la próxima llamada a esta función
    glutTimerFunc(16, actualizarAsteroide, 0);
}






