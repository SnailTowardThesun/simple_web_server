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
#ifndef SIMPLE_WEB_APP_POLL_THREAD_H
#define SIMPLE_WEB_APP_POLL_THREAD_H

#include "../core/simple_web_core.h"
#include <sys/epoll.h>

#define FOR_DEBUG
#ifdef FOR_DEBUG
static const long default_port = 8080;
static const long max_event_num = 8;
#endif
class SimpleWebAppPollThread
{
public:
    SimpleWebAppPollThread();
    virtual ~SimpleWebAppPollThread();
private:
    std::vector<epoll_event*> poll_event_list;
public:
    virtual long initialize();
    virtual long loop();
    virtual long do_with_fd(int fd);

#ifdef FOR_DEBUG
private:
    long signal_in_class;
    int epoll_fd;
    int listen_socket_fd;
    struct epoll_event event;
    struct epoll_event* events;
protected:
    long create_socket_bind();
    long make_socket_non_blocking(int infd);
#endif
};

#endif
