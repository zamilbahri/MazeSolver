/*
#####################################################################
AUTHORS: Zamil Bahri & Jacob Steckler

MAZE SOLVER

 This program solves a pixel-based using well-known
 pathfinding algorithms, such as:
 - BFS
 - DFS
 - A*
 and displays the solution(s).

 TODO
 - Better UI
 - Optimize A*
 - Divide Maze(data, width) into smaller functions
 - Error evasion for SolveMaze() in Solve class
 - Better classification of public and private attributes & methods
 - Completely separate graphics related functions
 ####################################################################
 */

/* Imports and Definitions */
#include "../include/Setup.h"

using namespace std;

/* Functions*/


int main(int argc, char *argv[]) {


	Setup *s = new Setup();

	// Display maze options to user
	s->DisplayMazeOptions();

	// Input the name of the .bmp file the maze is in
	s->InputFileName();

	// exits if file not found, or some other problem encountered
	if (!s->ImportImage()) exit(0);

	// exits if maze not created properly.
	if (!s->CreateMaze()) exit(0);	

	// keeps trying to input methods until valid ones are entered
	while (!s->InputMethods()) {}

	// solves the maze.
	//TODO: implement some sort of error evasion (has not been encountered)
	s->SolveMaze();

	//delete s;

	return 0;
}


