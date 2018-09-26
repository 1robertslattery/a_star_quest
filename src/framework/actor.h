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

#ifndef ACTOR_H
#define ACTOR_H

#include <math/linear_algebra/vector.h>
#include <core/simulation_interface.h>

/*
 * Sphere  
 * 
 * Requires static members to be called in FreeGLUT simulation.
 */
class actor : public simulation_interface
{
    
public:
    
    explicit actor() {}
    virtual ~actor();
    
    inline double get_x() { return pos_x; }
    inline double get_y() { return pos_y; }
    inline double get_z() { return pos_z; }
        
    void draw_base_color();
           
    static vector2_i current_position;
    vector2_i get_position() const;
    static bool set_position(vector2_i _new_location);
    
    static vector2_array_i path_coordinates;
    static vector2_array_i obstacles;
        
    static void move_to_coordinate();
    static vector2_i get_next_coordinate();
    
    //~ Begin Simulation Interface
    virtual int init() override { return 0; }
    virtual void clear() override;
    virtual void draw() override;
    virtual void draw_lines() override;
    //~ End Simulation Interface
            
private:
             
    static bool has_reached_destination;
        
    static double pos_x;
    static double pos_y;
    static double pos_z;
            
};

#endif /* ACTOR_H */

