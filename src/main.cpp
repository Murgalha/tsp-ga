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

/* Initial window size */
int WINDOW_HEIGHT = 800;
int WINDOW_WIDTH = 800;

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

    /* setting population size and mutation chance 
     * from command line argument */
    POP_SIZE = atoi(argv[P_SIZE]);
    MUT_CHANCE = atof(argv[M_CHANCE]);

    population = std::vector< std::vector<int> >(POP_SIZE);

    /* set rand seed to avoid repeated numbers */
    srand(time(NULL));
    
    best_fitness = 0;
    
    glutInit(&argc, argv);

    /* setup all data from window and algorithm */
    setup();
    glutMainLoop();
}
