all:
	@g++ -o tsp src/*.cpp -Iinclude -lGL -lGLU -lglut
run:
	@./tsp
