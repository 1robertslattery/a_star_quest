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

#include "plane.h"
#include <GL/glut.h>

plane::~plane()
{
    clear();
}

void plane::clear()
{
    
}

// Draw a plane using GL scale
void plane::draw()
{
    glColor3f(0, 1, 1);
    glPushMatrix();
    glScalef(2, 0.1, 2);
    glTranslatef(0, -1, 0);
    glutSolidCube(1);
    glPopMatrix();
    glFlush();
}

// Draw a grid
void plane::draw_lines()
{
    glColor3f(0.f, 0.5f, 1.f);
    
    const unsigned int size = 25; // 25x25
    
    glBegin(GL_LINES);
    
        for (unsigned int i = 0; i <= size; ++i)
        {
            glVertex3f(i, 0, 0);
            glVertex3f(i, 0, size);
            glVertex3f(0, 0, i);
            glVertex3f(size, 0, i);
        }
    
    glEnd();
}

void plane::draw_obstacle(float _x, float _y, float _z)
{
    glPushMatrix();
        glTranslatef(_x, _y, _z);
        glColor3f(0, 1, 0);
        glutSolidCube(0.5); // green obstacle
    glPopMatrix();
}

void plane::draw_goal()
{
    glPushMatrix();
        glTranslatef(20, 0.25, 20);
        glColor3f(1, 0, 0);
        glutSolidCube(0.5); // red target
    glPopMatrix();
}
