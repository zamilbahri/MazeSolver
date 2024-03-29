#include "../include/Setup.h"
#include <fstream>
#include <cstdlib>
#include <stdint.h>

Setup::Setup() : methods{ false } {
	width = 0;
	mz = nullptr;
	s = nullptr;
	im = nullptr;
	filePath = "mazes/";
	return;
}

Setup::~Setup() {
	return;
}

// Displays a list of maze/file names
void Setup::DisplayMazeOptions() {
	std::cout << "Choose a maze from the following options:" << endl;

	std::cout << "tiny       - 10x10. Used for testing." << endl;
	std::cout << "normal     - 41x41. Used for testing." << endl;
	std::cout << "braid63    - 63x63. Used for testing." << endl;
	std::cout << "combo400   - 401x401. Multiple solutions, no dead ends." << endl;
	std::cout << "braid600   - 601x601. Multiple solutions." << endl;
	std::cout << "perfect600 - 601x601. Unique solution." << endl;
	std::cout << "braid800   - 801x801. Multiple solutions" << endl;
	std::cout << "perfect800 - 801x801. Unique solution." << endl;
	std::cout << "braid1k    - 1001x1001. Multiple solutions." << endl;
	std::cout << "perfect1k  - 1001x1001. Unique solution." << endl;
	std::cout << "perfect2k  - 2001x2001. Unique solution." << endl;
	std::cout << "perfect4k  - 4001x4001. Unique solution." << endl;
	std::cout << "perfect6k  - 6001x6001. Unique solution." << endl;
	std::cout << "combo6k    - Multiple solutions, no dead ends." << endl;

	std::cout << endl;
}


bool Setup::InputFileName() {
	std::cout << "Enter the name of the maze:\n>>>";
	string fileName;
	getline(cin, fileName);
	filePath += fileName + ".bmp";

	if (FILE* file = fopen(filePath.c_str(), "r")) {
		fclose(file);
		std::cout << "File exists." << endl;
		std::cout << "filePath = " << filePath << endl;
		std::cout << endl;
		return true;
	}

	std::cout << "File does not exist." << endl;
	std::cout << "filePath = " << filePath << endl;
	return true;
}

bool Setup::InputMethods() {
	std::cout << "Which of the following method(s) would you like to\n";
	std::cout << "solve the maze with?" << endl;
	std::cout << "1) Breadth-First Search" << endl;
	std::cout << "2) Depth-First Search" << endl;
	std::cout << "3) A*" << endl;
	std::cout << "Your input:\n>>>";

	string choices;
	getline(cin, choices);

	for (int i = 0; (choices[i] && i<3); ++i) {
		int m = choices[i];
		if (m == 32) { // space
			continue;
		}
		else if (((m - 49) >= 0) && ((m - 49 <= 3))) {
			methods[(m - 48) - 1] = true;
		}
		else {
			std::cout << "Input not recognized. Please try again.\n" << endl;
			return 0;
		}
	}
	system("cls");

	if (width < MAX_WIDTH && DISPLAY_SOLUTION && !DISPLAY_EMPTY_MAZE) DisplayImage();

	return 1;
}


// Helper function for ImportImage(). Gets the pixel from
// the (x, y) coordinates of the SDL_Surface
static Uint32 getpixel(SDL_Surface *surface, int x, int y) {
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		return *p;

	case 2:
		return *(Uint16 *)p;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];

	case 4:
		return *(Uint32 *)p;

	default:
		return 0; /* shouldn't happen, but avoids warnings */

	}
}


// Gets the data in a boolean array format from an image
bool Setup::ImportImage() {

	clock_t begin = clock();

	maze = SDL_LoadBMP(filePath.c_str());

	if (maze == NULL) {
		std::cout << "Could not import image." << endl;
		SDL_FreeSurface(maze);
		return 0;
	}

	SDL_LockSurface(maze);

	// Initialize data array
	im = new bool[maze->w * maze->w];

	// for some reason, sometimes black gets recorded as 1
	//	and white gets recorded as 0. This recognizes
	//	the problem and adjusts accordingly
	bool needToInvert = getpixel(maze, 0, 0);

	for (int row = 0; row < maze->w; row++)
	{
		for (int col = 0; col < maze->w; col++) {
			int p = fabs(needToInvert - getpixel(maze, col, row));
			int i = row * maze->w + col;
			im[i] = p; // implicit conversion int -> bool
		}
	}
	std::cout << "Dimensions = " << maze->w << " x " << maze->h << endl;
	width = maze->w;

	SDL_UnlockSurface(maze);

	clock_t end = clock();
	double timeElapsed = (double)(end - begin) / CLOCKS_PER_SEC;
	std::cout << "Time taken to read pixels = " << timeElapsed << " seconds." << endl;
	std::cout << endl;

	return 1;
}

