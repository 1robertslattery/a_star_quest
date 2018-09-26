/* 
 * MIT License
 * Copyright (c) 2018 Robert Slattery, Damian Barczyński
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

#include "path_builder.h"
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <ctime>
#include <utility>
#include <set>
#include <math.h>
#include <cstring>
#include <random>
#include <core/exception.h>
#include <math/common.h>
#include <framework/actor.h>

path_builder::path_builder()
{
    // Manhattan (4 directions) by default
    set_diagonal_movement(false);
    set_heuristic(manhattan);
    
    direction = 
    {
        { 0, 1 }, { 1, 0 }, { 1, 0 }, { 0, -1},
        { -1, -1 }, { 1, 1 }, { 0, 1 }, { 1, 1 }
    };

    actor_ptr = new actor();
    if (actor_ptr != nullptr) init_collisions();
}

path_builder::~path_builder()
{
    clear();
}

void path_builder::clear()
{
    if (actor_ptr)
    {
        delete actor_ptr;
        actor_ptr = nullptr;
    }
    
    for (auto it = open_list.begin(); it != open_list.end();)
    {
        delete *it;
        it = open_list.erase(it);
    }
        
    for (auto it = closed_list.begin(); it != closed_list.end();)
    {
        delete *it;
        it = closed_list.erase(it);
    }
    
    walls.clear();
    direction.clear();
}

void path_builder::init_path_coordinates(int _start_x, int _start_y, int _end_x, int _end_y)
{
    path_data_ref.start_coordinate = vector2_i({_start_x, _start_y});
    path_data_ref.end_coordinate = vector2_i({_end_x, _end_y});
}

void path_builder::set_world_size(vector2_i _world_size)
{
    world_size = _world_size;
}

void path_builder::set_diagonal_movement(bool _enabled)
{
    directions = (_enabled ? 8 : 4);
}

int path_builder::init()
{
    open_list.clear();
    closed_list.clear();
    
    return SUCCESS;
}

bool path_builder::is_data_valid()
{
    return ((path_data_ref.end_coordinate.x >= 0 && path_data_ref.end_coordinate.x < world_size.x)
            && (path_data_ref.end_coordinate.y >= 0 && path_data_ref.end_coordinate.y < world_size.y)
            && (path_data_ref.start_coordinate.x >= 0 && path_data_ref.start_coordinate.x < world_size.x)
            && (path_data_ref.start_coordinate.y >= 0 && path_data_ref.start_coordinate.y < world_size.y)
            );
}

void path_builder::set_heuristic(std::function<int(vector2_i, vector2_i)> _heuristic)
{
    heuristic = std::bind(_heuristic, std::placeholders::_1, std::placeholders::_2);
}

void path_builder::add_collision(vector2_i _coordinates)
{
    walls.push_back(_coordinates);
}

void path_builder::remove_collision(vector2_i _coordinates)
{
    auto it = std::find(walls.begin(), walls.end(), _coordinates);
    
    if (it != walls.end())
        walls.erase(it);
}

// Set for (25, 25) grid with goal of (20, 20)
void path_builder::init_collisions()
{
    // 375 obstacles
    for (int i = 0; i < 375; ++i) 
    {
        int min = 0;
        int max = 25;
        
        vector2_i coordinate;
        
        int x = rand_num(min, max);
        int y = rand_num(min, max);
        
        coordinate.x = (int)x;
        coordinate.y = (int)y;
        
        if (x != 0 && y != 0)
        {
            if (x != 20 && y != 20)
            {
                add_collision({x, y});
                actor_ptr->obstacles.push_back(coordinate);
            }    
        }    
    }
}

vector2_array_i path_builder::find_path(const path_data& _data)
{
    init();
  
    node* current = nullptr;
    open_list.insert(new node(_data.start_coordinate));
        
    while (!open_list.empty()) 
    {
        try
        {
            current = *open_list.begin();

            for (auto node : open_list) 
                if (node->get_sum() <= current->get_sum())
                    current = node;

            if (current->position == static_cast<vector2_i>(_data.end_coordinate))
                break;

            closed_list.insert(current);
            open_list.erase(std::find(open_list.begin(), open_list.end(), current));

            // From all movable directions, check the neighbors
            for (int i = 0; i < directions; ++i) 
            {
                vector2_i new_coordinates(current->position + direction[i]);

                if (detect_collision(new_coordinates) || get_node(closed_list, new_coordinates))
                    continue;
                
                double total_cost = current->g + (i < 4 ? 10 : 14); // if i < 4 directions...

                node* successor = get_node(open_list, new_coordinates);

                if (successor != nullptr)
                {
                    if (total_cost < successor->g) 
                    {
                        successor->parent = current;
                        successor->g = total_cost;
                    }
                }
                else
                {
                    successor = new node(new_coordinates, current);
                    successor->g = total_cost;
                    successor->h = heuristic(successor->position, _data.end_coordinate);
                    open_list.insert(successor);
                    successor->set_state(node_state::IN_OPEN_LIST);
                }
            }
        }
        catch (exception& e)
        {
             std::cout << e.what() << std::endl;
        }
    }
    
    vector2_array_i path;
    
    while (current != nullptr)
    {
        path.push_back(current->position);
        current = current->parent;
    }
    
    clear();
    return path;
}

// Finds the node representing given coordinates in nodes list
node* path_builder::get_node(std::set<node*>& _nodes, vector2_i _coordinates)
{
    for (auto node : _nodes)
        if (node->position == static_cast<vector2_i>(_coordinates)) 
            return node; 
            
    return nullptr;
}

// Checks if the point lies inside the obstacle
bool path_builder::detect_collision(vector2_i _coordinates)
{
    if (  _coordinates.x < 0 || _coordinates.x >= world_size.x 
       || _coordinates.y < 0 || _coordinates.y >= world_size.y 
       || std::find(walls.begin(), walls.end(), _coordinates) != walls.end()) 
    {
        return true;
    }
  
    return false;
}

vector2_i path_builder::distance(vector2_i _current, vector2_i _neighbor)
{
    return {abs(_current.x - _neighbor.x), abs(_current.y - _neighbor.y)};
}

int path_builder::euclidean(vector2_i _current, vector2_i _neighbor) // any direction
{
    auto delta = std::move(distance(_current, _neighbor));
    return static_cast<int>(10 * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
}

int path_builder::manhattan(vector2_i _current, vector2_i _neighbor) 
{
    auto delta = std::move(distance(_current, _neighbor));
    return static_cast<int>(10 * (delta.x + delta.y));
}

int path_builder::octagonal(vector2_i _current, vector2_i _neighbor) 
{
    auto delta = std::move(distance(_current, _neighbor));
    return (10 * (delta.x + delta.y) + (-6) * std::min(delta.x, delta.y));
}
