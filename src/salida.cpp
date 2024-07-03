#include "funciones.h"
#include <vector>  // Incluimos la cabecera vector
#include <algorithm>  // Incluimos la cabecera algorithm

float mover_x = 0;
float mover_y = -15;

float angulo = 0.0f;

//vector<Proyectil> proyectiles;
//vector<Asteroide> asteroides;

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

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-1.5f, 1.0f);
        glVertex2f(1.5f, 1.0f);
        glVertex2f(1.5f, 2.0f);
        glVertex2f(-1.5f, 2.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.5f, 0.0f);
        glVertex2f(0.5f, 0.0f);
        glVertex2f(0.5f, 4.0f);
        glVertex2f(-0.5f, 4.0f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.25f, 2.5f);
        glVertex2f(0.25f, 2.5f);
        glVertex2f(0.25f, 3.5f);
        glVertex2f(-0.25f, 3.5f);
    glEnd();

    glPopMatrix();
}

void asteroide(){
    glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
		glVertex2f(-1.0f, -1.0f);
		glVertex2f(1.0f, -1.0f);
		glVertex2f(1.0f, 1.0f);
		glVertex2f(-1.0f, 1.0f);
	glEnd();
}

/*
void Disparo(unsigned char key, int x, int y) {
    if (key == 32) {  // Tecla de espacio
        CrearProyectil();
    }
}

void CrearProyectil() {
    Proyectil nuevoProyectil;
    nuevoProyectil.x = mover_x;
    nuevoProyectil.y = mover_y + 4.0f;  // La posición inicial del proyectil
    proyectiles.push_back(nuevoProyectil);
}

void MoverProyectiles() {
    glColor3f(1.0f, 1.0f, 0.0f);
    for (auto& proyectil : proyectiles) {
        proyectil.y += 0.1f;
        glBegin(GL_QUADS);
            glVertex2f(proyectil.x - 0.1f, proyectil.y);
            glVertex2f(proyectil.x + 0.1f, proyectil.y);
            glVertex2f(proyectil.x + 0.1f, proyectil.y + 0.5f);
            glVertex2f(proyectil.x - 0.1f, proyectil.y + 0.5f);
        glEnd();
    }
    glutPostRedisplay();
}

void CrearAsteroide() {
    Asteroide nuevoAsteroide;
    nuevoAsteroide.x = (rand() % 40) - 20;
    nuevoAsteroide.y = 20.0f;
    nuevoAsteroide.angulo = 0.0f;
    asteroides.push_back(nuevoAsteroide);
}

void MoverAsteroides() {
    glColor3f(0.5f, 0.5f, 0.5f);
    for (auto& asteroide : asteroides) {
        asteroide.y -= 0.05f;
        asteroide.angulo += 1.0f;
        glPushMatrix();
        glTranslatef(asteroide.x, asteroide.y, 0);
        glRotatef(asteroide.angulo, 0, 0, 1);
        glBegin(GL_QUADS);
            glVertex2f(-1.0f, -1.0f);
            glVertex2f(1.0f, -1.0f);
            glVertex2f(1.0f, 1.0f);
            glVertex2f(-1.0f, 1.0f);
        glEnd();
        glPopMatrix();
    }
    glutPostRedisplay();
}

void DibujarExplosión(float x, float y) {
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(x - 0.5f, y - 0.5f);
        glVertex2f(x + 0.5f, y - 0.5f);
        glVertex2f(x + 0.5f, y + 0.5f);
        glVertex2f(x - 0.5f, y + 0.5f);
    glEnd();
}

void CheckCollisions() {
    for (auto itP = proyectiles.begin(); itP != proyectiles.end(); ++itP) {
        for (auto itA = asteroides.begin(); itA != asteroides.end(); ++itA) {
            if (itP->x > itA->x - 1.0f && itP->x < itA->x + 1.0f &&
                itP->y > itA->y - 1.0f && itP->y < itA->y + 1.0f) {
                // Si hay una colisión
                DibujarExplosión(itA->x, itA->y);
                itA = asteroides.erase(itA);  // Eliminar asteroide
                itP = proyectiles.erase(itP);  // Eliminar proyectil
                break;  // Salir del bucle interior para evitar invalidar el iterador
            }
        }
    }

    // Eliminar proyectiles que están fuera de la pantalla
    proyectiles.erase(
        remove_if(proyectiles.begin(), proyectiles.end(), [](const Proyectil& p) { return p.y > 20.0f; }),
        proyectiles.end()
    );

    // Eliminar asteroides que están fuera de la pantalla
    asteroides.erase(
        remove_if(asteroides.begin(), asteroides.end(), [](const Asteroide& a) { return a.y < -20.0f; }),
        asteroides.end()
    );

    glutPostRedisplay();
}
*/
