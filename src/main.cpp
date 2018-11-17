#include <iostream>
#include "utils.h"
#include "tsp.h"
#include "ui.h"

std::vector<Point> city;
std::vector< std::vector<int> > population(POP_SIZE);
std::vector<int> best;
float best_fitness;

int main(int argc, char *argv[]) {
    int k = 1;
    srand(time(NULL));
    
    best_fitness = 0;
    
    glutInit(&argc, argv);
    setup();
    glutMainLoop();

    
    while(k <= N_GEN) {
        std::cout << "\nGeneration " << k << std::endl;
        set_best();
        
        for(int i = 0; i < POP_SIZE; i++)
            population[i] = reproduce(population[i], best);
        print_best();
        k++;
    }
}
