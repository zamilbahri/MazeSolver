// AUTHOR: Zamil Bahri and Jacob Steckler.
// - BFS() Jacob Steckler and Zamil Bahri
// - DFS()  Jacob Steckler and  Zamil Bahri
// - Rest: Zamil Bahri

#ifndef SOLVER_H_
#define SOLVER_H_

#include "Maze.h"
#include <list>
#include <queue>
#include <stack>

class Solver {
private:
	/* --- METHODS --- */
	void ReconstructPath(Node *cameFrom, Node *current);
	void Astar();
	void BFS();
	void DFS();

public:
	class Compare {
	public:
		bool operator() (Node *A, Node *B);
	};

	/* --- ATTRIBUTES --- */

	int width;
	Node *start;
	Node *end;
	list<Node*> path;

	int pathLength;
	int nodesExplored;

	/* --- METHODS --- */

	Solver();
	Solver(Node *start, Node *end);
	~Solver();

	void StartSolve(int method);

};

#endif
