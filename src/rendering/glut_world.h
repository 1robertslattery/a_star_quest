/* 
 * MIT License
 * Copyright (c) 2018 Robert Slattery
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef GLUT_WORLD_H
#define GLUT_WORLD_H

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <core/simulation_interface.h>
#include <GL/glut.h>

#define SUCCESS 0
#define FAILURE -1

class simulation_interface;

/*
 * The class that handles the FreeGLUT simulation.  
 * 
 * NOTE: This version uses 2D vectors (vector2_i) that have to be adapted 
 * to 3D coordinates for the simulation.  This is because the A* search is done
 * on a 2D grid.  If you require strict continuity, then use vector3_i instead.
*/
class glut_world
{
    
public:
    
    explicit glut_world() {};
    ~glut_world() {};
    
    void setup_lighting();
    int run(int argc, char** argv);
    
    static void timer_callback(int value);
    static void display_callback();
    static void reshape_callback(int width, int height);
    static void loop_callback();
               
private:
    
    static int frame_count;
    static int fps;
    static int previous_time;
    inline static int get_fps() { return fps; };
    static int new_frame();
        
    static class actor actor_ref;
    static class plane plane_ref;

};

#endif /* GLUT_WORLD_H */

