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
#include "core/simple_web_core.h"
#include "kernel/simple_web_kernel_http_server.h"
#include "app/simple_web_app_poll_thread.h"
int main(int argc,char** argv)
{
    // initialize the global varibales
    if (simple_web_initialize("/home/hankun/github/simple_web_server/trunk/objs/www") != RESULT_OK) {
        simple_web_app_log::log("error","simple_web_server.cpp","fail to initialize the SourceCtl part");
        return -1;
    }
    SimpleWebAppPollThread th;
    th.initialize();
    return th.loop();
    /*
    // start a http server
    SimpleWebKernelHttpServer http_server;
    if(http_server.initialize("",9090) == RESULT_ERROR) return -1;
    return http_server.loop();
     */
}
