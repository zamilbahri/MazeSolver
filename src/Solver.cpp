#include "../include/Solver.h"

Solver::Solver() {
	return;
}

Solver::Solver(Node *start, Node *end) {
	this->width = start->maxCols;
	this->start = start;
	this->end = end;
	this->nodesExplored = 0;
	this->pathLength = 0;
	return;
}

Solver::~Solver() {
	return;
}

// Custom comparison operator for priority_queue in AStar()
bool Solver::Compare::operator() (Node *A, Node *B) {
	if (A->F > B->F) {
		return true;
	}
	return false;
}

void Solver::ReconstructPath(Node *cameFrom, Node *current) {
	while (cameFrom != nullptr) {
		++pathLength;
		this->path.push_front(current);
		current = current->parent;
		cameFrom = cameFrom->parent;
	}
	this->path.push_front(start);
	++pathLength;
}

// Examine each layer of nodes before going to the next layer
void Solver::BFS() {

	int total = width * width;

	queue<Node*> openList;

	// Holds the indices of all nodes that have already been evaluated
	bool *closedList = new bool[total] {false};

	Node *cur = nullptr;

	openList.push(start);
	closedList[start->index] = true;

	while (!openList.empty()) {
		++nodesExplored;
		cur = openList.front();
		openList.pop();

		if (cur == end) {
			ReconstructPath(cur->parent, end);
			break;
		}

		Node *n = nullptr;
		for (int i = 0; i < 4; ++i) {
			n = cur->neighbours[i];

			if (n == nullptr) {
				continue;
			}

			if (closedList[n->index]) {
				continue;
			}

			closedList[n->index] = true;
			n->parent = cur;
			openList.push(n);
		}
	}
	delete[] closedList;
}

// Examine all children of a certain node before examining the next one
void Solver::DFS() {
	int total = width * width;

	stack<Node*> openList;

	// Holds the indices of all nodes that have already been evaluated
	bool *closedList = new bool[total] {false};

	Node *cur = nullptr;

	openList.push(start);
	closedList[start->index] = true;

	while (!openList.empty()) {
		++nodesExplored;

		cur = openList.top();
		openList.pop();

		if (cur == end) {
			ReconstructPath(cur->parent, end);
			break;
		}
		
		Node *n = nullptr;
		for (int i = 0; i < 4; ++i) {
			n = cur->neighbours[i];

			if (n == nullptr) {
				continue;
			}

			if (closedList[n->index]) {
				continue;
			}

			closedList[n->index] = true;
			n->parent = cur;
			openList.push(n);
		}
	}
	delete[] closedList;
}

// Keeps track of distance from start and end to decide which
//	node to examine next.
// Note: It works, but doesn't necessarily return shortest path
void Solver::Astar() {
	int total = width * width;

	// Holds all nodes that are currently under consideration.
	// Sorts by F-value for quicker access
	priority_queue<Node*, vector<Node*>, Compare> openList;
	if (USE_DEFAULT_COMPARISON) {
		priority_queue<Node*> openList;
	}

	// Holds the indices of all nodes that have already been evaluated
	//	Reason for not having a "visited" attribute is because of multiple
	//	algorithms conflicting with each other if ran in the same program launch.
	bool *closedList = new bool[total] {false};

	//This index holds all priority queue nodes as they are created. 
	bool *inOpenList = new bool[total] {false};

	// To begin, set the distance from start to 0 (we're there) and add to openList
	start->G = 0;
	start->H = start->ManhattanDistance(end);
	inOpenList[start->index] = true;
	openList.push(start);

	Node *cur = nullptr;

	// while openList is not empty (if empty, then no path)
	while (!openList.empty()) {

		++nodesExplored;

		// Set cur to node at the top of openList
		// Remove said node from openList and to closedList
		cur = openList.top();
		openList.pop();
		closedList[cur->index] = true;

		// if end is reached
		if (cur == end) {
			ReconstructPath(cur->parent, end);
			if (ASTAR_SEARCH_ALL_NODES == false) break;
		}

		// evaluate each neighbour
		for (int i = 0; i < 4; ++i) {
			Node *n = cur->neighbours[i];

			// if this neighbour is nullptr
			if (n == nullptr) {
				continue;
			}

			// If node is in closed list
			if (closedList[n->index]) {
				continue;
			}

			// Calculate G(n) = distance from start
			//				  = d(cur, start) + d(n, cur)
			int newCost = n->DistanceFromNeighbour(3 - i);
			double tempG = cur->G + newCost;

			// Compare tempG to existing G cost
			// That is, if a shorter path to current node exists from start
			if (!inOpenList[n->index]) {
				openList.push(n);
				inOpenList[n->index] = true;
			}
			else if (tempG >= n->G) {
				continue;
			}

			// Past if-statements: This is the best path until now!

			n->parent = cur; // Set the parent of this node to cur
			n->H = n->ManhattanDistance(end); // Heuristic cost

			n->F = n->G + n->H;
		}
	}
	delete[] inOpenList;
	delete[] closedList;

	return;
} 

void Solver::StartSolve(int method) {
	if (method == 0) {
		BFS();
	}
	else if (method == 1) {
		DFS();
	}
	else if (method == 2) {
		Astar();
	}
}