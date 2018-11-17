#include <math.h>
#include <string> 
#include <iostream>
#include "ui.h"
#include "point.h"
#include "utils.h"
#include "tsp.h"

int start = 0;		// Flag para indicar o comeco da execucao do algoritmo
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 800;

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

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int i = 0; i < city.size(); i++)
        drawFilledCircle(city[i].x(), city[i].y(), 10);

    if (start) {
        init_population();
        set_best();
        print_pop();
        drawAll();
    }

    //drawFilledCircle(200, 200, 10);
    //drawLine(100, 100, 200, 200);
    glutSwapBuffers();
}

void setup() {
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800, 800);
    glutCreateWindow("TSP");;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f);

    glutMouseFunc(OnMouseClick);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPressEvent);
}
