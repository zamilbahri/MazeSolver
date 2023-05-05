// AUTHOR: Zamil Bahri

// This files neatly stores all the pre-preprocessor constants
// used in the program

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

/* Smaller mazes will be enlarged to MIN_WINDOW_SIZE. */
/* Larger mazes will be actual size */
#define MIN_WINDOW_SIZE 800

/* Mazes larger than this will not be displayed */
#define MAX_WIDTH 1002

/* Display Maze before solving it */
/* Preferred state = false. Otherwise, it pops up in front of the console window */
#define DISPLAY_EMPTY_MAZE false

/* Dislay the solution(s) to the maze */
#define DISPLAY_SOLUTION true

/* Animate the solution(s). */
/* If false, solution(s) will just be displayed */
/* Solution will not display if DISPLAY_SOLUTION = false */
#define ANIMATE_SOLUTION true

/* Prompts user to press enter after each successive algorithm is used */
#define PAUSE_AFTER_SOLUTION false

/* Make the priority_queue in A* use the default comparison operator */
/* Setting to false takes more time and longer path - don't know why */
#define USE_DEFAULT_COMPARISON false

/* A* Algorithm searches all nodes to find absolute shortest path. (Doesn't work as expected) */
/* Note that Astar() unfortunately does not necessarily find shortest path */
#define ASTAR_SEARCH_ALL_NODES false

#endif