// Displays the Maze
void Setup::DisplayImage() {
	SDL_Window* window = SDL_CreateWindow("maze", 10, 0, NULL, NULL, SDL_WINDOW_SHOWN);

	// Set width of the window size
	int multiplier = MIN_WINDOW_SIZE / width;

	if (multiplier > 1) {
		SDL_SetWindowSize(window, width * multiplier, width * multiplier);
	}
	else {
		SDL_SetWindowSize(window, width, width);
	}

	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	
	//SDL_Window* window = SDL_CreateWindow("maze", 200, 200, 200, 200, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	textMaze = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 50, 50); //Creating a texture

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_SetRenderTarget(renderer, textMaze);
	SDL_RenderClear(renderer);
	SDL_SetRenderTarget(renderer, NULL);
	SDL_SetSurfaceBlendMode(maze, SDL_BLENDMODE_ADD);

	textMaze = SDL_CreateTextureFromSurface(renderer, maze);

	SDL_RenderCopy(renderer, textMaze, NULL, NULL);
	SDL_RenderPresent(renderer);
}

// Sets up the nodes and the graph for the maze
bool Setup::CreateMaze() {
	if (width == 0) {
		std::cout << "Data not properly scraped" << endl;
		SDL_FreeSurface(maze);
		return 0;
	}

	std::cout << "Creating Maze..." << endl;

	clock_t begin = clock();
	mz = new Maze(im, width);
	clock_t end = clock();
	double timeElapsed = (double)(end - begin) / CLOCKS_PER_SEC;

	std::cout << "Maze created." << endl;
	std::cout << "Time taken to set up nodes = " << timeElapsed << " seconds." << endl;
	std::cout << "Number of nodes = " << mz->numNodes << endl;
	std::cout << endl;

	if (width <= MAX_WIDTH && DISPLAY_EMPTY_MAZE) {
		DisplayImage();
	}

	system("pause");
	system("cls");
	std::cout << "filePath = " << filePath << endl;
	std::cout << endl;

	return 1;
}

// Displays the solution(s) to the maze
void Setup::DisplayPath(list<Node*> path, int r, int g, int b) {

	Node *cameFrom = nullptr;
	for (Node* n : path) {

		if (cameFrom == nullptr) {
			cameFrom = n;
			continue;
		}

		int multiplier = MIN_WINDOW_SIZE / width;
		if (multiplier < 1) multiplier = 1;
		double offSet = (double)multiplier / 2;

		double x1 = cameFrom->px * multiplier + offSet;
		double y1 = cameFrom->py * multiplier + offSet;

		double x2 = n->px * multiplier + offSet;
		double y2 = n->py * multiplier + offSet;

		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

		if (ANIMATE_SOLUTION) SDL_RenderPresent(renderer);

		cameFrom = n;
	}
	if (PAUSE_AFTER_SOLUTION) system("pause");
}

void Setup::SolveMaze() {

	std::cout << "filePath = " << filePath << endl;
	std::cout << "Number of nodes = " << mz->numNodes << endl;
	std::cout << endl;

	for (int i = 0; i < 3; ++i) {
		if (methods[i] == false) continue;

		Solver *s = new Solver(mz->start, mz->end);

		std::cout << "Starting the solve using ";
		if (i == 0) std::cout << "Breadth First Search..." << endl;
		if (i == 1) std::cout << "Depth First Search..." << endl;
		if (i == 2) std::cout << "A*..." << endl;

		clock_t begin = clock();
		s->StartSolve(i);
		clock_t end = clock();
		double timeElapsed = (double)(end - begin) / CLOCKS_PER_SEC;

		std::cout << "Maze solved." << endl;
		std::cout << "Time taken to solve = " << timeElapsed << " seconds" << endl;
		std::cout << "Nodes explored = " << s->nodesExplored << endl;
		std::cout << "Path length = " << s->pathLength << endl;
		std::cout << endl;

		// Adds current path to renderer
		if (width < MAX_WIDTH && DISPLAY_SOLUTION) {
			if (i == 0) DisplayPath(s->path, 255, 0, 0);
			if (i == 1) DisplayPath(s->path, 0, 255, 0);
			if (i == 2) DisplayPath(s->path, 0, 0, 255);
		}

		delete s;
	}
	if (width < MAX_WIDTH && DISPLAY_SOLUTION && !ANIMATE_SOLUTION) SDL_RenderPresent(renderer);
	if (width < MAX_WIDTH && DISPLAY_SOLUTION) SDL_RenderCopy(renderer, textMaze, NULL, NULL);
	system("pause");
	SDL_FreeSurface(maze);
}


