#include "funciones.h"

int main(int argc, char**argv){
	cout << "!!!Bienvenidos!!!" << endl;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(650,350);
	glutCreateWindow("Primera Ventana");
	Inicializar();
	glutDisplayFunc(Dibujar);
	glutSpecialFunc(traslado);
	glutMainLoop();
	return 0;
}
