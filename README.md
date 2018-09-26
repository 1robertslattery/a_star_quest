# A* Quest
A solution to find the shortest path

## OVERVIEW

The A* search algorithm is a popular technique to approximate the shortest path between points, typically on a 2D grid.  This project solves an A* search algorithm and uses FreeGLUT to simulate the movement of a sphere actor from start to goal against a random set of obstacles set on the simulation grid.  This project was developed for **Debian 9.5.0 (amd64)** with the Netbeans IDE.

**Features:**
- `C++11` and `C++14` tested to compile with `gcc 6.3.0`
- Allows various movement directions: manhattan (4 directions), euclidean (any direction) or octagonal directions, with optional diagonal movement
- POSIX Multithreading, using a thread pool to run workers in parallel
- API that follows `abstract interface pattern` for additional modules
- Randomized obstacles that allow for a multitude of path outcomes
- Templated math library for vectors
- Prints coordinates to terminal
- Makefile
- Requires compile flags:  `-lGL`  `-lGLU`  `-lglut`  `-lGLEW`  `-lpthread`

## FREEGLUT DEMONSTRATION

### Manhattan (Diagonal Movement)

![alt text](/screenshots/manhattan-diagonal.png?raw=true)

### Manhattan (No Diagonal Movement)

![alt text](/screenshots/manhattan.png?raw=true)

### Euclidean (Diagonal Movement)

![alt text](/screenshots/euclidean-diagonal.png?raw=true)

### Euclidean (No Diagonal Movement)

![alt text](/screenshots/euclidean.png?raw=true)

### Octagonal (Diagonal Movement)

![alt text](/screenshots/octagonal-diagonal.png?raw=true)

### Octagonal (No Diagonal Movement)

![alt text](/screenshots/octagonal.png?raw=true)

## FREEGLUT LIBRARY

### For Debian/Ubuntu

**1. Make sure your apt lists are up-to-date**

```
sudo apt-get update
```

**2. Install FreeGLUT/OpenGL development libraries**

```
sudo apt-get install freeglut3 freeglut3-dev libglew-dev libglu-dev libgl-dev libgl1-mesa-dev libglu1-mesa-dev mesa-utils mesa-common-dev build-essential
```

## EXAMPLE USAGE

```c++
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <parallel/thread_pool.h>
#include <framework/path_master.h>
#include <rendering/glut_world.h>

int main(int argc, char** argv) 
{
    path_master calculations;
    glut_world simulation;
    
    // Using 2 worker threads
    thread_pool pool(2);
    
    pool.enqueue([&] { calculations.run(argc, argv); } );
    std::this_thread::sleep_for(std::chrono::seconds(1));
    pool.enqueue([&] { simulation.run(argc, argv); } );
        
    return 0;
}
```

## FILES AND FOLDERS

| Files and Folders	| Description						|
| --------------------- |:-----------------------------------------------------:|
| `nbproject`		| Files that configure Makefile and Netbeans project	|
| `src`			| Project source						|
| `screenshots`		| Demo pictures in README				|
| `CHANGELOG`		| Log to track changes in respository			|
| `README`		| This file						|
| `Makefile`		| Used to tell compiler which source files to use	|

### nbproject

| Files			| Description				|
| ----------------------|:-------------------------------------:|
| `configurations.xml`	| Edit this file to update Makefile	|
| `project.xml`		| For project generation		|

### src

| Files and Folders		| Description						|
| ----------------------------- |:-----------------------------------------------------:|
| `src/core`			| Base classes						|
| `src/framework`		| Pathfinding calculations				|
| `src/math`			| Common math functions					|
| `src/math/geometry`		| Example of grid plane					|
| `src/math/linear_algebra`	| Templated vector math					|
| `src/parallel`		| Example to handle multithreading			|
| `src/rendering`		| FreeGLUT example					|
| `main.cpp`			| Example						|

### src/core

| Files				| Description						|
| ----------------------------- |:-----------------------------------------------------:|
| `exception.h`			| Exception you are not allowed to catch		|
| `interface.h`			| Base class for interfaces				|
| `object.h`			| Generic base class					|
| `path_interface.h`		| Interface for pathfinding				|
| `simulation_interface.h`	| Interface for FreeGLUT simulation			|

### src/framework

| Files			| Description						|
| --------------------- |:-----------------------------------------------------:|
| `actor.h`		| Header: Represented as sphere in simulation		|
| `actor.cpp`		| Source: Represented as sphere in simulation		|
| `node.h`		| The node picked each step of search			|
| `path_builder.h`	| Header: A* Search Algorithm				|
| `path_builder.cpp`	| Source: A* Search Algorithm				|
| `path_master.h`	| Header: Executes pathfinding calculations		|
| `path_master.cpp`	| Source: Executes pathfinding calculations		|

### src/math

| Files		| Description						|
| ------------- |:-----------------------------------------------------:|
| `common.h`	| Common math functions					|

### src/math/geometry

| Files			| Description						|
| --------------------- |:-----------------------------------------------------:|
| `plane.h`		| Header: Represented as a 2D grid in simulation	|
| `plane.cpp`		| Source: Represented as a 2D grid in simulation	|

### src/math/linear_algebra

| Files		| Description						|
| --------------|:-----------------------------------------------------:|
| `vector.h`	| Templated structs that handle vector math		|

### src/parallel

| Files			| Description						|
| --------------------- |:-----------------------------------------------------:|
| `thread_pool.h`	| Example to handle multithreading			|

### src/rendering

| Files			| Description						|
| --------------------- |:-----------------------------------------------------:|
| `camera.h`		| Header: Camera to visualize simulation		|
| `camera.cpp`		| Source: Camera to visualize simulation		|
| `glut_world.h`	| Header: Executes FreeGLUT				|
| `glut_world.cpp`	| Source: Executes FreeGLUT				|

## LICENSE

**Files attributed to this repository author will have the following text:**

> MIT License
>
> Copyright (c) 2018 Robert Slattery
> 
> Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## NOTES

This software is shipped "as-is" without warranty.
