// AUTHOR: Zamil Bahri and Jacob Steckler
// - ImportImage(): Jacob
// - DisplayImage(): Jacob
// - DisplayPath(): Jacob and Zamil
// - Graphics related functions were mainly Jacob's responsibility
// - Rest: Zamil

// This class sets up the rest of the program properly.
// Also responsible for all the graphics related functions

#ifndef SETUP_H_
#define SETUP_H_

#include "Solver.h"
#include <SDL.h>
#include <ctime>
#include <string>

class Setup {

private:
	/* --- METHODS --- */
	void DisplayImage();
	void DisplayPath(list<Node*> path, int r, int g, int b);

public:

	/* --- ATTRIBUTES --- */

	string filePath;
	Maze *mz;
	Solver *s;
	bool *im;
	int width;
	bool methods[3]; // {BFS, DFS, Astar}

	// Used for graphics
	SDL_Surface *maze;
	SDL_Window* window;

	SDL_Renderer* renderer;
	SDL_Texture* textMaze;

	/* --- METHODS --- */

	Setup();
	~Setup();
	
	void InputFileName();
	bool ImportImage();
	bool CreateMaze();
	bool InputMethods();
	void SolveMaze();

};

#endif
