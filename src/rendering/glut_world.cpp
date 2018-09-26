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

#include "glut_world.h"
#include <string>
#include <math/linear_algebra/vector.h>
#include <rendering/camera.h>
#include <math/geometry/plane.h>
#include <framework/actor.h>

#define FPS 120

actor glut_world::actor_ref;
plane glut_world::plane_ref;
int glut_world::frame_count = 0;
int glut_world::fps = 0;
int glut_world::previous_time = 0;

void glut_world::setup_lighting()
{
    GLfloat placeLight[4] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat diffusedLight[4] = { 0.7, 0.7, 0.7, 1.0 };      // color 
    GLfloat specularLight[4] = { 1.0, 1.0, 1.0, 1.0 };      // brightness 
    GLfloat lightPosition[4] = { 10.0, 10.0, 1.0, 1.0 };    // light position variation

    // Material brightness 
    GLfloat specularity[4] = { 1.0, 1.0, 1.0, 1.0 };
    GLint materialSpecularity = 60;

    // Gouraud colors
    glShadeModel(GL_SMOOTH);

    // Reflection 
    glMaterialfv(GL_FRONT,GL_SPECULAR, specularity);
    
    // Brightness concentration 
    glMateriali(GL_FRONT,GL_SHININESS, materialSpecularity);

    // Place light
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, placeLight);

    glLightfv(GL_LIGHT0, GL_AMBIENT, placeLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffusedLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
}

int glut_world::run(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowPosition(50, 50);
    glutInitWindowSize(1024, 768);
    glutCreateWindow("A* Search Algorithm");
    
    setup_lighting();

    glutDisplayFunc(display_callback);
    glutTimerFunc(25, timer_callback, 0);
    glutReshapeFunc(reshape_callback);

    glutMainLoop();
    
    return SUCCESS;
}

void glut_world::timer_callback(int value)
{
    loop_callback();
    glutTimerFunc((1000 / FPS), timer_callback, 0);
    glutPostRedisplay();
}

void glut_world::display_callback()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    new_frame();

    camera::update_camera(0, actor_ref.get_y(), 0);
    plane_ref.draw_lines();
    plane_ref.draw_goal();
        
    for (auto& obstacle : actor_ref.obstacles)
        plane_ref.draw_obstacle(obstacle.x, 0.25f, obstacle.y);
        
    actor_ref.draw();
    actor_ref.draw_lines();

    glutSwapBuffers();
}

void glut_world::reshape_callback(int width, int height)
{
    glViewport (0, 0, (GLsizei) width, (GLsizei) height);
    float ratio = (float)width / (float)height;
    camera::set_window_ratio(ratio);
    camera::update_camera(0, actor_ref.get_y(), 0);
}

void glut_world::loop_callback()
{
    actor_ref.move_to_coordinate();
}

int glut_world::new_frame()
{
    frame_count++;
    
    // Get the number of milliseconds since glutInit called
    int current_time = glutGet(GLUT_ELAPSED_TIME);

    // Calculate time passed
    int time_interval = current_time - previous_time;

    if (time_interval > 1000)
    {  
        // Calculate the number of frames per second
        fps = frame_count / (time_interval / 1000.0f);
        previous_time = current_time;
        frame_count = 0;
    }
    
    return fps;
}

