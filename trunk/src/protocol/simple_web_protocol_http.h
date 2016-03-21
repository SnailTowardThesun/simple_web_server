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

#ifndef SIMPLE_WEB_PROTOCOL_HTTP_H
#define SIMPLE_WEB_PROTOCOL_HTTP_H

#include "../core/simple_web_core.h"
#include "../core/simple_web_core_buffer.h"
namespace simple_web_http
{
    class simple_web_protocol_http_request:simple_web_core_buffer
    {
    public:
        simple_web_protocol_http_request();
        virtual ~simple_web_protocol_http_request();
    public:
        bool parse_http_request(std::string request);
        bool make_up_http_request();
    };

    class simple_web_protocol_http_response:simple_web_core_buffer
    {
    public:
        simple_web_protocol_http_response();
        virtual ~simple_web_protocol_http_response();
    public:
        bool parse_http_response(std::string response);
        bool make_up_http_response();
    };

    class simple_web_protocol_http
    {
    public:
        simple_web_protocol_http();
        virtual ~simple_web_protocol_http();
    private:
        simple_web_protocol_http_request request_;
        simple_web_protocol_http_response response_;
    public:
        bool deal_with_request(std::string request);
        bool deal_with_response(std::string response);
    };
}

#endif
