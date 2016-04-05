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
using namespace SimpleWebSocket;

BaseSocket::BaseSocket()
{

}

BaseSocket::~BaseSocket()
{

}

TCPServerSock::TCPServerSock() : host_port_(0),
    st_nfd_(NULL)
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
    int server_socket_ = socket(AF_INET,SOCK_STREAM,0);
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
    if ((st_nfd_ = st_netfd_open(server_socket_)) == NULL) {
        simple_web_app_log::log("error","simple_web_app_socket.cpp","fail to open st netfd");
        return RESULT_ERROR;
    }
    if (st_netfd_serialize_accept(st_nfd_) < 0) {
        simple_web_app_log::log("error","simple_web_app_socket.cpp","fail to accept");
        return RESULT_ERROR;
    }
    return RESULT_OK;
}

st_netfd_t TCPServerSock::accept_socket()
{
    struct sockaddr_in client_name;
    int client_name_len = sizeof(client_name);
    st_netfd_t conn_socket = st_accept(st_nfd_, (struct sockaddr *)&client_name, &client_name_len, ST_UTIME_NO_TIMEOUT);
    return conn_socket;
}

HTTPTCPConnSock::HTTPTCPConnSock():conn_socket_(NULL)
{

}

HTTPTCPConnSock::HTTPTCPConnSock(st_netfd_t sock):conn_socket_(sock)
{

}

HTTPTCPConnSock::~HTTPTCPConnSock()
{
    if(conn_socket_ != NULL) {
        st_netfd_close(conn_socket_);
    }
}

int HTTPTCPConnSock::initialize(std::string ip, long port)
{
    if(!ip.empty()){
        simple_web_app_log::log("trace","simple_web_app_socket.cpp","the ip is not empty");
    }
    if(port < 1) {
        simple_web_app_log::log("help","simple_web_app_sokcet.cpp","the port is illegal");
        return RESULT_ERROR;
    }
    return RESULT_OK;
}

bool HTTPTCPConnSock::get_http_header_message(std::string& message)
{
    message.clear();
    buffer_.clear();
    // end with \r\n\r\n
    bool isEnd = false;
    char c = '\0';
    while(!isEnd) {
        if(st_read(conn_socket_,&c,1,1000) == 0) break;
        buffer_ += c;
        // if got \n
        if(c == '\r') {
            if(st_read(conn_socket_,&c,1,1000) == 0) break;
            buffer_ += c;
            if(c == '\n') {
                if(st_read(conn_socket_,&c,1,1000) == 0) break;
                buffer_ += c;
                if(c == '\r') {
                    if(st_read(conn_socket_,&c,1,1000) == 0) break;
                    buffer_ += c;
                    if(c == '\n') {
                        buffer_ += c;
                        isEnd = true;
                    }
                }
            }
        }
    }
    message = buffer_;
    message.erase(0,message.find_first_not_of('\0'));
    message.erase(message.find_last_not_of('\0')+1);
    return (!message.empty());
}

int HTTPTCPConnSock::read(std::string buf, int size)
{
    int ret = 0;
    return ret;
}

int HTTPTCPConnSock::write(std::string buf, int size)
{
    return st_write(conn_socket_, buf.c_str(), size, ST_UTIME_NO_TIMEOUT);
}
