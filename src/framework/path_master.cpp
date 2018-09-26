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

#include "path_master.h"
#include <iostream>
#include <cstdlib>
#include <assert.h>
#include <math/linear_algebra/vector.h>

path_master::path_master()
{
    init();
}

path_master::~path_master()
{
    clear();
}

int path_master::init()
{
    path_builder_ptr = new path_builder();
    actor_ptr = new actor();
    return 0;
}

void path_master::clear()
{
    if (path_builder_ptr)
    {
        delete path_builder_ptr;
        path_builder_ptr = nullptr;
    }
    
    if (actor_ptr)
    {
        delete actor_ptr;
        actor_ptr = nullptr;
    }
}

int path_master::run(int argc, char** argv)
{
    assert(path_builder_ptr != nullptr);
    assert(actor_ptr != nullptr);

    path_builder_ptr->set_world_size({ 25, 25 });
    path_builder_ptr->init_path_coordinates(0, 0, 20, 20);
    
    path_builder_ptr->set_heuristic(path_builder_ptr->euclidean);
    path_builder_ptr->set_diagonal_movement(true);

    // Returns vector of coordinates from start to end
    auto path = path_builder_ptr->find_path(path_builder_ptr->path_data_ref);

    for (auto& coordinate : path)
    {
        std::cout << "X: " << coordinate.x << "\t" << "Y: " << coordinate.y << "\n";

        // Add coordinate to an array for sphere actor movement
        actor_ptr->path_coordinates.push_back(coordinate);
    }
    
    return SUCCESS;
}

