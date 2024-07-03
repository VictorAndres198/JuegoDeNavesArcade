#include "funciones.h"
#include <cmath>
#include <cstdlib>
#include <cstring>  // Para memset

// PARTE DEL ASTEROIDE PARA DARLE UNA FORMA FIJA LUEGO DE CREARLO
#include <vector>
struct Vertice {
    float x, y;
};

struct Asteroide {
    vector<Vertice> vertices;
    float angulo;
    float mover_x;
    float mover_y;
    float velocidad_y;

    Asteroide() : angulo(0.0f), mover_x(0.0f), mover_y(20.0f), velocidad_y(0.0f) {}
};
std::vector<Asteroide> asteroides;
std::vector<Vertice> verticesAsteroide;

float angulo_asteroide = 0.0f;
float mover_x_asteroide = 10.0f;
float mover_y_asteroide = 20.0f;  // Inicializar el asteroide arriba de la pantalla
float velocidad_y_asteroide = 0.0f;  // Declarar la velocidad de bajada del asteroide
//****************************************************************************

// PARTE DE MOVIMIENTO
float mover_x = 0;
float mover_y = -15;
//// *****************


// ============ PARTE DE MOVIMIENTO FLUIDO ===============================
float velocidad_x = 0.0f;
float velocidad_y = 0.0f;
float aceleracion = 0.1f;  // Ajusta la aceleración según sea necesario
float desaceleracion = 0.05f;  // Ajusta la desaceleración según sea necesario
bool teclas[256];
bool teclasEspeciales[256];

//****************************************************************************

//============================== PARTE DE ESTRELLAS===============================
struct Estrella {
    float x, y;
    float velocidad_y;

    Estrella(float x, float y, float velocidad_y)
        : x(x), y(y), velocidad_y(velocidad_y) {}
};
std::vector<Estrella> estrellas;

void generarEstrellas() {
    estrellas.clear();
    srand(time(NULL));  // Semilla para generar números aleatorios

    int numEstrellas = rand() % 50 + 150;  // Generar entre 50 y 150 estrellas

    for (int i = 0; i < numEstrellas; ++i) {
        float x = -20.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (20.0f - (-20.0f))));
        float y = -20.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (20.0f - (-20.0f))));
        float velocidad_y = 0.17f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.05f - 0.02f)));

        estrellas.push_back(Estrella(x, y, velocidad_y));
    }
}


void dibujarEstrellas() {
    glColor3f(1.0f, 1.0f, 1.0f);  // Color blanco para las estrellas

    for (const auto& estrella : estrellas) {
        glPushMatrix();
        glTranslatef(estrella.x, estrella.y, 0.0f);
        glBegin(GL_POINTS);
            glVertex2f(0.0f, 0.0f);  // Dibuja un punto para representar la estrella
        glEnd();
        glPopMatrix();
    }
}

void actualizarEstrellas(int valor) {
    for (auto& estrella : estrellas) {
        estrella.y -= estrella.velocidad_y;

        // Si una estrella sale de la pantalla, se regenera arriba con una nueva posición x aleatoria
        if (estrella.y < -20.0f) {
            estrella.x = -20.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (20.0f - (-20.0f))));
            estrella.y = 20.0f;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, actualizarEstrellas, 0);  // Llamar de nuevo a esta función cada 16 ms (~60 FPS)
}


//============== PARTE DE DISPAROS =====================

Disparo disparos[MAX_DISPAROS];  // Arreglo de disparos

void dibujarDisparos() {
	glColor3f(0.5f, 0.0f, 0.5f);  // Color morado oscuro para los disparos

    for (int i = 0; i < MAX_DISPAROS; ++i) {
        if (disparos[i].activo) {
            glPushMatrix();
            glTranslatef(disparos[i].x, disparos[i].y, 0.0f);
            glBegin(GL_QUADS);
                glVertex2f(-0.1f, 0.0f);
                glVertex2f(0.1f, 0.0f);
                glVertex2f(0.1f, 0.5f);
                glVertex2f(-0.1f, 0.5f);
            glEnd();
            glPopMatrix();
        }
    }
}

void disparar() {
    for (int i = 0; i < MAX_DISPAROS; ++i) {
        if (!disparos[i].activo) {
            disparos[i].x = mover_x;  // Posición inicial del disparo en x (posición de la nave)
            disparos[i].y = mover_y + 2.8f;  // Posición inicial del disparo en y (posición de la nave)
            disparos[i].activo = true;
            break;
        }
    }
}
// parte de movimiento fluido
void teclado(unsigned char key, int x, int y) {
    teclas[key] = true;
}

void liberarTecla(unsigned char key, int x, int y) {
    teclas[key] = false;
}

void tecladoEspecial(int key, int x, int y) {
    teclasEspeciales[key] = true;
}

void liberarTeclaEspecial(int key, int x, int y) {
    teclasEspeciales[key] = false;
}

