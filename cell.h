#ifndef CELL_H
#define CELL_H
#include <vector>

// Every square on our grid will be a living cell in the automata
class Cell{
	public:
		Cell();
		char alive;	// We'll use this to keep track if a cell is alive or nor
		std::vector<Cell*> neighbors;	// A list of all its grid neighbors
		unsigned char count_neighbors(); // Return how many alive neighbors
		char check_rules();	// Checks the rules for Conway's GoL
};

#endif
