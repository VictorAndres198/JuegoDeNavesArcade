#include "funciones.h"

int main(int argc, char** argv){
    cout << "!!!Bienvenidos!!!" << endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Juego Arcade de Naves Espaciales");
    Inicializar();

    generarAsteroide();  // Generar la forma del asteroide una vez

    glutDisplayFunc(Dibujar);
    glutSpecialFunc(traslado);
    glutKeyboardFunc(teclado);  // Registrar la función de teclado para manejar las teclas presionadas

    glutTimerFunc(16, actualizarAsteroide, 0);  // Llamar a la función de actualización del asteroide cada 16 ms (~60 FPS)


    // Inicializar disparos y otros elementos
    for (int i = 0; i < MAX_DISPAROS; ++i) {
        disparos[i].activo = false;
    }

    // Configurar el temporizador para actualizar los disparos
    glutTimerFunc(0, actualizarDisparos, 0);

    glutMainLoop();
    return 0;
}
