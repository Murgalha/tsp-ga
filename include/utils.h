#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include "point.h"

/* color struct with red, green and blue values */
typedef struct {
    GLfloat r, g, b;
} color_t;

extern float MUT_CHANCE;
extern int POP_SIZE;

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

extern bool start;
extern bool hide_population;
extern int generation_counter;
extern color_t bg_color, fg_color, best_color, pop_color;

extern std::vector<Point> city;
extern std::vector< std::vector<int> > population;
extern std::vector<int> best;
extern float best_fitness;

#endif
