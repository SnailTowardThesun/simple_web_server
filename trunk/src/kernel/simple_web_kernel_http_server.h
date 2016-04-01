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
#ifndef SIMPLE_WEB_SERVER_SIMPLE_WEB_KERNEL_HTTP_SERVER_H
#define SIMPLE_WEB_SERVER_SIMPLE_WEB_KERNEL_HTTP_SERVER_H

#include "../core/simple_web_core.h"
#include "../app/simple_web_app_socket.h"


#ifdef USING_ST
#include <st.h>
#include "../app/simple_web_app_thread.h"
#else
#include <pthread.h>
#endif

static const long DEFAULT_HTTP_SERVER_PORT = 8080;
class SimpleWebKernelHttpServer : public SimpleWebAppThread
{
#ifdef USING_ST
    SimpleWebSocket::TCPServerSock srv_sock_;
#endif
public:
    SimpleWebKernelHttpServer();
    virtual ~SimpleWebKernelHttpServer();
public:
    int initialize(std::string ip, long port);
    long thread_func();
};

#endif //SIMPLE_WEB_SERVER_SIMPLE_WEB_KERNEL_HTTP_SERVER_H
