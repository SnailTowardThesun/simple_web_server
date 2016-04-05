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

#include "simple_web_app_thread.h"
static const long DEFAULT_MAX_THREADS = 4;

SimpleWebAppThread::SimpleWebAppThread():tid(NULL)
{

}

SimpleWebAppThread::~SimpleWebAppThread()
{

}

long SimpleWebAppThread::start()
{
    // start
    if (tid != NULL) {
        simple_web_app_log::log("warning", "simpe_web_app_thread.cpp", "the thread is running");
        return RESULT_ERROR;
    }
    if ((tid = st_thread_create(thread_cycle, this, 0, 0)) == NULL) {
        simple_web_app_log::log("error", "simpe_web_app_thread.cpp", "st create thread failed");
        return RESULT_ERROR;
    }
    return RESULT_OK;
}

long SimpleWebAppThread::stop()
{
    if (tid != NULL) {
    }
    tid = NULL;
    return RESULT_OK;
}

long SimpleWebAppThread::thread_func()
{
    simple_web_app_log::log("trace", "simple_web_app_thread.cpp", "step into base thread");
    return RESULT_OK;
}

void* SimpleWebAppThread::thread_cycle(void* param) {
    // base class just show a log
    SimpleWebAppThread *pC = (SimpleWebAppThread *) param;
    pC->thread_func();
    simple_web_app_log::log("trace", "simple_web_app_thread.cpp", "ready to exit trehad");
    return NULL;
}

