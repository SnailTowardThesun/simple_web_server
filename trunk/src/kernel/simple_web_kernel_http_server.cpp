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

SimpleWebKernelHttpServer::SimpleWebKernelHttpServer() {
    srv_socket.sock = new SimpleWebSocket::TCPServerSock();
}

SimpleWebKernelHttpServer::~SimpleWebKernelHttpServer()
{
    if(srv_socket.sock != NULL) delete srv_socket.sock;
}

void* SimpleWebKernelHttpServer::recv_thread(void* pParam)
{
#ifdef USING_ST
    simple_web_app_log::log("trace","simple_web_kernel_http_server.cpp","step into thread");
    socket_info* socket = (socket_info*)pParam;
    while (socket->wait_threads < MAX_THREAD) {
       st_netfd_t sock_client = socket->sock->accept_socket();
       if (sock_client == NULL) {
        simple_web_app_log::log("error","simple_web_kernel_http_server.cpp","fail to accept socket");
        continue;
       }
       socket->wait_threads--;
       socket->busy_threads++;
       if(socket->wait_threads < 0 && socket->wait_threads + socket->busy_threads < MAX_THREAD) {
           if (st_thread_create(recv_thread, socket, 0, 0) != NULL) {
               socket->wait_threads++;
           }
       }
       // handle the socket
       SimpleWebSocket::HTTPTCPConnSock* conn_sock = new SimpleWebSocket::HTTPTCPConnSock(sock_client);
       std::string request_header;
       SimpleWebHttp::SimpleWebProtocolHttp http;
       long message_size = 0;
       while (conn_sock->get_http_header_message(request_header)) {
           if(!http.deal_with_request(request_header, conn_sock)) {
               break;
           }
       }

       socket->wait_threads++;
       socket->busy_threads--;
    }
#else
    simple_web_app_log::log("trace", "simple_web_kernel_http_server.cpp", "get one connection");
    SimpleWebSocket::HTTPTCPConnSock* sock = (SimpleWebSocket::HTTPTCPConnSock*)pParam;
    SimpleWebHttp::SimpleWebProtocolHttp http;
    // recv the client's request
    std::string http_request;
    while(sock->get_http_header_message(http_request)) {
        if(!http.deal_with_request(http_request,sock)) {
            break;
        }
    }
#endif
    return 0;
}

int SimpleWebKernelHttpServer::initialize(long port = DEFAULT_HTTP_SERVER_PORT)
{
    // initialize the socket
    if(srv_socket.sock->initialize("",port) == RESULT_ERROR) {
        simple_web_app_log::log("error","simple_web_kernel_http_server.cpp","fail to initialize socket");
        return RESULT_ERROR;
    }
    return RESULT_OK;
}

int SimpleWebKernelHttpServer::loop()
{
#ifdef USING_ST
    simple_web_app_log::log("trace","simple_web_kernel_http_server.cpp","step into thread");
    socket_info* socket = (socket_info*)&srv_socket;
    while (socket->wait_threads < MAX_THREAD) {
       st_netfd_t sock_client = socket->sock->accept_socket();
       if (sock_client == NULL) {
        simple_web_app_log::log("error","simple_web_kernel_http_server.cpp","fail to accept socket");
        continue;
       }
       socket->wait_threads--;
       socket->busy_threads++;
       if(socket->wait_threads < 0 && socket->wait_threads + socket->busy_threads < MAX_THREAD) {
           if (st_thread_create(recv_thread, socket, 0, 0) != NULL) {
               socket->wait_threads++;
           }
       }
       // handle the socket
       SimpleWebSocket::HTTPTCPConnSock* conn_sock = new SimpleWebSocket::HTTPTCPConnSock(sock_client);
       std::string request_header;
       SimpleWebHttp::SimpleWebProtocolHttp http;
       long message_size = 0;
       while (conn_sock->get_http_header_message(request_header)) {
           if(!http.deal_with_request(request_header, conn_sock)) {
               break;
           }
       }

       socket->wait_threads++;
       socket->busy_threads--;
    }
    /*
    for (int i =0; i < MAX_THREAD; i++) {
        if (st_thread_create(recv_thread, (void*)&srv_socket, 0, 0) == NULL) {
            simple_web_app_log::log("error","simple_web_kernel_http_server.cpp","fail to create recv thread");
            continue;
        }
        srv_socket.wait_threads++;
    }
    */
    char c = getchar();
#else
    int sock_client = 0;
    while(1) {
        if((sock_client = p_socket_->accept_socket()) == -1) {
            sleep(1);
            continue;
        }
        SimpleWebSocket::HTTPTCPConnSock* conn_socket = new SimpleWebSocket::HTTPTCPConnSock(sock_client);
        pthread_t thread;
        pthread_create(&thread,NULL,recv_thread,(void*)conn_socket);
    }
#endif
    return RESULT_OK;
}
