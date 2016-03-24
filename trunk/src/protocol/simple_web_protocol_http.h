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
#include "../core/simple_web_core_source.h"

namespace SimpleWebHttp
{
    class SimpleWebCoreSource;
    class SimpleWebProtocolHttpRequest:public SimpleWebCoreBuffer
    {
    public:
        SimpleWebProtocolHttpRequest();
        virtual ~SimpleWebProtocolHttpRequest();
    private:
        std::map<std::string,std::string> http_request_map_;
    protected:
        bool get_http_request_parts(std::vector<std::string>);
    public:
        bool parse_http_request(std::string request);
        std::string get_info(std::string name);
    };

    class SimpleWebProtocolHttpResponse:SimpleWebCoreBuffer
    {
    public:
        SimpleWebProtocolHttpResponse();
        virtual ~SimpleWebProtocolHttpResponse();
    private:
        std::map<std::string ,std::string> http_response_map_;
    protected:
        std::vector<std::string> combine_http_response(std::map<std::string,std::string>);
    public:
        bool parse_http_response(std::string response);
        void set_info(std::string name, std::string content);
        std::string get_http_response();
    };

    class SimpleWebProtocolHttp
    {
    public:
        SimpleWebProtocolHttp();
        virtual ~SimpleWebProtocolHttp();
    private:
        SimpleWebProtocolHttpRequest request_;
        SimpleWebProtocolHttpResponse response_;
    public:
        SimpleWebCoreSource* deal_with_request(std::string request);
        bool deal_with_response(std::string response);
    };
}

#endif
