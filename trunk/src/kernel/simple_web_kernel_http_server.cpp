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
#include "simple_web_kernel_http_server.h"

simple_web_kernel_http_server::simple_web_kernel_http_server():p_socket_(NULL)
{
    p_socket_ = new simple_web_socket::TCPServerSock();
}

simple_web_kernel_http_server::~simple_web_kernel_http_server()
{
    if(p_socket_ != NULL) delete p_socket_;
}

int simple_web_kernel_http_server::initialize(long port = DEFAULT_HTTP_SERVER_PORT)
{
    // initialize the socket
    if(p_socket_->initialize("",port) != RESULT_ERROR) {
        simple_web_app_log::log("error","simple_web_kernel_http_server.cpp","fail to initialize socket");
        return RESULT_ERROR;
    }
    return RESULT_OK;
}

int simple_web_kernel_http_server::loop()
{
    while(1) {
        simple_web_socket::TCPConnSock* conn_socket = new simple_web_socket::TCPConnSock(p_socket_->accept_socket());
        // recv the client's request
        // decode the request and make up the response
        // send the response to client
    }
    return RESULT_OK;
}
