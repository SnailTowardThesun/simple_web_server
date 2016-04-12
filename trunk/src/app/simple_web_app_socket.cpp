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
#include <simple_web_app_socket.h>
using namespace SimpleWebSocket;

#define MAX_LENGTH_TO_QUEUE_OF_LISTEN_SOCKET 5
#define TIME_OUT_LIMIT 1000000LL * 30

BaseSocket::BaseSocket()
{

}

BaseSocket::~BaseSocket()
{

}

TCPServerSock::TCPServerSock() : host_port(0),
    st_nfd(NULL)
{

}

TCPServerSock::~TCPServerSock()
{

}

int TCPServerSock::initialize(std::string ip, long port)
{
    if (port < 1) {
        simple_web_app_log::log("help", "simple_web_app_socket.cpp", "the port is illegal");
        return RESULT_ERROR;
    }
    if (!ip.empty()){
        simple_web_app_log::log("trace", "simple_web_app_socket.cpp", "the ip is not empty");
    }
    host_port = port;

    // initialize the socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        simple_web_app_log::log("error", "simple_web_app_sock.cpp", "fail to initialize the server socket");
        return RESULT_ERROR;
    }
    // local addr
    struct sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_port = htons((uint16_t)host_port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);// the default ip address.
    // bind the socket
    if (bind(server_socket, (const sockaddr*)&name, sizeof(name)) < 0) {
        simple_web_app_log::log("error", "simple_web_add_sock.cpp", "fail to bind the socket");
        return RESULT_ERROR;
    }
    // begin to listen
    if (listen(server_socket, MAX_LENGTH_TO_QUEUE_OF_LISTEN_SOCKET) < 0) {
        simple_web_app_log::log("error", "simple_web_app_socket.cpp", "fail to listen");
        return RESULT_ERROR;
    }
    if ((st_nfd = st_netfd_open(server_socket)) == NULL) {
        simple_web_app_log::log("error", "simple_web_app_socket.cpp", "fail to open st netfd");
        return RESULT_ERROR;
    }
    if (st_netfd_serialize_accept(st_nfd) < 0) {
        simple_web_app_log::log("error", "simple_web_app_socket.cpp", "fail to accept");
        return RESULT_ERROR;
    }
    return RESULT_OK;
}

st_netfd_t TCPServerSock::accept_socket()
{
    struct sockaddr_in client_name;
    int client_name_len = sizeof(client_name);
    st_netfd_t conn_socket = st_accept(st_nfd, (struct sockaddr *)&client_name, &client_name_len, ST_UTIME_NO_TIMEOUT);
    return conn_socket;
}

HTTPTCPConnSock::HTTPTCPConnSock():conn_socket(NULL)
{

}

HTTPTCPConnSock::HTTPTCPConnSock(st_netfd_t sock):conn_socket(sock)
{

}

int HTTPTCPConnSock::set_sock(st_netfd_t sock)
{
   if (conn_socket != NULL) {
       st_netfd_close(conn_socket);
   }
    conn_socket = sock;
    return RESULT_OK;
}

int HTTPTCPConnSock::close_sock()
{
    if(conn_socket != NULL) {
        st_netfd_close(conn_socket);
        conn_socket = NULL;
    }
    return RESULT_OK;
}

HTTPTCPConnSock::~HTTPTCPConnSock()
{
    if (conn_socket != NULL)
        st_netfd_close(conn_socket);
}

int HTTPTCPConnSock::initialize(std::string ip, long port)
{
    if(!ip.empty()){
        simple_web_app_log::log("trace", "simple_web_app_socket.cpp", "the ip is not empty");
    }
    if(port < 1) {
        simple_web_app_log::log("help", "simple_web_app_sokcet.cpp", "the port is illegal");
        return RESULT_ERROR;
    }
    return RESULT_OK;
}

long HTTPTCPConnSock::get_http_header_message(std::string& message)
{
    long ret = RESULT_OK;
    message.clear();
    buffer.clear();
    // end with \r\n\r\n
    bool isEnd = false;
    char c = '\0';
    while (!isEnd) {
        if (st_read(conn_socket, &c, 1, TIME_OUT_LIMIT) == 0) {
            break;
        }
        buffer += c;
        // if got \n
        if (c == '\r') {
            if (st_read(conn_socket, &c, 1, TIME_OUT_LIMIT) == 0) {
                break;
            }
            buffer += c;
            if (c == '\n') {
                if (st_read(conn_socket, &c, 1, TIME_OUT_LIMIT) == 0) {
                    break;
                }
                buffer += c;
                if (c == '\r') {
                    if (st_read(conn_socket, &c, 1, TIME_OUT_LIMIT) == 0) {
                        break;
                    }
                    buffer += c;
                    if (c == '\n') {
                        buffer += c;
                        isEnd = true;
                    }
                }
            }
        }
    }
    message = buffer;
    // delete the '\0'
    message.erase(0, message.find_first_not_of('\0'));
    message.erase(message.find_last_not_of('\0') + 1);
    return (ret = message.empty() ? RESULT_ERROR : RESULT_OK);
}

int HTTPTCPConnSock::read(std::string buf, int size)
{
    int ret = 0;
    return ret;
}

int HTTPTCPConnSock::write(std::string buf, int size)
{
    return st_write(conn_socket, buf.c_str(), size, ST_UTIME_NO_TIMEOUT);
}
