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
#include "../protocol/simple_web_protocol_http.h"
SimpleWebKernelHttpServer::SimpleWebKernelHttpServer():p_socket_(NULL)
{
    p_socket_ = new SimpleWebSocket::TCPServerSock();
}

SimpleWebKernelHttpServer::~SimpleWebKernelHttpServer()
{
    if(p_socket_ != NULL) delete p_socket_;
}

void* SimpleWebKernelHttpServer::recv_thread(void* pParam)
{
    SimpleWebSocket::HTTPTCPConnSock* sock = (SimpleWebSocket::HTTPTCPConnSock*)pParam;
    SimpleWebHttp::SimpleWebProtocolHttp http;
    // recv the client's request
    std::string http_request;
    while(sock->get_http_header_message(http_request)) {
        if(http.deal_with_request(http_request) == NULL) {
            break;
        }
        // send the file
    }
    return 0;
}

int SimpleWebKernelHttpServer::initialize(long port = DEFAULT_HTTP_SERVER_PORT)
{
    // initialize the socket
    if(p_socket_->initialize("",port) != RESULT_ERROR) {
        simple_web_app_log::log("error","simple_web_kernel_http_server.cpp","fail to initialize socket");
        return RESULT_ERROR;
    }
    return RESULT_OK;
}

int SimpleWebKernelHttpServer::loop()
{
    while(1) {
        SimpleWebSocket::HTTPTCPConnSock* conn_socket = new SimpleWebSocket::HTTPTCPConnSock(p_socket_->accept_socket());
        pthread_t thread;
        pthread_create(&thread,NULL,recv_thread,(void*)conn_socket);
    }
    return RESULT_OK;
}
