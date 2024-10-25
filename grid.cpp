#include "grid.h"
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

Grid::Grid(int size) : size(size){
	initialize();
	deadGrid = false;
}

void Grid::initialize(){
	int area = size * size;
	cells.resize(area);
	for (int i = 0; i < area; i++){
		Cell* cell = new Cell();
		cells[i] = cell;
	}

	set_neighbors();
}

void Grid::set_neighbors(){
	for (int i = 0; i < cells.size(); i++){
		// Not on left edge
		if(i % size != 0){
			// Add left gridspace
			cells[i]->neighbors.push_back(cells[i-1]);
			// Not on top edge
			if(i >= size){
				// Add top-left gridspace
				cells[i]->neighbors.push_back(cells[i-size-1]);
			}
			// Not on bottom edge
			if (i < (size * (size - 1))){
				// Add bottom-left gridspace
				cells[i]->neighbors.push_back(cells[i+size-1]);
			}
		}

		// Not on right edge
		if((i + 1) % size != 0){
			// Add right gridspace
			cells[i]->neighbors.push_back(cells[i+1]);
			// Not on top edge
			if(i >= size){
				// Add top-right gridspace
				cells[i]->neighbors.push_back(cells[i-size+1]);
			}
			// Not on bottom edge
			if (i < (size * (size - 1))){
				// Add bottom-right gridspace
				cells[i]->neighbors.push_back(cells[i+size+1]);
			}
		}


		if(i >= size){
			// Add top gridspace
			cells[i]->neighbors.push_back(cells[i-size]);
		}
		if (i < (size * (size - 1))){
			// Add bottom gridspace
			cells[i]->neighbors.push_back(cells[i+size]);
		}
	}
}


/* Why are we using 2 grid objects as you will see in main as well?
*  If we see that the state of cell index i must turn from alive to dead
*  and we then modify that same grid as soon as we can, it will effect
*  the program's decision when it comes to the cell to thr right of i
*  or right below it. My way of getting past this is to take the objective
*  next change of each cell and send it to a 2nd grid in the same place.
*  This way, we won't sully the generation calculation as it happens.
*/
void Grid::update(Grid* otherGrid){
	bool anyAlive = false;
	for (int i = 0; i < cells.size(); i++){
		otherGrid->cells[i]->alive = cells[i]->check_rules();
		if (otherGrid->cells[i]->alive == '0'){
			anyAlive = true;
		}
	}

	if (anyAlive = false){
		deadGrid = true;
		otherGrid->deadGrid = true;
	}
}

void Grid::print(){
	for (int i = 0; i < cells.size(); i++){
		cout << cells[i]->alive << " ";
		if ((i + 1)%size == 0){
			cout << endl;
		}
	}
	cout << endl;
}

void Grid::random(int bodies, unsigned char neighbors){
	neighbors = neighbors - 1;
	int area = size * size;
	int cellIndex = 0;
	int neighborIndex = 0;
	srand(time(0));

	// Try to make a distinct number of living cells
	for (int i = 0; i < bodies; i++){
		int cellIndex = rand() % area;
		cells[cellIndex]->alive = '0';

		// Until reached given number, choose random neighbors to make alive
		for (int j = 0; j < cells[cellIndex]->neighbors.size(); j++){
			neighborIndex = rand() % cells[cellIndex]->neighbors.size();
			cells[cellIndex]->neighbors[neighborIndex]->alive = '0';
			if (j >= neighbors){
				break;
			}
		}
	}	
}

int Grid::find_middle(){
	if (size % 2 == 0){ // If even
		return ((size * size) - 1 - ((2 * size) / 3)) / 2;
	} else {	// If odd
		return ((size * size) - 1) / 2;
	}
}

void Grid::clock(){
	int mid = find_middle();
	cells[mid]->alive = '0';
	cells[mid - 1 - size]->alive = '0';
	
	cells[mid + size]->alive = '0';
	cells[mid - size + 1]->alive = '0';
	
	cells[mid - size - size + 1]->alive = '0';
	cells[mid + 2]->alive = '0';
}

void Grid::figure_eight(){
	int mid = find_middle();
	cells[mid]->alive = '0';	
	cells[mid - 1]->alive = '0';	
	cells[mid + 1]->alive = '0';	
	
	cells[mid - size]->alive = '0';	
	cells[mid - size - 1]->alive = '0';	
	cells[mid - size + 1]->alive = '0';	
	
	cells[mid + size]->alive = '0';	
	cells[mid + size - 1]->alive = '0';	
	cells[mid + size + 1]->alive = '0';	

	mid = mid + 3 + (size * 3);
	cells[mid]->alive = '0';	
	cells[mid - 1]->alive = '0';	
	cells[mid + 1]->alive = '0';	
	
	cells[mid - size]->alive = '0';	
	cells[mid - size - 1]->alive = '0';	
	cells[mid - size + 1]->alive = '0';	
	
	cells[mid + size]->alive = '0';	
	cells[mid + size - 1]->alive = '0';	
	cells[mid + size + 1]->alive = '0';	
}
