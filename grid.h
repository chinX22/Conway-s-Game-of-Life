#ifndef GRID_H
#define GRID_H

#include "cell.h"
#include <vector>

class Grid{
	public:
		Grid(int);
		void initialize();	// Fill the grid with dead cells
		void update(Grid*); // Send the next frame to the other buffer grid
		void print();
		void set_neighbors();	// Sets the neighbor's list for each cell
		int find_middle();		// Find roughly the middle point of every grid
		void random(int, unsigned char);	// Random grid, takes # of bodies
		void clock();			// Test case, spinning clock hands
		void figure_eight();	// Test case, repeating pattern
		bool deadGrid;
	private:
		int size;	// Length and width of grid
		std::vector<Cell*> cells;	// Our vector of cells
};

#endif
