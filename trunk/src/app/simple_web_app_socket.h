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
#ifndef __SIMPLE_WEB_APP_SOCKET_HEADER__
#define __SIMPLE_WEB_APP_SOCKET_HEADER__
#include "../core/simple_web_core.h"
#include "../core/simple_web_core_buffer.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <csignal>

#include <st.h>
namespace SimpleWebSocket
{
    // using state thread
    static const int MAX_LENGTH_TO_QUEUE_OF_LISTEN_SOCKET = 5;
    static const int MAX_LENGHT_FROM_SOCKET = 1024;
    class BaseSocket
    {
    public:
        BaseSocket();
        virtual ~BaseSocket();
    public:
        virtual int initialize(std::string ip, long port) = 0;
    };

    class TCPServerSock:BaseSocket
    {
    public:
        TCPServerSock();
        virtual ~TCPServerSock();
    private:
        //int server_socket_;
        long host_port_;
        st_netfd_t st_nfd_;
    public:
        int initialize(std::string ip, long port);
        st_netfd_t accept_socket();
    };

    class HTTPTCPConnSock:BaseSocket,SimpleWebCoreBuffer
    {
    public:
        HTTPTCPConnSock();
        HTTPTCPConnSock(st_netfd_t sock);
        virtual ~HTTPTCPConnSock();
    private:
        st_netfd_t conn_socket_;
    public:
        int initialize(std::string ip, long port);
        bool get_http_header_message(std::string& message);
        //bool send_msg(std::string msg, long msg_length);
        virtual int read(std::string buf, int size);
        virtual int write(std::string buf, int size);
    };
};


#endif

