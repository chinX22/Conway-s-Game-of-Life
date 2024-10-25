#include "cell.h"

// The only initializing need is to set every cell to dead
Cell::Cell(){
	alive = '.';
}

// Iterate through all grid neighbors and return the tally of live ones
unsigned char Cell::count_neighbors(){
	unsigned char numNeighbors = 0;	
	for (unsigned char i = 0; i < (unsigned char)neighbors.size(); i++){
		if (neighbors[i]->alive == '0'){
			numNeighbors++;
		}
	}
	return numNeighbors;
}

char Cell::check_rules(){
	unsigned char aliveNeighbors = count_neighbors();

	// If the cell is alive, less than 2 living neighbors causes death by
	// solitation, more than 3 neighbors causes death by overpopulation
	if (alive == '0'){
		if (aliveNeighbors > 3 || aliveNeighbors < 2){
			return '.';
		} else {
			return '0';
		}
	
	// If the cell is dead, it can be repopulated if it has 3 live neighbors
	} else {
		if (aliveNeighbors == 3){
			return '0';
		} else {
			return '.';
		}
	}
}


