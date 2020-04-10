#ifndef CHESS_H
#define CHESS_H

struct cells {
	float belief_prev; // belief state from previous action
	float belief_curr; // updated belief state from new action
	int numWalls; // 1 = 1 wall, 2 = 2 walls, 0 = terminal
	int col; // cell column
	int row; //  cell row
};

struct cells allCells[12];

void setBeliefState(char a, int e);
void initialize(int c, int r);
float getProbES(int col, int row, int e, int k);
float getProbSAS(int col, int row, char a, int k);
float getBeliefState(int col, int row);
int is_wall(col, row);
void normalize();



#endif
