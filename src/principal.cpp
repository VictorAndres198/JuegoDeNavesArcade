#include "funciones.h"

#include <GL/glut.h>

int main(int argc, char** argv){
    std::cout << "!!!Bienvenidos!!!" << std::endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Juego Arcade de Naves Espaciales");
    Inicializar();

    generarAsteroides();  // Generar la forma de los asteroides una vez

    glutDisplayFunc(Dibujar);
    glutSpecialFunc(tecladoEspecial);  // Registrar función para teclas especiales
    glutSpecialUpFunc(liberarTeclaEspecial);  // Registrar función para liberar teclas especiales
    glutKeyboardFunc(teclado);  // Registrar función para teclas normales
    glutKeyboardUpFunc(liberarTecla);  // Registrar función para liberar teclas normales

    glutTimerFunc(16, actualizarAsteroide, 0);  // Llamar a la función de actualización de los asteroides cada 16 ms
    glutTimerFunc(16, actualizarEstrellas, 0);  // Timer para estrellas
    glutTimerFunc(16, actualizar, 0);  // Llamar a la función de actualización del juego cada 16 ms (~60 FPS)

    // Inicializar disparos y otros elementos
    for (int i = 0; i < MAX_DISPAROS; ++i) {
        disparos[i].activo = false;
    }

    // Configurar el temporizador para actualizar los disparos
    glutTimerFunc(0, actualizarDisparos, 0);

    glutMainLoop();
    return 0;
}
