#include "algorithm.h"
#include <stdio.h>


int main() {
	int n = 5;

	// action, observation, c and r are the inputs
	char action[] = { 'l', 'l', 'l', 'l', 'l'};
	int observation[] = {2,2,2,2,2};
	int c = 0;
	int r = 0;

	initialize(c, r);
	
	for (int i = 1; i <= n; i++) {
		setBeliefState(action[i - 1], observation[i - 1]);
	}
	for (int j = 0; j < 12; j++) {
		printf("\n");
		printf("(%d, %d): %f", allCells[j].col, allCells[j].row, allCells[j].belief_curr);
	}
}
