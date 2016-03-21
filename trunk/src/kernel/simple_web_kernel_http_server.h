//
// Created by Hank on 2016/3/21.
//

#ifndef SIMPLE_WEB_SERVER_SIMPLE_WEB_KERNEL_HTTP_SERVER_H
#define SIMPLE_WEB_SERVER_SIMPLE_WEB_KERNEL_HTTP_SERVER_H

#include "../core/simple_web_core.h"

static const long DEFAULT_HTTP_SERVER_PORT = 8080;

class simple_web_kernel_http_server
{
public:
    simple_web_kernel_http_server();
    virtual ~simple_web_kernel_http_server();
public:
    int initialize(long port);
    int start();
    int loop();
};

#endif //SIMPLE_WEB_SERVER_SIMPLE_WEB_KERNEL_HTTP_SERVER_H
