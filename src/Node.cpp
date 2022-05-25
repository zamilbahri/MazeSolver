#include "../include/Node.h"
#define INF 99999

Node::Node() {
	return;
}

Node::~Node() {
	return;
}

Node::Node(double G) {
	this->G = G;
}

Node::Node(int x, int y, int maxCols) {
	this->maxCols = maxCols;
	this->G = INF;
	this->F = INF;
	this->index = y * maxCols + x;
	this->px = x;
	this->py = y;
	//this->py = index / maxCols;
	//this->px = index - py * maxCols;
}

void Node::PrintInfo() {
	cout << this->index << endl;
}

double Node::ManhattanDistance(Node *end) {
	double absX = (double)(fabs(this->px - end->px));
	double absY = (double)(fabs(this->py - end->py));

	return absX + absY;
}

double Node::GetF() {
	return G + H;
}

bool Node::operator==(Node *other) {
	if (this->index == other->index) {
		return true;
	}
}

double Node::DistanceFromNeighbour(int neighbourIndex) {
	int i = neighbourIndex;
	// N or S
	if (!i || !(3-i)) {
		int tpy = index / maxCols;
		int npy = neighbours[i]->index / maxCols;
		return fabs(tpy - npy);
	}
	// E or W
	else {
		return fabs(index - neighbours[i]->index);
	}
}