#include "funciones.h"

float mover_x=0;
float mover_y=0;

float triangulo_x = 3.0;
float triangulo_y = 1.0;

void planoCartesiano(){
    glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_LINES);
		  glVertex2f(-10.0,0.0);
		  glVertex2f(10.0,0.0);
	glEnd();
	glBegin(GL_LINES);
			  glVertex2f(0.0,-10.0);
			  glVertex2f(0.0,10.0);
	glEnd();
}
void traslado(int key, int x, int y){
	switch (key)
	{
		case GLUT_KEY_RIGHT: mover_x++;break;
		case GLUT_KEY_LEFT: mover_x--;break;
		case GLUT_KEY_UP: mover_y++;break;
		case GLUT_KEY_DOWN: mover_y--;break;
	}
	glutPostRedisplay();
}

void naveespacial() {
	/*Alas de la nave principal*/
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(3.0, 2.0);
        glVertex2f(6.0, 2.0);
        glVertex2f(6.0, 4.0);
        glVertex2f(3.0, 4.0);
    glEnd();
    /*El cuerpo de la nave principal*/
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(4.0, 1.0);
        glVertex2f(5.0, 1.0);
        glVertex2f(5.0, 8.0);
        glVertex2f(4.0, 8.0);
    glEnd();
    /*Ventana de la nave principal*/
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
            glVertex2f(4.25, 2.0);
            glVertex2f(4.75, 2.0);
            glVertex2f(4.75, 5.0);
            glVertex2f(4.25, 5.0);
    glEnd();
}


/*
void naveenemiga(){
	    //El cuerpo de la nave enemiga
	    glColor3f(1.0f,0.0f,1.0f);
	    glBegin(GL_TRIANGLES);
	        glVertex2f(3.5, -1.0);
	        glVertex2f(7.5, -1.0);
	        glVertex2f(5.5, -6.5);
	        glVertex2f(4.5, -1.0);
	        glVertex2f(6.5, -1.0);
	        glVertex2f(5.5, -0.0);
	    glEnd();

	    //Las alas de la nave enemiga
	    glColor3f(1.0f, 1.0f, 0.0f);
	    glBegin(GL_TRIANGLES);
	    	glVertex2f(6.0, -1.0);
	    	glVertex2f(8.0, -1.0);
	    	glVertex2f(7.0, -3.5);

	    	glVertex2f(3.0, -1.0);
	        glVertex2f(5.0, -1.0);
	    	glVertex2f(4.0, -3.5);

	    	glVertex2f(6.5, -1.0);
	    	glVertex2f(7.5, -1.0);
	    	glVertex2f(7.0, -0.0);

	    	glVertex2f(3.5, -1.0);
	    	glVertex2f(4.5, -1.0);
	    	glVertex2f(4.0, -0.0);
	    glEnd();
	    //La ventana de la nave enemiga
	    glColor3f(0.0f, 0.0f, 1.0f);
	    glBegin(GL_QUADS);
	            glVertex2f(5.0, -2.0);
	            glVertex2f(6.0, -2.0);
	            glVertex2f(6.0, -4.0);
	            glVertex2f(5.0, -4.0);
	    glEnd();
}
*/
