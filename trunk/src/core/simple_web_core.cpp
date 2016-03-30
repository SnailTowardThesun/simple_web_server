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

#include "simple_web_core.h"
#include "../kernel/simple_web_kernel_sources_control.h"
#include <st.h>
long simple_web_initialize()
{
    // initialize the source control 
    if (SimpleWebKernelSourcesCtl::getInstance()->initialize() != RESULT_OK) {
        simple_web_app_log::log("help", "simple_web_core.cpp", "SimpleWebKernelSourcesCtl initialize failed");
        return RESULT_ERROR;
    }
    // initialize the st library
    st_set_eventsys(ST_EVENTSYS_ALT);
    if (st_init() < 0) {
        simple_web_app_log::log("help", "simple_web_core.cpp", "state thread initialize failed");
        return RESULT_ERROR;
    }
    std::cout<<"get event's name "<<st_get_eventsys_name()<<std::endl;
    return RESULT_OK;
}
