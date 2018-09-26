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

#include "camera.h"
#include <stdint.h>
#include <math.h>
#include <math/common.h>
#include <GL/glut.h>

float camera::zoom = 20.f;
float camera::angle = 90.f;
float camera::cam_x = 0.1f;
float camera::cam_y = 0.1f;
float camera::cam_z = 0.1f;
float camera::window_ratio = 1.f;

void camera::update_camera(float _actor_x, float _actor_y, float _actor_z)
{
    float radians = angle * PI / 180;

    // Orientation
    cam_x = cos(radians) * zoom + _actor_x;
    cam_y = _actor_y + 1;    
    cam_z = sin(radians) * zoom + _actor_z;
        
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, window_ratio, 1, 30);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(cam_x, cam_y, cam_z, _actor_x, _actor_y, _actor_z, 0, 1, 0);
    
    // Positioning
    glTranslatef(-12.f, 12.f, -3.f);    // (left/right, up/down, zoom)
    glRotatef(90.f, 1.f, 0, 0);         // Allows top-down rotation
}

void camera::reset_camera()
{
    zoom = 3.f;
    angle = 30.f;
    cam_x = 0.1f;
    cam_y = 0.1f;
    cam_z = 0.1f;
}

