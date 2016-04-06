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

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <cerrno>
#include <fcntl.h>
#include <cstring>
#include "simple_web_app_poll_thread.h"
#ifdef FOR_DEBUG
SimpleWebAppPollThread::SimpleWebAppPollThread() : signal_in_class(true),
                                                   epoll_fd(NULL),
                                                   events(NULL)
#else
SimpleWebAppPollThread::SimpleWebAppPollThread()
#endif
{
}

SimpleWebAppPollThread::~SimpleWebAppPollThread()
{
    if (!poll_event_list.empty()) {
        poll_event_list.clear();
    }
    if(events != NULL){
        realloc(events, sizeof(epoll_event) * max_event_num);
    }
}

#ifdef FOR_DEBUG
long SimpleWebAppPollThread::create_socket_bind()
{
    if (listen_socket_fd != NULL) {
        simple_web_app_log::log("error", "simple_web_app_poll_thread.cpp"
                , "the thread is running");
        return RESULT_ERROR;
    }
    listen_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_socket_fd == -1) {
        simple_web_app_log::log("error", "simple_web_app_poll_thread.cpp", "create socket failed");
        return RESULT_ERROR;
    }
    struct sockaddr_in name;
    unsigned short host_port_ = default_port;
    name.sin_family = AF_INET;
    name.sin_port = htons(host_port_);
    name.sin_addr.s_addr = htonl(INADDR_ANY);// the default ip address.
    // bind the socket
    if(bind(listen_socket_fd,(const sockaddr*)&name,sizeof(name)) < 0) {
        simple_web_app_log::log("error","simple_web_app_poll_thread.cpp","fail to bind the socket");
        return RESULT_ERROR;
    }
    // make socket no block
    if (make_socket_non_blocking(listen_socket_fd) == RESULT_ERROR) {
        simple_web_app_log::log("error", "simpel_web_app_poll_thread.cpp"
                , "make socket no block failed");
        return RESULT_ERROR;
    }
    // begin to listen and set the default queue at 100;
    if(listen(listen_socket_fd, 100) < 0) {
        simple_web_app_log::log("error", "simple_web_app_socket.cpp", "fail to listen");
        close(listen_socket_fd);
        return RESULT_ERROR;
    }
    return RESULT_OK;
}

long SimpleWebAppPollThread::make_socket_non_blocking(int infd)
{    
    int flags, s;
    flags = fcntl(infd, F_GETFL, 0);
    if (flags == -1) {
        simple_web_app_log::log("error", "simple_web_app_poll_thread.cpp", "fcntl failed");
        return -1;
    }

    flags |= O_NONBLOCK;
    s = fcntl(infd, F_SETFL, flags);
    if (s == -1) {
        simple_web_app_log::log("error", "simple_web_app_poll_thread.cpp", "fcntl failed");
        return -1;
    }
    return 0;
}
#endif

long SimpleWebAppPollThread::initialize()
{
    // create the listen socket
    if (create_socket_bind() == RESULT_ERROR) {
        simple_web_app_log::log("error", "simpel_web_app_epoll_thread.cpp"
                , "create socket, bind it and listen failed");
        return RESULT_ERROR;
    }
    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        simple_web_app_log::log("error", "simple_web_app_poll_thread.cpp", "create the epoll failed");
        return RESULT_ERROR;
    }
    event.data.fd = listen_socket_fd;
    event.events = EPOLLIN | EPOLLET;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_socket_fd, &event) == -1) {
        simple_web_app_log::log("error", "simple_web_app_poll_thread.cpp", "epoll control failed");
        return RESULT_ERROR;
    }
    if (events != NULL) {
        delete events;
        events = NULL;
    }
    events = (epoll_event*)malloc(sizeof(epoll_event) * max_event_num);

    return RESULT_OK;
}

long SimpleWebAppPollThread::loop()
{
    long ret = RESULT_OK;
    while(signal_in_class) {
        // loop to get the epoll singnal
        int i = 0;
        simple_web_app_log::log("trace", "simple_web_app_poll_thread.cpp", "step into while loop");
        int n = epoll_wait(epoll_fd, events, max_event_num, -1);
        if(n == -1) {
            simple_web_app_log::log("error", "simple_web_app_poll_thread.cpp", "epoll wait failed");
            return RESULT_ERROR;
        }
        for (i = 0; i < n; i++) {
            std::cout<<"n is "<<n<<" i is "<<i<<std::endl;
            if((events[i].events & EPOLLERR)
               || (events[i].events & EPOLLHUP)
               || !(events[i].events & EPOLLIN)) {
                simple_web_app_log::log("error", "smple_web_app_poll_thread.cpp"
                        , "epoll failed");
                close(events[i].data.fd);
                break;
            }
            if (listen_socket_fd == events[i].data.fd) {
                struct sockaddr in_addr;
                socklen_t in_len;
                int infd;
                char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
                in_len = sizeof in_addr;
                infd = accept(listen_socket_fd, &in_addr, &in_len);
                if (infd == -1) {
                    if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                        simple_web_app_log::log("trace", "simple_web_app_poll_thread.cpp"
                                , "the errno is EAGAIN when accepting the socket");
                        break;
                    }
                    else {
                        simple_web_app_log::log("error", "simple_web_app_poll_thread.cpp"
                                , "accept socket failed");
                        break;
                    }
                }

                int s = getnameinfo(&in_addr, in_len, hbuf, sizeof hbuf, sbuf, sizeof sbuf, NI_NUMERICHOST | NI_NUMERICSERV);
                if (s == 0) {
                    printf("Accepted connection on descriptor %d (host=%s, port=%s)\n", infd, hbuf, sbuf);
                }

                s = (int) make_socket_non_blocking(infd);
                if (s == -1) {
                    abort();
                }

                event.data.fd = infd;
                event.events = EPOLLIN | EPOLLET;
                s = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, infd, &event);
                if (s == -1) {
                    simple_web_app_log::log("error", "simple_web_app_poll_thread.cpp", "epoll ctl failed");
                    abort();
                }
                simple_web_app_log::log("trace", "simple_web_app_poll_thread.cpp", "successed in accepting one socket");
            } else {
                do_with_fd(events[i].data.fd);
            }
        }
    }
    return ret;
}

long SimpleWebAppPollThread::do_with_fd(int fd)
{
    int done = 0;
    while (1) {
        char buf[512];
        ssize_t count = read(fd, buf, sizeof buf);
        if (count == -1) {
            if(errno != EAGAIN) {
                done = 1;
            }
            break;
        }
        else if(count == 0) {
            done = 1;
            break;
        }
        // judge whether we get the the whole message
        char resp[] = "HTTP/1.0 200 OK\r\nContent-type: text/html\r\nContent-Length: 18\r\n"
                "Connection: close\r\n\r\n<H2>It worked!</H2>\n";
        ssize_t s = write(fd, resp, sizeof(resp) - 1);
        simple_web_app_log::log("trace", "simple_web_app_poll_thread.cpp", "success in sending msg");
        if (s == -1) {
            perror("write");
            abort();
        }
        simple_web_app_log::log("trace", "simple_web_app_poll_thread.cpp", "successed in dealing one connection");
    }
    if (done == 1) {
        printf("Closed connection on descriptor %d\n", fd);
        close(fd);
    }
    return RESULT_OK;
}
