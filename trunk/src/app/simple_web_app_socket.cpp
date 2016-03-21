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

#include "simple_web_app_socket.h"
using namespace simple_web_socket;

BaseSocket::BaseSocket()
{

}

BaseSocket::~BaseSocket()
{

}

TCPServerSock::TCPServerSock() : server_socket_(-1),
    host_port_(0)
{

}

TCPServerSock::~TCPServerSock()
{

}

int TCPServerSock::initialize(std::string ip, long port)
{
    if(port < 1) {
        simple_web_app_log::log("help","simple_web_app_socket.cpp","the port is illegal");
        return RESULT_ERROR;
    }
    if(!ip.empty()){
        simple_web_app_log::log("trace","simple_web_app_socket.cpp","the ip is not empty");
    }
    host_port_ = port;

    // initialize the socket
    server_socket_ = socket(AF_INET,SOCK_STREAM,0);
    if(server_socket_ == -1) {
        simple_web_app_log::log("error","simple_web_app_sock.cpp","fail to initialize the server socket");
        return RESULT_ERROR;
    }
    // local addr
    struct sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_port = htons(host_port_);
    name.sin_addr.s_addr = htonl(INADDR_ANY);// the default ip address.
    // bind the socket
    if(bind(server_socket_,(const sockaddr*)&name,sizeof(name)) < 0) {
        simple_web_app_log::log("error","simple_web_add_sock.cpp","fail to bind the socket");
        return RESULT_ERROR;
    }
    // begin to listen
    if(listen(server_socket_, MAX_LENGTH_TO_QUEUE_OF_LISTEN_SOCKET) < 0) {
        simple_web_app_log::log("error","simple_web_app_socket.cpp","fail to listen");
        return RESULT_ERROR;
    }
    return RESULT_OK;
}