void actualizar(int valor) {
    // Movimiento más fluido de la nave
    if (teclasEspeciales[GLUT_KEY_RIGHT] && mover_x < 18.0f) mover_x += 0.5f;
    if (teclasEspeciales[GLUT_KEY_LEFT] && mover_x > -18.0f) mover_x -= 0.5f;
    if (teclasEspeciales[GLUT_KEY_UP] && mover_y < 16.5f) mover_y += 0.5f;
    if (teclasEspeciales[GLUT_KEY_DOWN] && mover_y > -19.0f) mover_y -= 0.5f;

    // Disparar cuando se presiona la barra espaciadora
    if (teclas[' ']) disparar();

    // Volver a dibujar la escena
    glutPostRedisplay();

    // Configurar la próxima llamada a esta función
    glutTimerFunc(16, actualizar, 0);  // Llamar de nuevo a esta función cada 16 ms (~60 FPS)
}

//*******************************************


void actualizarDisparos(int valor) {
    for (int i = 0; i < MAX_DISPAROS; ++i) {
        if (disparos[i].activo) {
            // Mover el disparo hacia arriba en el eje Y
            disparos[i].y += 1.0f;  // Ajusta la velocidad de movimiento hacia arriba según sea necesario

            // Verificar si el disparo ha salido de la pantalla
            if (disparos[i].y > 20.0f) {
                disparos[i].activo = false;  // Desactivar el disparo si sale de la pantalla
            } else {
                // Verificar colisión con los asteroides
                bool colision = false;
                for (auto& ast : asteroides) {
                    for (const auto& vertice : ast.vertices) {
                        // Calcular distancia al vértice del asteroide
                        float dx = disparos[i].x - (ast.mover_x + vertice.x);
                        float dy = disparos[i].y - (ast.mover_y + vertice.y);
                        float distancia = sqrt(dx * dx + dy * dy);

                        // Si la distancia es menor que un umbral, hay colisión
                        if (distancia < 1.0f) {  // Ajusta este umbral según el tamaño del asteroide
                            disparos[i].activo = false;  // Desactivar el disparo
                            colision = true;
                            // Aumentar el puntaje por destruir un asteroide
                            puntaje += 10;
                            break;  // Salir del bucle de vértices
                        }
                    }
                    if (colision) {
                        // Eliminar el asteroide de la lista
                        ast = asteroides.back();
                        asteroides.pop_back();
                        break;  // Salir del bucle de asteroides
                    }
                }
            }
        }
    }

    // Volver a dibujar la escena
    glutPostRedisplay();

    // Configurar la próxima llamada a esta función
    glutTimerFunc(16, actualizarDisparos, 0);  // Llamar de nuevo a esta función cada 16 ms (~60 FPS)
}


// *****************************************************************************************

// PARTE DE LAS VIDAS Y PUNTAJE
int puntaje = 0;
int vidas = 3;  // Inicializa con la cantidad de vidas que desees
// ***************************


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
    if (teclasEspeciales[GLUT_KEY_UP]) {
        glColor3f(1.0f, 0.7f, 0.0f);  // Amarillo (simula fuego o propulsión similar al sol)
    } else {
        glColor3f(0.0f, 0.0f, 0.0f);  // Negro (propulsor apagado)
    }
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.2f, -0.5f);
        glVertex2f(0.2f, -0.5f);
        glVertex2f(0.0f, -1.0f);
    glEnd();

    // Propulsor derecho
    if (teclasEspeciales[GLUT_KEY_UP]) {
        glColor3f(1.0f, 0.7f, 0.0f);  // Amarillo (simula fuego o propulsión similar al sol)
    } else if (teclasEspeciales[GLUT_KEY_LEFT]) {
        glColor3f(1.0f, 0.7f, 0.0f);  // Amarillo (simula fuego o propulsión similar al sol)
    } else {
        glColor3f(0.0f, 0.0f, 0.0f);  // Negro (propulsor apagado)
    }
    glBegin(GL_TRIANGLES);
        glVertex2f(0.4f, -0.5f);
        glVertex2f(0.7f, -0.5f);
        glVertex2f(0.55f, -1.0f);
    glEnd();

    // Propulsor izquierdo
    if (teclasEspeciales[GLUT_KEY_UP]) {
        glColor3f(1.0f, 0.7f, 0.0f);  // Amarillo (simula fuego o propulsión similar al sol)
    } else if (teclasEspeciales[GLUT_KEY_RIGHT]) {
        glColor3f(1.0f, 0.7f, 0.0f);  // Amarillo (simula fuego o propulsión similar al sol)
    } else {
        glColor3f(0.0f, 0.0f, 0.0f);  // Negro (propulsor apagado)
    }
    glBegin(GL_TRIANGLES);
         glVertex2f(-0.4f, -0.5f);
         glVertex2f(-0.7f, -0.5f);
         glVertex2f(-0.55f, -1.0f);
    glEnd();


    // Ventana en el centro
    glColor3f(0.7f, 0.9f, 1.0f);  // Azul claro
    glBegin(GL_QUADS);
        glVertex2f(-0.3f, 1.0f);
        glVertex2f(0.3f, 1.0f);
        glVertex2f(0.2f, 2.0f);
        glVertex2f(-0.2f, 2.0f);
    glEnd();


    // Ventanas en la parte inferior
    	glColor3f(0.6f, 0.6f, 0.6f);  // Azul claro
        glBegin(GL_QUADS);
            glVertex2f(-0.3f, -0.0f);
            glVertex2f(0.3f, -0.0f);
            glVertex2f(0.2f, -0.5f);
            glVertex2f(-0.2f, -0.5f);
        glEnd();

        glBegin(GL_QUADS);
            glVertex2f(-0.8f, -0.0f);
            glVertex2f(-0.3f, -0.0f);
            glVertex2f(-0.4f, -0.5f);
            glVertex2f(-0.7f, -0.5f);
        glEnd();

        glBegin(GL_QUADS);
            glVertex2f(0.8f, -0.0f);
            glVertex2f(0.3f, -0.0f);
            glVertex2f(0.4f, -0.5f);
            glVertex2f(0.7f, -0.5f);
        glEnd();

    glPopMatrix();
}



