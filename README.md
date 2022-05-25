# MazeSolver

**AUTHORS: Zamil Bahri and Jacob Steckler**

<h2>About</h2>

The mazes were generated in a program called [Daedalus (version 3.3)](http://www.astrolog.org/labyrnth/daedalus.htm). All mazes must be in .bmp format. They are stored in the "mazes" folder. The program assumes that a start exists at the top row of the maze and an exit exists in the bottom row of the maze. The program only works with pixel-based, black and white mazes. The walls are black and the paths are white. The image format should be bitmap (.bmp). The graphics in the program were rendered using the [SDL2](https://libsdl.org/release/SDL2-devel-2.0.22-VC.zip) library.

<h2> How to Link SDL2 and compile in Visual Studio </h2>

0) Download SDL2 using the above link. Save it a directory where you can find it easily (for exampple, C:\\Libraries).
1) Go to the Project Properties in Visual Studio.
2) Go to VC++ Directories -> Include Directories, and click Edit.
4) Navigate to where you downloaded SDL2, copy the path of the "include" folder, and add it to Include Directories, then click OK.
4) Go to VC++ Directories -> Library Directories, and click Edit.
5) Navigate to where you downloaded SDL2, copy the path of the "lib/x64" folder, and add it to Library Directories, then click OK.
6) Go to Linker -> Input -> Additional Dependencies, and click Edit
7) Type "SDL2.lib; SDl2main.lib" in the available box, then click OK.
8) Go to Linker -> System -> SubSystem, and in the dropdown menu, click "/SUBSYSTEM: CONSOLE".
9) Click OK and exit out of MazeSolver Properties.
10) Compile and run the program by clicking "Local Windows Debugger" at the top.
 
<h2> Mazes and Searching </h2>

There are 3 types of mazes used in this program:
- braid: Multiple solutions
- perfect: Unique solution
- combo: braid, but with no dead ends.

This progam attempts to solve these mazes using three well known search/pathfinding algorithms:
1) Breadth-First Search (BFS)
2) Depth-First Search (DFS)
3) A* (Read: A-Star)

The "tiny.bmp" and "normal.bmp" were used extensively for initial testing. "tiny" is braid, while "normal" is perfect.

<h2>How to run the program</h2>

Launch the program. Take the look at the "DEFINITIONS.h" file if you want to change minor things, such as displaying/animating the solution, changing minimum window size, maximum size of maze displayed etc.

You will be given a list of files to choose from, with some brief information. Enter the NAME of the file. DO NOT add ".bmp" in your input. If an incorrect file name is chosen, the program will recognize this and terminate accordingly.

If the name is input successfully and the maze is created, the program will display the length of time taken to create the maze,
and the number of nodes the maze has been reduced to.

At this point, you might want to move the console window to the right side of the screen. If the maze window pops up, it will
block the screen and you won't be able to see the console.

Next, you will be given the aforementioned algorithms to choose from. You may choose one or more algorithms. Here are some
sample inputs:
- BFS and A*: 1 2
- DFS and A*: 23
- All: 123
- All: 1 2 3

Once you have chosen your method(s), the program will begin the pathfinding. Depending on your preferences set in
DEFINITIONS.h, the program will display (and animate) the solution to the maze.

Once the animation is completed, press enter, and enter again to terminate the program. Hopefully, the program
ends with exit code 0.

<h2>Bugs</h2>

- Take a look at the top of main.cpp file for the TODO list for an overview.
- Moving the console window on top of the maze window messes up the graphics. It is recommended you restart the program and move the console wndow to the right before the graphics winsow pops up.
- Mazes larger than the height of your monitor screen will not be displayed by default. If you wish to have them diplayed, change the "MAX_WIDTH" constant's value in the "DEFINITIONS.h" file to a suitable value.
- A* doesn't necessarily find the shortest path. Using a custom comparator for priority_queue to compare G_cost is less effective than the default comparator. Possible reason for less effectiveness could be that the heuristic function is off. The manhattan distance is not a good approximation, since the actual distance in the maze can be a long and convoluted path.
- Need more comments, although most functions without comments are self-explanatory.

