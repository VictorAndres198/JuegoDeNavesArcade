#include "funciones.h"

void Inicializar(){
	glClearColor(0.0,0.0,0.0,1.0); /// FondoColor Negro
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-16.0,16.0,-16.0,16.0,-16.0,16.0);
}

void Dibujar(){
	glClear(GL_COLOR_BUFFER_BIT);
	planoCartesiano();
	naveespacial();
	//naveenemiga();
	glFlush();
}


