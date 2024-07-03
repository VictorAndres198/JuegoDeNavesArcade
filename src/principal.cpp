#include "funciones.h"
#include <GL/glut.h>

int main(int argc, char** argv){
    cout << "!!!Bienvenidos!!!" << endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Juego Arcade de Naves Espaciales");
    Inicializar();
    glutDisplayFunc(Dibujar);
    glutSpecialFunc(traslado);
//  glutKeyboardFunc(Disparo);
    glutMainLoop();
    return 0;
}
