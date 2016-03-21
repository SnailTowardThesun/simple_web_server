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

#include "simple_web_protocol_http.h"
using namespace simple_web_http;

simple_web_protocol_http_request::simple_web_protocol_http_request()
{

}

simple_web_protocol_http_request::~simple_web_protocol_http_request()
{

}

bool simple_web_protocol_http_request::parse_http_request(std::string request)
{
    if (request.empty()) {
        simple_web_app_log::log("help","simple_web_protocol_http.cpp","the request is empty");
        return false;
    }
    return true;
}

bool simple_web_protocol_http_request::make_up_http_request()
{
    return true;
}

simple_web_protocol_http_response::simple_web_protocol_http_response()
{

}

simple_web_protocol_http_response::~simple_web_protocol_http_response()
{

}

bool simple_web_protocol_http_response::parse_http_response(std::string response)
{
    if (response.empty()) {
        simple_web_app_log::log("help","simple_web_protocol_http.cpp","the response is empty");
        return false;
    }
    return true;
}

bool simple_web_protocol_http_response::make_up_http_response()
{
    return true;
}

simple_web_protocol_http::simple_web_protocol_http()
{

}

simple_web_protocol_http::~simple_web_protocol_http()
{

}

bool simple_web_protocol_http::deal_with_request(std::string request)
{
    if (request.empty()) {
        simple_web_app_log::log("help","simple_web_protocol_http.cpp","the reques is empty");
        return false;
    }
    return true;
}

bool simple_web_protocol_http::deal_with_response(std::string response)
{
    if (response.empty()) {
        simple_web_app_log::log("help","simple_web_protocol_http.cpp","the response is empty");
        return false;
    }
    return true;
}
