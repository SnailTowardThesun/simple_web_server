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
#ifndef SIMPLE_WEB_APP_THREAD_H
#define SIMPLE_WEB_APP_THREAD_H

#include "../core/simple_web_core.h"
#include <st.h>

static const long DEFAULT_HTTP_SERVER_PORT = 8080;
static const long MAX_BIND_ADDR = 16;
static const long MAX_THREAD = 8;
class SimpleWebAppThread
{
public:
    SimpleWebAppThread();
    virtual ~SimpleWebAppThread();
private:
    st_thread_t tid;
public:
    virtual long start();
    virtual long stop();
    virtual long thread_func();
protected:
    static void* thread_cycle(void* arg);
};

#endif
