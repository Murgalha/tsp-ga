#include <cstring>
#include <cmath>
#include <cstdio>
#include "draw.h"
#include "utils.h"
#include "ui.h"
#include "tsp.h"

/* draw string on screen begining on pos (x, y) */
void drawText(char *string, GLint x, GLint y) {  
	char *c;
	glRasterPos2f(x, y);

	for(c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
}

/* draw a full circle on position clicked (x, y) */
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius) {
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

/* draw a straight line from point p1 to p2 */
void drawLine(Point p1, Point p2) {
    glBegin(GL_LINES);
    glVertex2f(p1.x(), p1.y());
    glVertex2f(p2.x(), p2.y());
    glEnd();
}

/* draw the full path from an individual
   of a population */
void drawPath(std::vector<int> person) {
    for(int i = 0; i < person.size(); i++) {
        drawLine(city[person[i%city.size()]], 
                city[person[(i+1)%city.size()]]);
    }
}

/* draw every generated path */
void drawAll() {
    /* if hide flag is not set, draw population path */
    if(!hide_population) {
        /* set color and draw path for every member */
        glColor3f(pop_color.r, pop_color.g, pop_color.b);
        for(int k = 0; k < population.size(); k++) {
            drawPath(population[k]);
        }
    }

    /* draw best path on a different color */
    glColor3f(best_color.r, best_color.g, best_color.b);
    drawPath(best);
}

/* draw number of generation on screen */
void drawGenerationHUD() {
    char generation[] = "Generation: ";
    char num[256];
    char result[256];

    /* clear memory and concatenate on result */
    memset(result, 0, 256);

    strcat(result, generation);

    /* put number on result string only
       if algorithm has not started yet */
    if(start) {
        sprintf(num, "%d", generation_counter);
        strcat(result, num);
    }

    /* set color and draw */
    glColor3f(fg_color.r, fg_color.g, fg_color.b);
    drawText(result, 20, WINDOW_HEIGHT-20);
}

/* draw command list on screen */
void drawCommandHUD() {
    char click[] = "Click - Set city";
    char hide[] = "H - Show/Hide population";
    char start[] = "S - Start simulation";
    char next[] = "N - Next generation";
    char reset[] = "R - Reset simulation";
    char quit[] = "Q - Quit simulation";

    /* draw command list on top right of the screen */
    glColor3f(fg_color.r, fg_color.g, fg_color.b);
    drawText(click, WINDOW_WIDTH - 450, 20);
    drawText(start, WINDOW_WIDTH - 450, 40);
    drawText(next, WINDOW_WIDTH - 450, 60);
    drawText(hide, WINDOW_WIDTH - 250, 20);
    drawText(reset, WINDOW_WIDTH - 250, 40);
    drawText(quit, WINDOW_WIDTH - 250, 60);
}

/* draw best distance on screen */
void drawDistanceHUD() {
    char dist[] = "Best Distance: ";
    char num[256];
    char result[256];

    memset(result, 0, 256);

    strcat(result, dist);

    /* draw number on screen only if simulation
       has not started yet */
    if(start) {
        sprintf(num, "%.3f", path_distance(best));
        strcat(result, num);
    }

    /* set color and draw resulting text */
    glColor3f(fg_color.r, fg_color.g, fg_color.b);
    drawText(result, 20, 20);
}

void drawCitiesHUD() {
    char cities[] = "Cities: ";
    char num[256];
    char result[256];

    memset(result, 0, 256);

    /* concatenate number of cities on result string */
    sprintf(num, "%lu", city.size());

    strcat(result, cities);
    strcat(result, num);

    /* set color and draw resulting text */
    glColor3f(fg_color.r, fg_color.g, fg_color.b);
    drawText(result, 20, 40);
}
