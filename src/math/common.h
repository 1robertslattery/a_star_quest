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

#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <random>
#include <stdint.h>
#include "linear_algebra/vector.h"

#define PI 3.14159265359

#ifdef _WIN32
    #define NOMINMAX
#endif

template<typename T>
T MAX(T a, T b)
{
    return ((a > b) ? a : b);
}

template<typename T>
T MIN(T a, T b)
{
    return ((a < b) ? a : b);
}

template<typename T>
inline T lerp(const T& a, const T& b, const float t)
{
    return (1.f - t) * a + b * t;
}

template<std::size_t n, typename T>
inline svector<n, T> lerp(svector<n, T>& a, svector<n, T>& b, const float t)
{
    svector<n, T> retVal;
    
    for (std::size_t i = 0; i < n; ++i)
        retVal[i] = lerp(a[i], b[i], t);
    
    return retVal;
}

template<typename T>
inline T rand_num(const T& min, const T& max)
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> uni(min, max); // use uniform_real_distribution for "float/double"
    return uni(generator);
}

template<typename T>
void remove(std::vector<T>& vec, std::size_t pos)
{
    auto it = vec.begin();
    std::next(it, pos);
    vec.erase(it);
}

#endif /* COMMON_H */

