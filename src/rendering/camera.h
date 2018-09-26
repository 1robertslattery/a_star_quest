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

#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>

/*
 * The camera used to visualize the FreeGLUT simulation.  
 */
class camera
{
    
public:
    
    inline static float get_cam_x() { return cam_x; }
    inline static void set_cam_x(float _x_look_to) { cam_x = _x_look_to; }

    inline static float get_cam_y() { return cam_y; };
    inline static void set_cam_y(float _y_look_to) { cam_y = _y_look_to; }

    inline static float get_cam_z() {return cam_z; }
    inline static void set_cam_z(float _z_look_to) { cam_z = _z_look_to; }

    inline static float get_zoom() { return zoom; }
    inline static void zoom_up() { zoom -= 0.1; }
    inline static void zoom_down() { zoom += 0.1; }

    inline static void rise_angle() { angle++; }
    inline static void set_window_ratio(float ratio) { window_ratio = ratio; }

    static void update_camera(float _actor_x, float _actor_y, float _actor_z);        
    static void reset_camera();
    
private:
    
    static float cam_x;
    static float cam_y;
    static float cam_z;
    static float angle;
    static float zoom;
    static float window_ratio;

};

#endif /* CAMERA_H */

