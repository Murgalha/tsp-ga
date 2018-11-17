#include <math.h>
#include <string> 
#include <iostream>
#include <cstring>
#include "ui.h"
#include "point.h"
#include "utils.h"
#include "tsp.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

int start = 0;		// Flag para indicar o comeco da execucao do algoritmo
int gen = 1;

void draw_text(char *string, GLint x, GLint y) {  
	char *c;
	glRasterPos2f(x, y);

	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

void keyPressEvent(unsigned char key, int x, int y) {
    if (key == 's') {
        if(!start) {
            init_population();
            start = 1;
        }
    }
    else if(key =='n') {
        if(start) {
            for(int i = 0; i < POP_SIZE; i++)
                population[i] = reproduce(population[i], best);
            gen++;
        }
    }
    glutPostRedisplay();
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
    int triangleAmount = 20;

    GLfloat twicePi = 2.0f * M_PI;
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);

    for (int i = 0; i <= triangleAmount;i++) {
        glVertex2f(x + (radius * cos(i *  twicePi / triangleAmount)), 
                y + (radius * sin(i * twicePi / triangleAmount)));

    }
    glEnd();
}

void drawLine(Point p1, Point p2) {
    glBegin(GL_LINES);
    glVertex2f(p1.x(), p1.y());
    glVertex2f(p2.x(), p2.y());
    glEnd();
}

void OnMouseClick(int button, int state, int x, int y) {
    if (!start) {
        if (button == GLUT_LEFT_BUTTON && (state == GLUT_DOWN)) { 
            Point p(x, y);
            city.push_back(p);
            std::cout << "Adding ("<<p.x()<<", "<<p.y()<<")..."<<std::endl;
            glutPostRedisplay();
        }
    }
}

void drawPath(std::vector<int> pop) {
    for(int i = 0; i < pop.size(); i++) {
        drawLine(city[pop[i%city.size()]], 
                city[pop[(i+1)%city.size()]]);
    }
}

void drawAll() {
    glColor3f(0.7f, 0.7f, 0.7f);
    for(int k = 0; k < population.size(); k++) {
        drawPath(population[k]);
    }

    glColor3f(1.0f, 0.0f, 0.0f);
    drawPath(best);
}

char *vector2buffer(std::vector<int> vector) {
    char *buffer = (char *) calloc (256, sizeof(char));

    for(int i = 0; i < vector.size(); i++) {
        sprintf(buffer+strlen(buffer), "%d ", vector[i]);
        if(i != vector.size()-1)
            sprintf(buffer+strlen(buffer), "- ");
    }

    return buffer;
}

char *generateDistanceHUD() {
    char *dist_buffer = (char *) calloc (50, sizeof(char));

    sprintf(dist_buffer, "Best Distance: %.3f\n", path_distance(best));

    return dist_buffer;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (start) {
        char *dist_buffer;
        std::cout << "\nGeneration: " << gen << std::endl;
        print_pop();
        set_best();
        drawAll();

        dist_buffer = generateDistanceHUD();
        glColor3f(1.0f, 1.0f, 1.0f);
        draw_text(dist_buffer, 20, 20);
    }
    
    for (int i = 0; i < city.size(); i++)
        drawFilledCircle(city[i].x(), city[i].y(), 10);

    glutSwapBuffers();
}

void setup() {
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("TSP");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f);

    glutMouseFunc(OnMouseClick);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPressEvent);
    
    glDepthFunc(GL_NEVER);
}

/* commented out for posterity */
/* char *generatePathHUD() { */
/*     char *path_buffer; */
/*     char *vec = vector2buffer(best); */

/*     path_buffer = (char *) calloc (12, sizeof(char)); // Size of 'Best Path: ' */
/*     strcpy(path_buffer, "Best Path: "); */
    
/*     path_buffer = (char *) realloc (path_buffer, sizeof(char)*(12+strlen(vec))); // Size of 'Best Path: ' */
/*     strcat(path_buffer, vec); */

/*     free(vec); */

/*     return path_buffer; */
/* } */
