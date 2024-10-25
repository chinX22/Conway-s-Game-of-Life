#include "grid.h"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string>

using namespace std;

int main(int argc, char* argv[]){

	int size = atoi(argv[2]);
	if (size < 3 && size != 0){
		cout << "Bad size!" << endl;
		return -1;
	}
	
	size = (size == 0) ? 21 : size;
	Grid* buffer1 = new Grid(size);

	string operation = argv[1];
	if (operation.compare("random") == 0){
		int numBodies = atoi(argv[3]);
		buffer1->random(numBodies, 3);
	} else if (operation.compare("clock") == 0){
		buffer1->clock();
	} else if (operation.compare("figure_eight") == 0){
		buffer1->figure_eight();
	} else {
		cout << "Usage: a.out operation size(0 for default of) " << 
			" (number of bodies if using random)"
			<< endl;
		cout << "Examples: ./a.out clock 25   ./a.out random 25 9" << endl;
		return -1;
	}

	Grid* buffer2 = new Grid(size);

	// Here is our driving loop, print a generation, send the data to the
	// other buffer, rinse and repeate
	while(true){
		// Clears the terminal and sets cursor to the top left
		cout << "\033[2J\033[H";
		buffer1->update(buffer2);
		buffer2->print();
		sleep(1);

		cout << "\033[2J\033[H";
		buffer2->update(buffer1);
		buffer1->print();
		sleep(1);

		if (buffer1->deadGrid || buffer2->deadGrid){
			break;
		}
	}
}
