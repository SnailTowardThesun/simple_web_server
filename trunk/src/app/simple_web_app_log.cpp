/*
The MIT License (MIT)

Copyright (c) 2016 ME_Kun_Han

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "simple_web_app_log.h"
#include <stdio.h>
#include <stdarg.h>

#define DEFAULT_SIMPLE_WEB_LOG_FILE "simple_web.log"
#define LOG_MAX_SIZE 4096
simple_web_app_log::simple_web_app_log() :
    log_file_name(DEFAULT_SIMPLE_WEB_LOG_FILE),
    log_data(NULL)
{
    log_data = new char[LOG_MAX_SIZE];
}

simple_web_app_log::~simple_web_app_log()
{
    if(log_data != NULL) delete[] log_data;
}

int simple_web_app_log::log(std::string level_name, std::string tag, const char *fmt, ...)
{
    char tmp[LOG_MAX_SIZE];
    va_list ap;
    va_start(ap,fmt);
    vsnprintf(tmp, LOG_MAX_SIZE, (char*)fmt, ap);
    va_end(ap);
    std::cout<<"["<<level_name<<"]"<<"["<<tag<<"]"<<tmp<<std::endl;
    return 0;
}

