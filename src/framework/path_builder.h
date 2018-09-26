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

#ifndef PATH_BUILDER_H
#define PATH_BUILDER_H

#include <memory>
#include <cstdint>
#include <functional>
#include <set>
#include <framework/node.h>
#include <math/linear_algebra/vector.h>
#include <core/path_interface.h>
#include <core/object.h>

#define SUCCESS 0
#define FAILURE -1

struct path_data
{
    vector2_i start_coordinate;
    vector2_i end_coordinate;
        
    explicit path_data() :
          start_coordinate({0, 0})
        , end_coordinate({0, 0})
    {}
    
    bool operator==(const path_data& A)
    {
        return (start_coordinate == A.start_coordinate 
            && end_coordinate == A.end_coordinate);
    }
    
    bool operator!=(const path_data& A)
    {
        return (start_coordinate != A.start_coordinate 
            || end_coordinate != A.end_coordinate);
    }
};

class path_builder : public object, public path_interface
{
    
public:
    
    path_builder();
    ~path_builder();
       
    // Solves the path
    vector2_array_i find_path(const path_data& _data);
                      
    // Node Sets
    std::set<node*> open_list;
    std::set<node*> closed_list;
    
    // Movement directions
    static vector2_i distance(vector2_i _current, vector2_i _neighbor);
    static int euclidean(vector2_i _current, vector2_i _neighbor);
    static int manhattan(vector2_i _current, vector2_i _neighbor);
    static int octagonal(vector2_i _current, vector2_i _neighbor);
    void set_diagonal_movement(bool _enabled);
    
    struct path_data path_data_ref;

    //~ Begin Path Interface
    virtual int init() override;
    virtual void clear() override;
    virtual bool is_data_valid() override;
    virtual void set_world_size(vector2_i _world_size) override;
    virtual void init_path_coordinates(int _start_x, int _start_y, int _end_x, int _end_y) override;
    virtual void add_collision(vector2_i _coordinates) override;
    virtual void remove_collision(vector2_i _coordinates) override;
    virtual void init_collisions() override;
    virtual void set_heuristic(std::function<int(vector2_i, vector2_i)> _heuristic) override;
    //~ End Path Interface
    
private:

    vector2_i world_size;
    vector2_array_i direction;
    vector2_array_i walls;
    int directions;
    std::function<int(vector2_i, vector2_i)> heuristic;
                        
    bool detect_collision(vector2_i _coordinates);
    
    node* get_node(std::set<node*>& _nodes, vector2_i _coordinates);
    
    class actor* actor_ptr;

};

#endif /* PATH_BUILDER_H */

