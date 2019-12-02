#include <string> 
#include <iostream>
#include "ui.h"
#include "draw.h"
#include "point.h"
#include "utils.h"
#include "tsp.h"

enum {
	DARK,
	LIGHT
};

/* start flag, initially set to false */
bool start = false;

/* generation counter */
int generation_counter = 1;

/* hide population draw flag, initially set to false */
bool hide_population = false;

int theme = DARK;

/* color variables for the theme */
color_t bg_color, fg_color, best_color, pop_color;

/* Light theme:
 * Background:      #FFFFFF
 * Foreground:      #000000
 * Best path:       #FF0000
 * Population path: #D8D8D8 */
void set_light_theme() {    
    /* set background to white and foreground to black */
    bg_color.r = bg_color.g = bg_color.b = 1.0f;
    fg_color.r = fg_color.g = fg_color.b = 0.0f;

    /* setting best path to red */
    best_color.r = 1.0f;
    best_color.g = best_color.b = 0.0f;

    /* set population color to light gray */
    pop_color.r = pop_color.g = pop_color.b = 0.843f;
}

/* Dark theme:
 * Background:      #000000
 * Foreground:      #FFFFFF
 * Best path:       #00FF00
 * Population path: #B2B2B2 */
void set_dark_theme() {
    /* set background to black and foreground to white */
    bg_color.r = bg_color.g = bg_color.b = 0.0f;
    fg_color.r = fg_color.g = fg_color.b = 1.0f;

    /* setting best path to green */
    best_color.r = 0.0f;
    best_color.g = 1.0f;
    best_color.b = 0.0;

    /* set population color to darkish gray */
    pop_color.r = pop_color.g = pop_color.b = 0.695f;    
}

void toggle_theme() {
    if(theme == DARK) {
        theme = LIGHT;
        set_light_theme();
    }
    else {
        theme = DARK;
        set_dark_theme();
    }
}

void keyPressEvent(unsigned char key, int x, int y) {
    /* S - start button */
    if (key == 's') {
        /* init population only if not already started
         * and set start flag */
        if(!start) {
            init_population();
            start = true;
        }
    }
    /* N - next generation */
    else if(key == 'n') {
        /* reproduce population with best individual
         * only if the game has already started 
         * increase generation counter */
        if(start) {
            for(int i = 0; i < POP_SIZE; i++)
                population[i] = reproduce(population[i], best);
            generation_counter++;
        }
    }
    /* H - toggle hide population draw flag*/
    else if(key == 'h')
        hide_population = !hide_population;

    /* R - reset simulation */
    else if(key == 'r') {
        /* reset every variable needed */
        generation_counter = 1;
        start = false;
        city.clear();
        for(int i = 0; i < POP_SIZE; i++)
            population[i].clear();
        best.clear();
        best_fitness = 0;
    }
    
    /* Q - Quit */
    else if(key == 'q')
        exit(0);

    /* T - Toggle theme */
    else if(key == 't')
        toggle_theme();

    glutPostRedisplay();
}

/* mouse click callback */
void OnMouseClick(int button, int state, int x, int y) {
    /* if simulation has not started, add clicked point to city vector */
    if (!start) {
        if (button == GLUT_LEFT_BUTTON && (state == GLUT_DOWN)) { 
            Point p(x, y);
            city.push_back(p);
            std::cout << "\nAdding ("<<p.x()<<", "<<p.y()<<")..."<<std::endl;
            glutPostRedisplay();
        }
    }
}

/* main draw callback function */
void display() {
    /* set background color based on the theme */
    glClearColor(bg_color.r, bg_color.g, bg_color.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* draw number of citites if vector not empty */
    if(city.size() > 0)
        drawCitiesHUD();

    /* draw info if simulation started */
    if (start) {
        std::cout << "\nGeneration: " << generation_counter << std::endl;
        /* print population info on terminal */
        print_pop();
        /* set best path */
        set_best();
        /* write  best distance on file to plot */
        write_best();
        /* draw every path */
        drawAll();
    }

    /* draw circles representing cities */
    for (int i = 0; i < city.size(); i++)
        drawFilledCircle(city[i].x(), city[i].y(), 10);

    /* draw best distance, command list 
       and generation counter on screen */
    drawDistanceHUD();
    drawCommandHUD();
    drawGenerationHUD();

    glutSwapBuffers();
}

/* window reshape callback */
void reshapeCallback(int width, int height) {
    /* set new viewport based on new window size */
    glViewport(0,0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluOrtho2D(0, width, height, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* set window size variables */
    WINDOW_HEIGHT = height;
    WINDOW_WIDTH = width;
    glutPostRedisplay();
}

void setup() {
    /* init program on dark theme */
    set_dark_theme();

    /* GLUT init functions */
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("TSP");

    /* setting color and projectin */
    glClearColor(bg_color.r, bg_color.g, bg_color.b, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f);

    /* set every callback needed */
    glutReshapeFunc(reshapeCallback);
    glutMouseFunc(OnMouseClick);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPressEvent);

    /* set draw depth function to most recent element 
       overlap the others */
    glDepthFunc(GL_NEVER);
}
