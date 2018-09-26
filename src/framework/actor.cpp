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

#include "actor.h"
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <iterator>
#include <unistd.h>
#include <stdint.h>
#include <math/common.h>
#include <GL/glut.h>
#include <core/exception.h>

double actor::pos_x = 0.0;
double actor::pos_y = 0.1;
double actor::pos_z = 0.0;
vector2_i actor::current_position = vector2_i::zero_vector;
vector2_array_i actor::path_coordinates = {};
vector2_array_i actor::obstacles = {};
bool actor::has_reached_destination = false;

actor::~actor() 
{
    clear();
}

void actor::clear()
{
    path_coordinates.clear();
}

void actor::draw()
{
    glPushMatrix();
        glTranslatef(pos_x, pos_y, pos_z);
        glRotatef(-90, 1, 0, 0);

        draw_base_color();
        glutSolidSphere(0.5, 50, 50); // the actor
    glPopMatrix();
}

void actor::draw_base_color()
{
    glPushMatrix();
        glColor3f(0.5,0.5,0.8);
        glScalef(1,1,0.1);    
        glutSolidCube(0.15);
    glPopMatrix();
}

void actor::draw_lines()
{
    glColor3f(1.f,0.f,0.f);   
        
    glBegin(GL_LINE_STRIP);

        for (auto it = path_coordinates.rbegin(); it != path_coordinates.rend() - 1; ++it)
        {
            auto coordinate = *std::next(it, 1);
            
            glVertex3f(it->x, 0.25, it->y); // current
            glVertex3f(coordinate.x, 0.25, coordinate.y); // next
        }
    
    glEnd();
}

vector2_i actor::get_next_coordinate()
{
    if (path_coordinates.size() <= 1)
        std::cout << "GOAL REACHED!" << std::endl;
    else
        std::cout << "Getting next coordinate..." << std::endl;

    for (auto it = path_coordinates.rbegin(); it != path_coordinates.rend() - 1; ++it) // The coordinates are reversed
    {
        auto first_element = path_coordinates.rbegin();    
        auto coordinate = *std::next(it, 1);
        path_coordinates.erase(first_element.base());
               
        std::cout << "The path coordinate index is..." << "\n" << std::endl;
        std::cout << "X: " << coordinate.x << "\t" << "Y: " << coordinate.y <<  "\n" << std::endl;

        has_reached_destination = false;
        return coordinate;
    }
        
    return vector2_i::zero_vector;
}

void actor::move_to_coordinate()
{
    usleep(200000);

    vector2_i next_coordinate = get_next_coordinate();
    
    if (current_position.x != (int)20 && current_position.y != (int)20)
        std::cout << "Moving to next coordinate..." << std::endl;
    
    while (!has_reached_destination)
    {
        try
        {
            vector2_i final_pos = lerp(current_position, next_coordinate, 1.f);
            set_position(final_pos);
            current_position = next_coordinate;
        }
        catch (exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}

vector2_i actor::get_position() const
{
    return current_position;
}

bool actor::set_position(vector2_i _new_location)
{
    if (pos_x != _new_location.x) pos_x = _new_location.x;
    pos_y = 0;
    if (pos_z != _new_location.y) pos_z = _new_location.y;
 
    has_reached_destination = true;
  
    return true;
}

