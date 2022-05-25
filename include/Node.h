// AUTHOR: Zamil Bahri

#ifndef NODE_H_
#define NODE_H_

#include "math.h"
#include <iostream>
#include "DEFINITIONS.h"

using namespace std;

class Node {

public:

	/* --- ATTRIBUTES --- */
	Node *parent = nullptr;
	int px;
	int py;
	int index;
	int maxCols; // need maxCols to convert to coordinates
	// Helpful reminder{0, 1, 2, 3} = {N, E, W, S}
	Node *neighbours[4] = { nullptr, nullptr, nullptr, nullptr };

	// Used in A*
	double G;
	double H;
	double F;

	/* --- METHODS --- */

	Node();
	~Node();
	Node(double G); // Mainly for testing
	Node(int x, int y, int maxCols);

	void PrintInfo();
	double ManhattanDistance(Node *goal); // Heuristic function
	double GetF();
	double DistanceFromNeighbour(int neighbourIndex);

	bool operator==(Node *other);
};

#endif
