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
#include "simple_web_protocol_http_common_variabels.h"
using namespace SimpleWebHttp;

SimpleWebProtocolHttpRequest::SimpleWebProtocolHttpRequest()
{

}

SimpleWebProtocolHttpRequest::~SimpleWebProtocolHttpRequest()
{

}

bool SimpleWebProtocolHttpRequest::get_http_request_parts(std::vector<std::string> http_header_list)
{
    if(http_header_list.empty()) {
        simple_web_app_log::log("help","simple_web_core_buffer.cpp","the http header's list is empty");
        return false;
    }
    http_request_map_.clear();
    for(std::vector<std::string>::iterator it = http_header_list.begin(); it != http_header_list.end(); it++) {
        std::string header_name,header_content;
        if(HttpMethod::is_http_method(header_name)) {

        }
    }
    return true;
}

bool SimpleWebProtocolHttpRequest::parse_http_request(std::string request)
{
    if (request.empty()) {
        simple_web_app_log::log("help","simple_web_protocol_http.cpp","the request is empty");
        return false;
    }
    std::vector<std::string> http_header_list = get_lines(request);
    return true;
}

bool SimpleWebProtocolHttpRequest::make_up_http_request()
{
    return true;
}

SimpleWebProtocolHttpResponse::SimpleWebProtocolHttpResponse()
{

}

SimpleWebProtocolHttpResponse::~SimpleWebProtocolHttpResponse()
{

}

bool SimpleWebProtocolHttpResponse::parse_http_response(std::string response)
{
    if (response.empty()) {
        simple_web_app_log::log("help","simple_web_protocol_http.cpp","the response is empty");
        return false;
    }
    return true;
}

bool SimpleWebProtocolHttpResponse::make_up_http_response()
{
    return true;
}

SimpleWebProtocolHttp::SimpleWebProtocolHttp()
{

}

SimpleWebProtocolHttp::~SimpleWebProtocolHttp()
{

}

bool SimpleWebProtocolHttp::deal_with_request(std::string request)
{
    if (request.empty()) {
        simple_web_app_log::log("help","simple_web_protocol_http.cpp","the reques is empty");
        return false;
    }
    // parse the request
    if(!request_.parse_http_request(request)) {
        simple_web_app_log::log("error","simple_web_protocol_http.cpp","fail to parse the http request");
        return false;
    }
    // find whether the file is existed
    // send request
    return true;
}

bool SimpleWebProtocolHttp::deal_with_response(std::string response)
{
    if (response.empty()) {
        simple_web_app_log::log("help","simple_web_protocol_http.cpp","the response is empty");
        return false;
    }
    return true;
}
