#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>
#include "point.h"

#define MUT_CHANCE 0.2
#define N_GEN 100
#define POP_SIZE 10
#define N_CITIES 15

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

extern std::vector<Point> city;
extern std::vector< std::vector<int> > population;
extern std::vector<int> best;
extern float best_fitness;

#endif
