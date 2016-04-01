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
#include <fstream>

SimpleWebKernelHttpServer::SimpleWebKernelHttpServer()
{
}

SimpleWebKernelHttpServer::~SimpleWebKernelHttpServer()
{
}

int SimpleWebKernelHttpServer::initialize(std::string ip, long port = DEFAULT_HTTP_SERVER_PORT)
{
    // initialize the socket
    if (srv_sock_.initialize(ip,port) == RESULT_ERROR) {
        simple_web_app_log::log("error","simple_web_kernel_http_server.cpp","fail to initialize socket");
        return RESULT_ERROR;
    }
    return RESULT_OK;
}

long SimpleWebKernelHttpServer::thread_func()
{
    std::string request_str;
    SimpleWebSocket::HTTPTCPConnSock* conn_sock = new SimpleWebSocket::HTTPTCPConnSock();
    SimpleWebHttp::SimpleWebProtocolHttp http_decoder;
    for (;;) {
        st_netfd_t sock_client = srv_sock_.accept_socket();
        if (sock_client == NULL) {
            simple_web_app_log::log("error", "simple_web_kernel_http_server.cpp", "accept socket failed");
            break;
        }
        conn_sock->set_sock(sock_client);
        if (conn_sock->get_http_header_message(request_str)) {
            http_decoder.deal_with_request(request_str, conn_sock);
        }
        conn_sock->close_sock();
    }
    delete conn_sock;
    return RESULT_OK;
}
