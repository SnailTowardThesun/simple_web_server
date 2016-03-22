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
#ifndef SIMPLE_WEB_PROTOCOL_HTTP_COMMON_VARIABLES_H
#define SIMPLE_WEB_PROTOCOL_HTTP_COMMON_VARIABLES_H

#include "../core/simple_web_core.h"

namespace SimpleWebHttp
{
    static const std::string HTTP_VERSION = "VERSION";

    static const std::string HTTP_METHOD = "METHOD";
    static const std::string HTTP_METHOD_GET = "GET";
    static const std::string HTTP_METHOD_POST = "POST";
    static const std::string HTTP_METHOD_PUT = "PUT";
    static const std::string HTTP_METHOD_DELETE = "DELETE";
    static const std::string HTTP_METHOD_TRACE = "TRACE";
    static const std::string HTTP_METHOD_OPTIONS = "OPTIONS";
    static const std::string HTTP_METHOD_CONNECT = "CONNECT";
    static const std::string HTTP_METHOD_PATCH = "PATCH";

    static const std::string HTTP_REQUEST_FILE = "FILE";

    static const std::string HTTP_RESPONSE_NUM = "RESPONSE_NUM";
    static const std::string HTTP_RESPONSE_100 = "100 Continue";
    static const std::string HTTP_RESPONSE_101 = "101 Switching Protocols";
    static const std::string HTTP_RESPONSE_200 = "200 OK";
    static const std::string HTTP_RESPONSE_201 = "201 Created";
    static const std::string HTTP_RESPONSE_202 = "202 Accepted";
    static const std::string HTTP_RESPONSE_203 = "203 Non-Authoritative Information";
    static const std::string HTTP_RESPONSE_204 = "204 No Content";
    static const std::string HTTP_RESPONSE_205 = "205 Reset Content";
    static const std::string HTTP_RESPONSE_206 = "206 Partial Content";
    static const std::string HTTP_RESPONSE_300 = "300 Multiple Choices";
    static const std::string HTTP_RESPONSE_301 = "301 Moved Permanently";
    static const std::string HTTP_RESPONSE_302 = "302 Found";
    static const std::string HTTP_RESPONSE_303 = "303 See Other";
    static const std::string HTTP_RESPONSE_304 = "304 Not Modified";
    static const std::string HTTP_RESPONSE_305 = "305 Use Porxy";
    static const std::string HTTP_RESPONSE_307 = "307 Temprorary Redirect";
    static const std::string HTTP_RESPONSE_400 = "400 Bad Request";
    static const std::string HTTP_RESPONSE_401 = "401 Unauthorized";
    static const std::string HTTP_RESPONSE_402 = "402 Payment Required";
    static const std::string HTTP_RESPONSE_403 = "403 Forbidden";
    static const std::string HTTP_RESPONSE_404 = "404 Not Found";
    static const std::string HTTP_RESPONSE_405 = "405 Method Not Allowed";
    static const std::string HTTP_RESPONSE_406 = "406 Not Acceptable";
    static const std::string HTTP_RESPONSE_407 = "407 Proxy Authentication Required";
    static const std::string HTTP_RESPONSE_408 = "408 Request Time-out";
    static const std::string HTTP_RESPONSE_409 = "409 Conflict";
    static const std::string HTTP_RESPONSE_410 = "410 Gone";
    static const std::string HTTP_RESPONSE_411 = "411 Length Required";
    static const std::string HTTP_RESPONSE_412 = "412 Precondition Failed";
    static const std::string HTTP_RESPONSE_413 = "413 Request Entity Too Large";
    static const std::string HTTP_RESPONSE_414 = "414 Request-URI Too Large";
    static const std::string HTTP_RESPONSE_415 = "415 Unsupported Media Type";
    static const std::string HTTP_RESPONSE_416 = "416 Requested range not satisfiable";
    static const std::string HTTP_RESPONSE_417 = "417 Expectation Failed";
    static const std::string HTTP_RESPONSE_500 = "500 Internal Server Error";
    static const std::string HTTP_RESPONSE_501 = "501 Not Implemented";
    static const std::string HTTP_RESPONSE_502 = "502 Bad Gateway";
    static const std::string HTTP_RESPONSE_503 = "503 Service Unavailabel";
    static const std::string HTTP_RESPONSE_504 = "504 Gateway Time-out";
    static const std::string HTTP_RESPONSE_505 = "505 HTTP Version not supported";

    static bool is_http_method(std::string str)
    {
                return (str == "GET" ||
                str == "HEAD"       ||
                str == "POST"       ||
                str == "PUT"        ||
                str == "DELETE"     ||
                str == "TRACE"      ||
                str == "OPTIONS"    ||
                str == "CONNECT"    ||
                str == "PATCH");
    }
}

#endif