void asteroide() {
    for (const auto& ast : asteroides) {
        glPushMatrix();
        glTranslatef(ast.mover_x, ast.mover_y, 0.0f);
        glRotatef(ast.angulo, 0.0f, 0.0f, 1.0f);

        glColor3f(0.5f, 0.5f, 0.4f);  // Grisáceo con ligero tinte marrón
        glBegin(GL_POLYGON);
            for (const auto& vertice : ast.vertices) {
                glVertex2f(vertice.x, vertice.y);
            }
        glEnd();

        glPopMatrix();
    }
}

// Función para generar asteroides
void generarAsteroides() {
    asteroides.clear();
    int numAsteroides = rand() % 3 + 1;  // Generar entre 1 y 3 asteroides

    for (int i = 0; i < numAsteroides; ++i) {
        Asteroide nuevoAsteroide;

        // Generar una posición aleatoria en el eje x
        nuevoAsteroide.mover_x = -20.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (20.0f - (-20.0f))));
        nuevoAsteroide.mover_y = 20.0f;  // Restablecer la posición inicial del asteroide arriba de la pantalla
        nuevoAsteroide.velocidad_y = 0.15f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.3f - 0.15f)));  // Generar una velocidad de bajada aleatoria

        // Generar los vértices del asteroide
        for (int j = 0; j < 8; ++j) {
            float angle = 2.0f * M_PI * j / 8;
            float radius = 1.0f + (rand() % 100) / 100.0f * 0.5f; // Radio entre 1.0 y 1.5
            float x = radius * cos(angle);
            float y = radius * sin(angle);
            nuevoAsteroide.vertices.push_back({x, y});
        }

        asteroides.push_back(nuevoAsteroide);
    }
}

void actualizarAsteroide(int valor) {
    // Vector para almacenar asteroides que siguen activos
    std::vector<Asteroide> asteroidesActivos;

    for (auto& ast : asteroides) {
        // Mover el asteroide hacia abajo con la velocidad calculada
        ast.mover_y -= ast.velocidad_y;

        // Verificar colisión con la nave
        float distancia_nave_asteroide = sqrt(pow(mover_x - ast.mover_x, 2) + pow(mover_y - ast.mover_y, 2));
        if (distancia_nave_asteroide < 3.0f) {  // Ajusta este umbral según el tamaño de la nave y el asteroide
            vidas--;  // Reducir una vida
            // Eliminar el asteroide de la lista al colisionar con la nave
            continue;  // Salir del ciclo actual de asteroides y no agregarlo a la lista de activos
        }

        // Verificar si el asteroide está aún en la pantalla
        if (ast.mover_y > -20.0f) {
            asteroidesActivos.push_back(ast);  // Mantener el asteroide activo
        }
    }

    // Actualizar la lista de asteroides activos
    asteroides = asteroidesActivos;

    // Si no hay suficientes asteroides activos, generar más
    while (asteroides.size() < 3) {  // Genera hasta un máximo de 3 asteroides activos
        Asteroide nuevoAsteroide;
        // Configurar nuevo asteroide con posiciones y características aleatorias
        nuevoAsteroide.mover_x = -20.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (20.0f - (-20.0f))));
        nuevoAsteroide.mover_y = 20.0f;  // Comienza arriba de la pantalla
        nuevoAsteroide.velocidad_y = 0.15f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.3f - 0.15f)));

        // Generar los vértices del asteroide
        for (int j = 0; j < 8; ++j) {
            float angle = 2.0f * M_PI * j / 8;
            float radius = 1.0f + (rand() % 100) / 100.0f * 0.5f; // Radio entre 1.0 y 1.5
            float x = radius * cos(angle);
            float y = radius * sin(angle);
            nuevoAsteroide.vertices.push_back({x, y});
        }

        asteroides.push_back(nuevoAsteroide);
    }

    // Verificar si se han agotado las vidas
    if (vidas <= 0) {
        // Aquí puedes manejar el final del juego, reiniciar puntaje, vidas, etc.
        puntaje = 0;
        vidas = 3;
    }

    // Volver a dibujar la escena
    glutPostRedisplay();

    // Configurar la próxima llamada a esta función
    glutTimerFunc(16, actualizarAsteroide, 0);
}



