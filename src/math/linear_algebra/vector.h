/* 
 * Attribution-NonCommercial 4.0 International (CC BY-NC 4.0) 
 * Copyright (c) 2018 Joey DeVries
 * 
 * Full License: https://creativecommons.org/licenses/by-nc/4.0/legalcode
 *
 * Changes made by Robert Slattery
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <cstdint>
#include <assert.h>
#include <initializer_list>
#include <array>
#include <vector>

template<std::size_t n, class T>
struct svector 
{

public:
        
    std::array<T, n> data;
    
    explicit svector() {}
    
    svector(const T& v)
    {
        for (auto& element : data)
            element = v;
    }
    
    svector(const std::initializer_list<T> args)
    {
        assert(args.size() < n);
        data = args;
    }
    
    T& operator[](const std::size_t index)
    {
        assert(index >= 0 && index < n);
        return data.at(index);
    }
    
    svector<n, T> operator-();
    svector<n, T> operator==(svector<n, T>& lhs);
    svector<n, T> operator!=(svector<n, T>& lhs);
    svector<n, T> operator%(svector<n, T>& lhs);

};

//~ 2D Vectors
template<typename T>
struct svector<2, T>
{
    union
    {
        std::array<T, 2> data;
        
        struct
        {
            T x;
            T y;
        };
    };
    
    static const svector<2, T> zero_vector;
    static const svector<2, T> forward_vector;
    static const svector<2, T> back_vector;
    static const svector<2, T> right_vector;
    static const svector<2, T> left_vector;
    
    inline int distance(const svector<2, T>& other) const // manhattan: 4 directions(right, left, top, bottom)
    {
        return (abs(other.x - x) + abs(other.y - y));
    }
    
    inline void set(const T& _x, const T& _y)
    {
        x = _x;
        y = _y;
    }
    
    explicit svector() { data = {}; }
    explicit svector(const T& v) { data = { v, v }; }
    
    // accept any number of arguments
    svector(const std::initializer_list<T> args)
    {
        assert(args.size() <= 2);
        int index = 0;
        
        for (auto begin = args.begin(); begin != args.end(); ++begin)
            data.at(index++) = *begin;
    }
    
    svector(const T& _x, const T& _y) 
    {
        data = { _x, _y };
    }
    
    T& operator[](const std::size_t index)
    {
        assert(index >= 0 && index < 2);
        return data.at(index);
    }
    
    svector<2, T> operator-();
    svector<2, T> operator==(svector<2, T>& lhs);
    svector<2, T> operator!=(svector<2, T>& lhs);
    svector<2, T> operator%(svector<2, T>& lhs);
    
    bool operator==(const svector<2, T>& A) const
    {
        return (x == A.x && y == A.y);
    }
    
    bool operator!=(const svector<2, T>& A) const
    {
        return (x != A.x || y != A.y);
    }
    
    bool operator <(const svector<2, T>& A) const
    {
        return (x < A.x || y < A.y);
    }
    
    bool operator >(const svector<2, T>& A) const
    {
        return (x > A.x || y > A.y);
    }
    
    bool operator%(const svector<2, T>& A) const
    {
        return (x % A.x && y % A.y);
    }
};

//~ 3D Vectors
template<typename T>
struct svector<3, T>
{
    union
    {
        std::array<T, 3> data;
            
        struct
        {
            T x;
            T y;
            T z;
        };
        
        struct
        {
            svector<2, T> xy;
        };
        
        struct
        {
            svector<2, T> yz;
        };
    };
    
    inline int distance(const svector<3, T>& other) const
    {
        //return (abs(other.x - x) + abs(other.y - y));
        return {abs(other.x - x) , abs(other.y - y), abs(other.z - z)};
    }
    
    inline void set(const T& _x, const T& _y, const T& _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
    
    static const svector<3, T> zero_vector;
    static const svector<3, T> up_vector;
    static const svector<3, T> down_vector;
    static const svector<3, T> forward_vector;
    static const svector<3, T> back_vector;
    static const svector<3, T> right_vector;
    static const svector<3, T> left_vector;
        
    explicit svector() { data = {}; }
    explicit svector(const T& v) { data = { v, v, v }; }
        
    // accept any number of arguments
    svector(const std::initializer_list<T> args)
    {
        assert(args.size() <= 3);
        int index = 0;
        
        for (auto begin = args.begin(); begin != args.end(); ++begin)
            data.at(index++) = *begin;
    }
        
    svector(const T& _x, const T& _y, const T& _z)  { data = { _x, _y , _z }; }
    
    svector(const svector<2, T>& _vec, const T& _z) { data = { _vec.x, _vec.y, _z }; }
    
    svector(const T& _x, const svector<2, T>& _vec) { data = { _x, _vec.x, _vec.y }; }
    
    T& operator[](const std::size_t index)
    {
        assert(index >= 0 && index < 3);
        return data.at(index);
    }
    
    svector<3, T> operator-();
    svector<3, T> operator==(svector<3, T>& lhs);
    svector<3, T> operator!=(svector<3, T>& lhs);
    svector<3, T> operator%(svector<3, T>& lhs);
    
    bool operator==(const svector<3, T>& A) const
    {
        return (x == A.x && y == A.y && z == A.z);
    }
    
    bool operator!=(const svector<3, T>& A) const
    {
        return (x != A.x || y != A.y || z != A.z);
    }
    
    bool operator +(const svector<3, T>& A) const
    {
        return { x + A.x, y + A.y, z + A.z };
    }
    
    bool operator <(const svector<3, T>& A) const
    {
        return { x < A.x, y < A.y, z < A.z };
    }
    
    bool operator%(const svector<3, T>& A) const
    {
        return (x % A.x && y % A.y && z % A.z);
    }
    
    svector& operator=(const svector& other) 
    { 
        x = other.x;
        y = other.y;
        z = other.z;
        xy = other.xy;
        yz = other.yz;
        return *this; 
    }

};

template<typename T> 
svector<2, T> const svector<2, T>::zero_vector = svector<2, T>(0.0, 0.0);

template<typename T> 
svector<2, T> const svector<2, T>::forward_vector = svector<2, T>(0.0, 1.0);

template<typename T> 
svector<2, T> const svector<2, T>::back_vector = svector<2, T>(0.0, -1.0);

template<typename T> 
svector<2, T> const svector<2, T>::right_vector = svector<2, T>(1.0, 0.0);

template<typename T> 
svector<2, T> const svector<2, T>::left_vector = svector<2, T>(-1.0, 0.0);


template<typename T> 
svector<3, T> const svector<3, T>::zero_vector = svector<3, T>(0.0, 0.0, 0.0);

template<typename T> 
svector<3, T> const svector<3, T>::up_vector = svector<3, T>(0.0, 1.0, 0.0);

template<typename T> 
svector<3, T> const svector<3, T>::down_vector = svector<3, T>(0.0, -1.0, 0.0);

template<typename T> 
svector<3, T> const svector<3, T>::forward_vector = svector<3, T>(0.0, 0.0, 1.0);

template<typename T> 
svector<3, T> const svector<3, T>::back_vector = svector<3, T>(0.0, 0.0, -1.0);

template<typename T> 
svector<3, T> const svector<3, T>::right_vector = svector<3, T>(1.0, 0.0, 0.0);

template<typename T> 
svector<3, T> const svector<3, T>::left_vector = svector<3, T>(-1.0, 0.0, 0.0);

//~ Set type names
typedef svector<2, int> vector2_i;
typedef svector<3, int> vector3_i;
typedef svector<2, float> vector2_f;
typedef svector<3, float> vector3_f;
typedef svector<2, double> vector2_d;
typedef svector<3, double> vector3_d;
typedef std::vector<svector<2, int>> vector2_array_i;
typedef std::vector<svector<2, float>> vector2_array_f;
typedef std::vector<svector<2, double>> vector2_array_d;
typedef std::vector<svector<3, int>> vector3_array_i;
typedef std::vector<svector<3, float>> vector3_array_f;
typedef std::vector<svector<3, double>> vector3_array_d;

template<std::size_t n, typename T>
inline svector<n, T> svector<n, T>::operator -()
{
    svector<n, T> retVal;
    
    for (std::size_t i = 0; i < n; ++i)
        retVal[i] = -data[i];
    
    return retVal;
}

template<std::size_t n, typename T>
inline svector<n, T> svector<n, T>::operator ==(svector<n, T>& lhs)
{
    svector<n, T> retVal;
    
    for (std::size_t i = 0; i < n; ++i)
    {
        if (retVal[i] == lhs[i])
            break;
    }
    
    return retVal;
}

template<std::size_t n, typename T>
inline svector<n, T> svector<n, T>::operator !=(svector<n, T>& lhs)
{
    svector<n, T> retVal;
    
    for (std::size_t i = 0; i < n; ++i)
    {
        if (retVal[i] != lhs[i])
            break;
    }
    
    return retVal;
}

template<std::size_t n, typename T>
inline svector<n, T> svector<n, T>::operator %(svector<n, T>& lhs)
{
    svector<n, T> retVal;
    
    for (std::size_t i = 0; i < n; ++i)
    {
        if (retVal[i] % lhs[i])
            break;
    }
    
    return retVal;
}

template<typename T>
inline svector<2, T> svector<2, T>::operator -()
{
    return { -x, -y };
}

template<typename T>
inline svector<3, T> svector<3, T>::operator -()
{
    return { -x, -y, -z };
}

template<std::size_t n, typename T>
inline svector<n, T> operator +(svector<n, T> lhs, T scale)
{
    svector<n, T> retVal;
    
    for (std::size_t i = 0; i < n; ++i)
        retVal[i] = lhs[i] + scale;
    
    return retVal;
}

template<std::size_t n, typename T>
inline svector<n, T> operator +(T scale, svector<n, T> rhs)
{
    svector<n, T> retVal;
    
    for (std::size_t i = 0; i < n; ++i)
        retVal[i] = rhs[i] + scale;
    
    return retVal;
}

template<std::size_t n, typename T>
inline svector<n, T> operator +(svector<n, T> lhs, svector<n, T> rhs)
{
    svector<n, T> retVal;
    
    for (std::size_t i = 0; i < n; ++i)
        retVal[i] = lhs[i] + rhs[i];
    
    return retVal;
}

template<std::size_t n, typename T>
inline svector<n, T> operator -(svector<n, T> lhs, T scale)
{
    svector<n, T> retVal;
    
    for (std::size_t i = 0; i < n; ++i)
        retVal[i] = lhs[i] - scale;
    
    return retVal;
}

template<std::size_t n, typename T>
inline svector<n, T> operator -(svector<n, T> lhs, svector<n, T> rhs)
{
    svector<n, T> retVal;
    
    for (std::size_t i = 0; i < n; ++i)
        retVal[i] = lhs[i] - rhs[i];
    
    return retVal;
}

template<std::size_t n, typename T>
inline svector<n, T> operator *(svector<n, T> lhs, T scale)
{
    svector<n, T> retVal;
    
    for (std::size_t i = 0; i < n; ++i)
        retVal[i] = lhs[i] * scale;
    
    return retVal;
}

template<std::size_t n, typename T>
svector<n, T>& operator *=(svector<n, T>& lhs, T scale)
{
    for (std::size_t i = 0; i < n; ++i)
        lhs[i] *= scale;
    
    return lhs;
}

template<std::size_t n, typename T>
inline svector<n, T> operator *(T scale, svector<n, T> lhs)
{
    svector<n, T> retVal;
    
    for (std::size_t i = 0; i < n; ++i)
        retVal[i] = lhs[i] * scale;
    
    return retVal;
}

template<std::size_t n, typename T>
inline svector<n, T> operator *(svector<n, T> lhs, svector<n, T> rhs)
{
    svector<n, T> retVal;
    
    for (std::size_t i = 0; i < n; ++i)
        retVal[i] = lhs[i] * rhs[i];
    
    return retVal;
}

template<std::size_t n, typename T>
inline svector<n, T> operator /(svector<n, T> lhs, T scale)
{
    svector<n, T> retVal;
    
    for (std::size_t i = 0; i < n; ++i)
        retVal[i] = lhs[i] / scale;
    
    return retVal;
}

template<std::size_t n, typename T>
inline svector<n, T> operator /(T scale, svector<n, T> lhs)
{
    svector<n, T> retVal;
    
    for (std::size_t i = 0; i < n; ++i)
        retVal[i] = lhs[i] / scale;
    
    return retVal;
}

template<std::size_t n, typename T>
inline svector<n, T> operator /(svector<n, T> lhs, svector<n, T> rhs)
{
    svector<n, T> retVal;
    
    for (std::size_t i = 0; i < n; ++i)
        retVal[i] = lhs[i] / rhs[i];
    
    return retVal;
}

template<std::size_t n, typename T>
inline svector<n, T> operator <(svector<n, T> lhs, svector<n, T> rhs)
{
    svector<n, T> retVal;
    
    for (std::size_t i = 0; i < n; ++i)
        retVal[i] = lhs[i] < rhs[i];
    
    return retVal;
}

#endif /* VECTOR_H */

