#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>
#include "point.h"

extern float MUT_CHANCE;
extern int POP_SIZE;

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

extern std::vector<Point> city;
extern std::vector< std::vector<int> > population;
extern std::vector<int> best;
extern float best_fitness;

#endif
