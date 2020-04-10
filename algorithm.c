#include "algorithm.h"
#include <stdio.h>

// sets the new belief states of the cells
	// a = the action to perform (u=up,d=down,l=left,r=right)
	// e = observation (1=1 wall, 2=2 walls, 0 = terminal)
void setBeliefState(char a, int e) {
	float p_es = 0;
	float p_sas = 0;
	// iterate through the columns
	for (int i = 1; i <= 4; i++) {
		// iterate through the rows
		for (int j = 1; j <= 3; j++) {
			// don't evaluate the blank cell
				// going through the allCells struct to find the correct cell
				for (int k = 0; k < 12; k++) {
					if (allCells[k].col == i && allCells[k].row == j) {
						p_es = getProbES(i, j, e, k);
						p_sas = getProbSAS(i, j, a, k);
						allCells[k].belief_prev = allCells[k].belief_curr;
						allCells[k].belief_curr = p_es * p_sas;
					}
				}
		}
	}
	normalize();
}

// normalize all the belief states
void normalize() {
	float n = 0;
	for (int i = 0; i < 12; i++) {
		n += allCells[i].belief_curr;
	}
	for (int j = 0; j < 12; j++) {
		allCells[j].belief_curr = allCells[j].belief_curr / n;
	}
}

// helper function for setBeliefState
	// calculates P(e|s')
float getProbES(int col, int row, int e, int k) {
	return 1;
	/*
	if (e == 0) {
		if (allCells[k].col == 4 && (allCells[k].row == 2 || allCells[k].row == 3)) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		if (e == allCells[k].numWalls) {
			return .9;
		}
		else {
			return .1;
		}
	}*/
}

// helper function for setBeliefState
	// calculates Summation P(s'|a,s)b(s)
float getProbSAS(int col, int row, char a, int k) {
	float stay = 0; // calculates probability of staying in same cell after moving
	float up = 0;
	float down = 0;
	float left = 0;
	float right = 0;
	// action a moving up
	if (a == 'u') {
		// finding wall when going up one cell
		if (is_wall(col,row+1)) {
			stay += 0.8;
		}
		// finding wall moving left one cell
		if (is_wall(col - 1,row)) {
			stay += 0.1;
		}
		// otherwise, cell to the left
		else {
			left += 0.1*getBeliefState(col-1, row);
		}
		// finding wall moving right one cell
		if (is_wall(col + 1,row)) {
			stay += 0.1;
		}
		// otherwise, cell to the right
		else {
			right += 0.1 * getBeliefState(col+1, row);
		}
		// cell below 
		if (!is_wall(col ,row-1)) {
			down += 0.8 * getBeliefState(col, row-1);
		}
	}
	else if (a == 'd') {
		// finding wall when going down one cell
		if (is_wall(col,row-1)) {
			stay += 0.8;
		}
		// finding wall moving left one cell
		if (is_wall(col - 1,row)) {
			stay += 0.1;
		}
		// otherwise, cell to the left
		else {
			left += 0.1 * getBeliefState(col - 1, row);
		}
		// finding wall moving right one cell
		if (is_wall(col + 1,row)) {
			stay += 0.1;
		}
		// otherwise, cell to the right
		else {
			right += 0.1* getBeliefState(col+1, row);
		}
		// cell above 
		if (!is_wall(col,row+1)) {
			up += 0.8 * getBeliefState(col, row+1);
		}

	}
	else if (a == 'l') {
		// finding wall when going left one cell
		if (is_wall(col - 1, row)) {
			stay += 0.8;
		}
		// finding wall moving down one cell
		if (is_wall(col, row-1)) {
			stay += 0.1;
		}
		// otherwise, cell down
		else {
			down += 0.1 * getBeliefState(col, row-1);
		}
		// finding wall moving up one cell
		if (is_wall(col, row+1)) {
			stay += 0.1;
		}
		// otherwise, cell up
		else {
			up += 0.1* getBeliefState(col, row+1);
		}
		// cell to the right 
		if (!is_wall(col+1, row)) {
			right += 0.8 * getBeliefState(col+1, row);
		}
	}
	else {
		// finding wall when going right one cell
		if (is_wall(col + 1, row)) {
			stay += 0.8;
		}
		// finding wall moving down one cell
		if (is_wall(col, row - 1)) {
			stay += 0.1;
		}
		// otherwise, cell down
		else {
			down += 0.1 * getBeliefState(col, row - 1);
		}
		// finding wall moving up one cell
		if (is_wall(col, row + 1)) {
			stay += 0.1;
		}
		// otherwise, cell up
		else {
			up += 0.1 * getBeliefState(col, row + 1);
		}
		// cell to the left 
		if (!is_wall(col - 1, row)) {
			left += 0.8 * getBeliefState(col+1, row);
		}
	}

	stay = stay * getBeliefState(col, row);
	return stay + up + down + left + right;
}

// returns true if (col,row) cell is a wall
int is_wall(col, row) {
	if (col > 4 || col < 1 || row > 3 || row < 1 || (col == 2 && row == 2)) {
		return 1;
	}
	else {
		return 0;
	}
}

// returns the belief state from cell (col, row)
float getBeliefState(int col, int row) {
	//printf("\n");
	//printf("!(%d, %d):! ", col, row);
	for (int i = 0; i < 12; i++) {
		//printf("(%d, %d)", allCells[i].col, allCells[i].row);
		if (allCells[i].col == col && allCells[i].row == row) {
			return allCells[i].belief_prev;
		}
	}
}

// initialize the struct for allCells
	// if c == r == 0, then no start belief state
		// otherwise, start from (c,r)
void initialize(int c, int r) {
	int n = 0;
	// iterate through the columns
	for (int i = 1; i <= 4; i++) {
		// iterate through the rows
		for (int j = 1; j <= 3; j++) {
			// set up the terminal cells
			if (i == 4 && j == 2) {
				allCells[n].belief_curr = 0;
				allCells[n].belief_prev = 0;
				allCells[n].col = i;
				allCells[n].row = j;
				allCells[n].numWalls = 0;
				n++;
			}
			else if (i == 4 && j == 3) {
				allCells[n].belief_curr = 0;
				allCells[n].belief_prev = 0;
				allCells[n].col = i;
				allCells[n].row = j;
				allCells[n].numWalls = 0;
				n++;
			}
			// otherwise, set up non-terminal cells
			else {
				// initiate all belief states in a unifrom distribution
				if (c == 0 && r == 0) {
					allCells[n].belief_curr = 0.1111;
					allCells[n].belief_prev = 0.1111;
				}
				// othersise, set the cell (c,r) = 1, and rest 0 belief state
				else {
					if (i == c && j == r) {
						allCells[n].belief_curr = 1;
						allCells[n].belief_prev = 1;
					}
					else {
						allCells[n].belief_curr = 0;
						allCells[n].belief_prev = 0;
					}
				}
				// initialize the position of elements of allCells array struct
				allCells[n].col = i;
				allCells[n].row = j;
				// if in column 3, then 1 wall observation
				if (i == 3) {
					allCells[n].numWalls = 1;
				}
				// otherwise, the cells have 2-wall observation
				else {
					allCells[n].numWalls = 2;
				}
				n++;
			}
		}
	}
}