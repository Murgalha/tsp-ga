all:
	@g++ -O2 -o tsp src/*.cpp -Iinclude -lGL -lGLU -lglut -std=c++11
run:
	@echo "Usage: ./tsp <POPULATION SIZE> <MUTATION_CHANCE>"
