#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <random>
#include <climits>
#include "point.h"
#include "utils.h"

int randint(int range) {
    return (rand()%range);
}

float randfloat(float range) {
    return (rand()/(RAND_MAX*1.0))*range;
}

float euclidean_distance(Point p1, Point p2) {
    return sqrt(pow(p1.x()-p2.x(),2) + pow(p1.y()-p2.y(),2));
}

void mutate(std::vector<int> person) {
    int idxA = randint(city.size());
    int idxB = randint(city.size());

    while(idxA == idxB)
        idxB = randint(city.size());
    std::swap(person[idxA], person[idxB]);
}

std::vector<int> reproduce(std::vector<int> personA, std::vector<int> personB) {
    std::vector<int> personC(city.size());
    int start = randint(city.size());
    int end = start + 1 + randint(city.size()-start);
    
    std::copy(personB.begin()+start, personB.begin()+end, personC.begin());
    
    std::vector<int>::iterator it;
    
    for(int i = 0; i < personA.size(); i++) {
        it = std::find(personC.begin(), personC.end(), personA[i]);
        if(it == personC.end())
            personC.push_back(personA[i]);
    }

    float randomf = randfloat(1);

    if(randomf <= MUT_CHANCE)
        mutate(personC);
    
    return personC;
}


float path_distance(std::vector<int> person) {
    float sum = 0;
    for(int i = 0; i < person.size(); i++)
        sum += euclidean_distance(city[person[i%city.size()]],
                                  city[person[(i+1)%city.size()]]);
    return sum;
}

float fitness(std::vector<int> person) {
    return 1/(path_distance(person)+1);
}

void set_best() {
    for(int i = 0; i < POP_SIZE; i++) {
        float aux_fitness = fitness(population[i]);
        
        if(fitness(population[i]) > best_fitness) {
            best = population[i];
            best_fitness = aux_fitness;
        }
    }
}

/* void init_cities() { */
/*     /1* Init N_CITIES on random positions *1/ */
/*     for(int i = 0; i < N_CITIES; i++) { */
/*         Point p(randint(20), randint(20)); */
/*         city.push_back(p); */
/*     } */
/* } */

void init_population() {
    /* Init random population */
    for(int i = 0; i < POP_SIZE; i++) {
        population[i].clear();
        for(int j = 0; j < city.size(); j++) {
            population[i].push_back(j);
        }
        std::random_shuffle(population[i].begin(), population[i].end());
    }
}

void print_best() {
    std::cout << "Best: ";
    for(int i = 0; i < best.size(); i++) {
        std::cout << best[i];
        if(i != best.size()-1)
            std::cout << ", ";
    }
    std::cout << std::endl;
    std::cout << "Path Distance: " << path_distance(best) << std::endl;
}

void print_pop() {
    for(int i = 0; i < POP_SIZE; i++) {
        for(int j = 0; j < population[i].size(); j++) {
            std::cout << " " << population[i][j];
        }
        std::cout << std::endl;
    }
}
