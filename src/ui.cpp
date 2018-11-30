#include <math.h>
#include <string> 
#include <iostream>
#include <cstring>
#include "ui.h"
#include "point.h"
#include "utils.h"
#include "tsp.h"

typedef struct {
    GLfloat r, g, b;
} color_t;

int start = 0;		// Flag para indicar o comeco da execucao do algoritmo
int gen = 1;
bool hide_population = false;
color_t bg_color, fg_color, best_color, pop_color;

void drawText(char *string, GLint x, GLint y) {  
	char *c;
	glRasterPos2f(x, y);

	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

void set_light_theme() {    
    /* set background to black and foreground to white */
    bg_color.r = bg_color.g = bg_color.b = 1.0f;
    fg_color.r = fg_color.g = fg_color.b = 0.0f;

    /* setting best path to red */
    best_color.r = 1.0f;
    best_color.g = best_color.b = 0.0f;

    pop_color.r = pop_color.g = pop_color.b = 0.85f;
}

void set_dark_theme() {
    /* set background to black and foreground to white */
    bg_color.r = bg_color.g = bg_color.b = 0.0f;
    fg_color.r = fg_color.g = fg_color.b = 1.0f;

    /* setting best path to green */
    best_color.r = 0.0f;
    best_color.g = 1.0f;
    best_color.b = 0.0;

    pop_color.r = pop_color.g = pop_color.b = 0.7f;    
}

void keyPressEvent(unsigned char key, int x, int y) {
    if (key == 's') {
        if(!start) {
            init_population();
            start = 1;
        }
    }
    else if(key == 'n') {
        if(start) {
            for(int i = 0; i < POP_SIZE; i++)
                population[i] = reproduce(population[i], best);
            gen++;
        }
    }
    else if(key == 'h') {
        hide_population = !hide_population;
    }
    else if(key == 'r') {
        gen = 1;
        start = 0;
        city.clear();
        for(int i = 0; i < POP_SIZE; i++)
            population[i].clear();
        best.clear();
        best_fitness = 0;
    }
    else if(key == 'q') {
        exit(0);
    }
    else if(key == '1') {
        set_dark_theme();
    }
    else if(key == '2') {
        set_light_theme();
    }

    glutPostRedisplay();
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
    int triangleAmount = 20;

    GLfloat twicePi = 2.0f * M_PI;
    glColor3f(fg_color.r, fg_color.g, fg_color.b);
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
            std::cout << "\nAdding ("<<p.x()<<", "<<p.y()<<")..."<<std::endl;
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
    if(!hide_population) {
        glColor3f(pop_color.r, pop_color.g, pop_color.b);
        for(int k = 0; k < population.size(); k++) {
            drawPath(population[k]);
        }
    }

    glColor3f(best_color.r, best_color.g, best_color.b);
    drawPath(best);
}

void printGenerationHUD() {
    char generation[] = "Generation: ";
    char num[256];
    char result[256];
    
    memset(result, 0, 256);

    strcat(result, generation);

    if(start) {
        sprintf(num, "%d", gen);
        strcat(result, num);
    }

    glColor3f(fg_color.r, fg_color.g, fg_color.b);
    drawText(result, 20, WINDOW_HEIGHT-20);
}

void printCommandHUD() {
    char click[] = "Click - Set city";
    char hide[] = "H - Show/Hide population";
    char start[] = "S - Start simulation";
    char next[] = "N - Next generation";
    char reset[] = "R - Reset simulation";
    char quit[] = "Q - Quit simulation";
    
    glColor3f(fg_color.r, fg_color.g, fg_color.b);
    drawText(click, WINDOW_WIDTH - 450, 20);
    drawText(start, WINDOW_WIDTH - 450, 40);
    drawText(next, WINDOW_WIDTH - 450, 60);
    drawText(hide, WINDOW_WIDTH - 250, 20);
    drawText(reset, WINDOW_WIDTH - 250, 40);
    drawText(quit, WINDOW_WIDTH - 250, 60);
}

void printDistanceHUD() {
    char dist[] = "Best Distance: ";
    char num[256];
    char result[256];

    memset(result, 0, 256);

    strcat(result, dist);
    
    if(start) {
        sprintf(num, "%.3f", path_distance(best));
        strcat(result, num);
    }

    glColor3f(fg_color.r, fg_color.g, fg_color.b);
    drawText(result, 20, 20);
}

void printCitiesHUD() {
    char cities[] = "Cities: ";
    char num[256];
    char result[256];

    memset(result, 0, 256);

    sprintf(num, "%lu", city.size());

    strcat(result, cities);
    strcat(result, num);
    
    glColor3f(fg_color.r, fg_color.g, fg_color.b);
    drawText(result, 20, 40);
}

void display() {
    glClearColor(bg_color.r, bg_color.g, bg_color.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(city.size() > 0)
        printCitiesHUD();

    if (start) {
        char *dist_buffer;
        std::cout << "\nGeneration: " << gen << std::endl;
        print_pop();
        set_best();
        drawAll();
    }
    
    for (int i = 0; i < city.size(); i++)
        drawFilledCircle(city[i].x(), city[i].y(), 10);

    printDistanceHUD();
    printCommandHUD();
    printGenerationHUD();

    glutSwapBuffers();
}

void reshapeCallback(int width, int height) {
    glViewport(0,0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, height, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    WINDOW_HEIGHT = height;
    WINDOW_WIDTH = width;
    glutPostRedisplay();
}

void setup() {
    set_dark_theme();
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("TSP");

    glClearColor(bg_color.r, bg_color.g, bg_color.b, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f);

    glutReshapeFunc(reshapeCallback);
    glutMouseFunc(OnMouseClick);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPressEvent);
    
    glDepthFunc(GL_NEVER);
}
