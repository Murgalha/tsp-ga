#ifndef _TSP_H_
#define _TSP_H_

#include "point.h"
#include "utils.h"

int randint(int);
float randfloat(float);
float euclidean_distance(Point, Point);
void mutate(std::vector<int>);
std::vector<int> reproduce(std::vector<int>, std::vector<int>);
float path_distance(std::vector<int>);
float fitness(std::vector<int>);
void set_best();
void init_population();
void write_best();
void print_best();
void print_pop();

#endif
