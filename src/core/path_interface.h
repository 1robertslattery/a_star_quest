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

#ifndef PATH_INTERFACE_H
#define PATH_INTERFACE_H

#include <stdint.h>
#include <functional>
#include <math/linear_algebra/vector.h>
#include <core/interface.h>

class path_interface : public interface
{
    
public:
    
    virtual ~path_interface() {};
        
    //~ Begin Path Interface
    virtual int init() = 0;
    virtual void clear() = 0;
    virtual bool is_data_valid() = 0;
    virtual void init_path_coordinates(int _start_x, int _start_y, int _end_x, int _end_y) = 0;
    virtual void set_world_size(vector2_i _world_size) = 0;
    virtual void add_collision(vector2_i _coordinates) = 0;
    virtual void remove_collision(vector2_i _coordinates) = 0;
    virtual void init_collisions() = 0;
    virtual void set_heuristic(std::function<int(vector2_i, vector2_i)> _heuristic) = 0;
    //~ End Path Interface

};

#endif /* PATH_INTERFACE_H */

