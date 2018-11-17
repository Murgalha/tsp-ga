#include <iostream>
#include "utils.h"
#include "tsp.h"
#include "ui.h"

std::vector<Point> city;
std::vector< std::vector<int> > population;
std::vector<int> best;
float best_fitness;
float MUT_CHANCE;
int POP_SIZE;


enum {
    PROGNAME,
    P_SIZE,
    M_CHANCE,
    NARGS
};

int main(int argc, char *argv[]) {
    if(argc != NARGS) {
        std::cout << "Usage: "<<argv[PROGNAME];
        std::cout << " <POPULATION SIZE> ";
        std::cout << "<MUTATION_CHANCE>\n";
        return 1;
    }

    POP_SIZE = atoi(argv[P_SIZE]);
    MUT_CHANCE = atof(argv[M_CHANCE]);

    population = std::vector< std::vector<int> >(POP_SIZE);

    srand(time(NULL));
    
    best_fitness = 0;
    
    glutInit(&argc, argv);
    setup();
    glutMainLoop();
}
