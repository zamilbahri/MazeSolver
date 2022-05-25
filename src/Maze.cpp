#include "../include/Maze.h"

Maze::Maze() {
	return;
}

Maze::~Maze() {
	return;
}

Maze::Maze(bool *data, int width) {
	int height = width; // for square mazes

	//this->data = new bool[width * width];
	this->data = data;

	Node **topnodes = new Node*[width];
	int count = 0;

	start = nullptr;
	end = nullptr;

	//start
	for (int x = 1; x < width - 1; ++x) {
		if (data[x]) {
			
			this->start = new Node(x, 0, width);
			topnodes[x] = start;
			++count;
			break;
		}
	}

	for (int y = 1; y < height - 1; ++y) {
		int rowOffset = y * width;
		int rowAboveOffset = rowOffset - width;
		int rowBelowOffset = rowOffset + width;

		// initialize previous, current, next
		bool prv = false;
		bool cur = false;
		bool nxt = data[rowOffset + 1];

		Node *leftnode = nullptr;

		for (int x = 1; x < width - 1; ++x) {

			// Move prev, current and next onwards. Read image once per pixel
			prv = cur;
			cur = nxt;
			nxt = data[rowOffset + x + 1];

			//cout << "row = " << y << " col = " << x << endl;
			//cout << "	" << prv << cur << nxt << endl;

			Node *n = nullptr;

			if (!cur) {
				// ON WALL - No action
				continue;
			}

			if (prv) {
				if (nxt) {
					//cout << "	ppp";
					// PATH PATH PATH
					// Create node only if path above or below
					if (data[rowAboveOffset + x] || data[rowBelowOffset + x]) {
						//cout << "-junction";
						n = new Node(x, y, width);
						leftnode->neighbours[1] = n;
						n->neighbours[2] = leftnode;
						leftnode = n;
					}
					//cout << endl;
				}
				else {
					// PATH PATH WALL
					// Create node at the end of corridor
					//cout << "	ppw" << endl;
					n = new Node(x, y, width);
					leftnode->neighbours[1] = n;
					n->neighbours[2] = leftnode;
					leftnode = nullptr;
				}
			}

			else {
				if (nxt) {
					// WALL PATH PATH
					// Create node at the start of corridor
					//cout << "	wpp" << endl;
					n = new Node(x, y, width);
					leftnode = n;
					
				}
				else {
					//cout << "	wpw";
					// WALL PATH WALL
					// Create node only if in dead end
					if (!data[rowAboveOffset + x] || !data[rowBelowOffset + x]) {
						//cout << "-dend";
						n = new Node(x, y, width);
					}
					//cout << endl;
				}
			}

			// If node isn't nullptr, we can assume we can connect N-S somewhere
			if (n) {
				// Clear above, connect to waiting top node
				if (data[rowAboveOffset + x]) {
					Node *t = topnodes[x];
					t->neighbours[3] = n;
					n->neighbours[0] = t;
				}
				
				// If clear below, put this new node in the top row for the next connection
				if (data[rowBelowOffset + x]) {

					topnodes[x] = n;
				}
				else {
					topnodes[x] = nullptr;
				}
				++count;
			}
		}
	}
	
	// End row
	int rowOffset = (height - 1)*width;
	for (int x = 1; x < width - 1; ++x) {
		if (data[rowOffset + x]) {
			this->end = new Node(x, height-1, width);
			Node *t = topnodes[x];
			t->neighbours[3] = this->end;
			this->end->neighbours[0] = t;
			++count;
			break;
		}
	}
	
	delete[] topnodes;

	this->numNodes = count;
	this->width = width;
	this->height = height;
}