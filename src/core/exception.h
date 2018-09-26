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

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <fstream>
#include <cstdarg>

// Types of exceptions
class exceptions
{
    
public:
    
    static const int standard = 81799;
    
};

// An exception you are not allowed to catch.  Means fatal error in code.
class exception : public std::exception
{
    
public:

    exception() 
    {
        code = 0;
        line = 0;
    }

    exception(
          int _code
        , const std::string& _err
        , const std::string& _func
        , const std::string& _file
        , int _line) :
          code(_code)
        , err(_err)
        , func(_func)
        , file(_file)
        , line(_line)
    {
        format_message();
    }
    
    virtual ~exception() throw() {}

    // Override the error description and the context as a string
    virtual const char *what() const throw() { return msg.c_str(); }
    
    void format_message()
    {
        if (func.size() > 0)
            msg = format("%s:%d: error: (%d) %s in function %s\n", file.c_str(), line, code, err.c_str(), func.c_str());
        else
            msg = format("%s:%d: error: (%d) %s\n", file.c_str(), line, code, err.c_str());
    }

    std::string msg; 

    int code;           // Error code
    std::string err;    // Description
    std::string func;   // Function name. Available only when the compiler supports __func__ macro
    std::string file;   // Source file name where the error has occured
    int line;           // Line number in the source file where the error has occured

private:
    
    inline std::string format(const char* fmt, ...)
    {
        char buffer[1 << 16];
        va_list args;
        va_start(args, fmt);
        vsprintf(buffer, fmt, args);
        return std::string(buffer);
    }
};

#endif /* EXCEPTION_H */

