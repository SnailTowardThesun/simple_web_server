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

#ifndef SIMPLE_WEB_KERNEL_SOURCES_H
#define SIMPLE_WEB_KERNEL_SOURCES_H

#include "../core/simple_web_core.h"

class SimpleWebCoreSource;
// this is a static class
// there is only one static object in whole project
class SimpleWebKernelSourcesCtl
{
public:
    SimpleWebKernelSourcesCtl();
    virtual ~SimpleWebKernelSourcesCtl();
private:
    static SimpleWebKernelSourcesCtl*  pInstance_;
public:
    static SimpleWebKernelSourcesCtl* getInstance();

private:
    std::map<std::string,SimpleWebCoreSource*> source_list_;
public:
    long initialize();
    SimpleWebCoreSource* get_source(std::string file_url);
};

#endif