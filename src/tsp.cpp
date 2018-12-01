#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <random>
#include <climits>
#include <fstream>
#include "point.h"
#include "utils.h"

/* generate random int from 0 to range-1 */
int randint(int range) {
    return (rand()%range);
}

/* generate random float from 0 to range */
float randfloat(float range) {
    return (rand()/(RAND_MAX*1.0))*range;
}

/* calculate euclidean distance between 2 points */
float euclidean_distance(Point p1, Point p2) {
    float square_dist = pow(p1.x()-p2.x(),2) + pow(p1.y()-p2.y(),2);
    return sqrt(square_dist);
}

void mutate(std::vector<int> person) {
    /* generate 2 random indexes to swap */
    int idxA = randint(city.size());
    int idxB = randint(city.size());

    /* keep generating random index while they are the same */
    /* to avoid no mutation at all */
    while(idxA == idxB)
        idxB = randint(city.size());

    /* swap elements */
    std::swap(person[idxA], person[idxB]);
}

std::vector<int> reproduce(std::vector<int> personA, std::vector<int> personB) {
    /* new generated individual */
    std::vector<int> personC;

    /* generate 2 indexes to copy from best */
    int start = randint(city.size());
    int end = start + 1 + randint(city.size()-start);
    
    /* copy best individual from start to end 
     * into the new individual */
    for(int j = start; j < end; j++)
        personC.push_back(personB[j]);
    
    std::vector<int>::iterator it;
    
    /* iterate through personA
    * if element at index 'i' is not on new individual, 
    * it is copied into personC */
    for(int i = 0; i < personA.size(); i++) {
        it = std::find(personC.begin(), personC.end(), personA[i]);
        if(it == personC.end())
            personC.push_back(personA[i]);
    }

    float randomf = randfloat(1);

    /* mutate new individual if random float is
     * less than MUT_CHANCE defined on command line argument */
    if(randomf <= MUT_CHANCE)
        mutate(personC);
    return personC;
}

/* get the distance of a full path from an individual */
float path_distance(std::vector<int> person) {
    float sum = 0;
    /* for each 2 points, get the euclidean distance between them */
    /* the '%' operator is used to get the distance between 
     * the last and the first city, closing the circuit*/
    for(int i = 0; i < person.size(); i++)
        sum += euclidean_distance(city[person[i%city.size()]],
                                  city[person[(i+1)%city.size()]]);
    return sum;
}

/* fitness is 1/path_distance to be 
 * an ascending curve */
float fitness(std::vector<int> person) {
    return 1/(path_distance(person)+1);
}

/* get the best fitness from a generation.
 * set the best on a global separate vector */
void set_best() {
    for(int i = 0; i < POP_SIZE; i++) {
        float aux_fitness = fitness(population[i]);
        
        if(fitness(population[i]) > best_fitness) {
            best = population[i];
            best_fitness = aux_fitness;
        }
    }
}

/* create a random generated population */
void init_population() {
    /* clear previous population and generate new one */
    for(int i = 0; i < POP_SIZE; i++) {
        population[i].clear();
        
        /* generate ordered vector and shuffle it */
        for(int j = 0; j < city.size(); j++) {
            population[i].push_back(j);
        }
        std::random_shuffle(population[i].begin(), population[i].end());
    }
}

/* write best distance on a file to be plotted later */
void write_best() {
    std::ofstream output;
    /* Filename = 'tsp_cities_population_mutation.data' */
    /* Data = generation    best_distance */
    std::string filename = "tsp_"+std::to_string(city.size())+"_"+
        std::to_string(POP_SIZE)+"_"+std::to_string(MUT_CHANCE)+".data";
    output.open(filename, std::ofstream::out | std::ofstream::app);
    output << generation_counter << "\t" << best_fitness << "\n";
}

/* function used to print best info on terminal */
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

/* print population info */
void print_pop() {
    for(int i = 0; i < POP_SIZE; i++) {
        for(int j = 0; j < population[i].size(); j++) {
            std::cout << " " << population[i][j];
        }
        std::cout << std::endl;
    }
}
