// AUTHOR: Zamil Bahri

// This class sets up the graph for the maze by linking
// several nodes between "start" and "end" through pointers

#ifndef MAZE_H_
#define MAZE_H_

#include "Node.h"

class Maze {
public:
	
	/* --- ATTRIBUTES --- */

	bool *data;
	int width;
	int height;
	int numNodes;
	Node *start;
	Node *end;

	/* --- METHODS --- */
	Maze();
	~Maze();
	Maze(bool *data, int width);
	
};

#endif