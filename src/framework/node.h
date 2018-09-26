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

#ifndef NODE_H
#define NODE_H

#include <math/linear_algebra/vector.h>

enum node_state
{
    NONE,
    IN_OPEN_LIST,
    IN_CLOSED_LIST
};

struct node
{
    double g;   // movement cost to move from start to given square on grid
    double h;   // heuristic value: a smart guess
    
    vector2_i position;
    node* parent;
    node_state state;
    
    explicit node(
          vector2_i _position
        , node* _parent = nullptr
        , node_state _state = node_state::NONE) :
          position(_position)
        , parent(_parent)
        , g(0)
        , h(0)
        , state(_state)
    {}
    
    inline double get_sum() { return g + h; } // calculates sum of g + h
    
    inline node_state get_state() { return state; }
    inline node_state set_state(node_state _state) { state = _state; }
    
    bool operator==(const node& A)
    {
        return (g == A.g
            && h == A.h
            && position == A.position
            && parent == A.parent
            && state == A.state);    
    }
};

#endif /* NODE_H */

