# MazeSolver

**AUTHORS: Zamil Bahri**

<h2>About</h2>

The mazes were generated in a program called [Daedalus (version 3.3)](http://www.astrolog.org/labyrnth/daedalus.htm). All mazes must be in .bmp format. They are stored in the "mazes" folder. The program assumes that a start exists at the top row of the maze and an exit exists in the bottom row of the maze. The program only works with pixel-based, black and white mazes. The walls are black and the paths are white. The image format should be bitmap (.bmp). The graphics in the program were rendered using the [SDL2](https://libsdl.org/release/SDL2-devel-2.0.22-VC.zip) library.

![](examples/braid63.png)
![](examples/braid1k.png)

<h2> How to Link SDL2 and compile in Visual Studio </h2>

1) Go to the Project Properties in Visual Studio.
2) Go to VC++ Directories -> Include Directories, and click Edit.
4) Copy the path of the "include" folder in SDL2-2.0.20, and add it to Include Directories, then click OK.
4) Go to VC++ Directories -> Library Directories, and click Edit.
5) Copy the path of the "lib/x64" folder in SDL2-2.0.20, and add it to Library Directories, then click OK.
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

Once the animation is completed, go back to the terminal window, press enter, and enter again to terminate the program.

