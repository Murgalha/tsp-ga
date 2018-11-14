#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <string> 
#include <iostream>

using namespace std;

int counter = 0;	// Contador de pontos criados na tela
int start = 0;		// Flag para indicar o comeco da execucao do algoritmo
int coord[20][2];	// Armazena os pontos

void keyPressEvent(unsigned char key, int x, int y) {
	if (key == 's')
		start = 1;

    glutPostRedisplay();
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
	int triangleAmount = 20; //# of triangles used to draw circle
	
	GLfloat twicePi = 2.0f * M_PI;
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); // center of circle
		for (int i = 0; i <= triangleAmount;i++) {
			glVertex2f(x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount)));
			
		}
	glEnd();
}


void drawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
    	glVertex2f(x1, y1);
    	glVertex2f(x2, y2);
	glEnd();
}

void OnMouseClick(int button, int state, int x, int y) {
	if (!start) {
		if (button == GLUT_LEFT_BUTTON && (state == GLUT_DOWN)) { 
	    	coord[counter][0] = x;
			coord[counter][1] = y;
			counter++;
			glutPostRedisplay();
		}
	}
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     
    for (int i = 0; i < counter; i++)
   			drawFilledCircle(coord[i][0], coord[i][1], 10);
    
    if (start) {
    	
    }
   	
    //drawFilledCircle(200, 200, 10);
    //drawLine(100, 100, 200, 200);
    glutSwapBuffers();
}

void setup() {
	int windowWidth = 800;
	int windowHeight = 800;

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Hello World");;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(0.0f, windowWidth, windowHeight, 0.0f, 0.0f, 1.0f);
	glutMouseFunc(OnMouseClick);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    setup();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPressEvent);
    glutMainLoop();

    return 0;
}