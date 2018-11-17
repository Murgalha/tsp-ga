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
    int idxA = randint(N_CITIES);
    int idxB = randint(N_CITIES);

    while(idxA == idxB)
        idxB = randint(N_CITIES);
    std::swap(person[idxA], person[idxB]);
}

std::vector<int> reproduce(std::vector<int> personA, std::vector<int> personB) {
    std::vector<int> personC(N_CITIES);
    int start = randint(N_CITIES);
    int end = start + 1 + randint(N_CITIES-start);
    
    std::copy(personB.begin()+start, personB.begin()+end, personC.begin());
    
    std::vector<int>::iterator it;
    
    for(int i = 0; i < N_CITIES; i++) {
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
    for(int i = 0; i < person.size()-1; i++)
        sum += euclidean_distance(city[person[i]],
                                  city[person[i+1]]);
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

void init_cities() {
    /* Init N_CITIES on random positions */
    for(int i = 0; i < N_CITIES; i++) {
        Point p(randint(20), randint(20));
        city.push_back(p);
    }
}

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
        if(i != N_CITIES-1)
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
