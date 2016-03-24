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
#include "simple_web_protocol_http_common_variables.h"
#include "../kernel/simple_web_kernel_sources_control.h"
#include "../core/simple_web_core_source.h"
using namespace SimpleWebHttp;

SimpleWebProtocolHttpRequest::SimpleWebProtocolHttpRequest()
{

}

SimpleWebProtocolHttpRequest::~SimpleWebProtocolHttpRequest()
{

}

std::string SimpleWebProtocolHttpRequest::get_info(std::string name)
{
    return http_request_map_[name];
}

bool SimpleWebProtocolHttpRequest::get_http_request_parts(std::vector<std::string> http_header_list)
{
    if(http_header_list.empty()) {
        simple_web_app_log::log("help","simple_web_core_buffer.cpp","the http header's list is empty");
        return false;
    }
    http_request_map_.clear();
    std::string show_message;
    for(std::vector<std::string>::iterator it = http_header_list.begin(); it != http_header_list.end(); it++) {
        std::string header_name,header_content;
        size_t size = it->find_first_of(" ");
        if(size == std::string::npos) {
            return false;
        }
        header_name.assign(*it,0,size);
        if(is_http_method(header_name)) {
            // add method name
            http_request_map_.insert(std::pair<std::string,std::string>(HTTP_METHOD,header_name));

            show_message = "get method name "+header_name;
            simple_web_app_log::log("trace","simple_web_protocol_http.cpp",show_message.c_str());

            // add the file asked
            size_t cur_size = it->find_first_of(" ",size + 1);
            if(cur_size == std::string::npos) {
                return false;
            }
            header_content.assign(*it,size+1,cur_size - size -1);

            show_message = "get file "+header_content;
            simple_web_app_log::log("trace","simple_web_protocol_http.cpp",show_message.c_str());

            http_request_map_.insert(std::pair<std::string,std::string>(HTTP_REQUEST_FILE,header_content));
            // add the http version
            header_content.assign(*it,cur_size+1,it->length() - cur_size - 1);

            show_message = "get http version "+header_content;
            simple_web_app_log::log("trace","simple_web_protocol_http.cpp",show_message.c_str());

            http_request_map_.insert(std::pair<std::string,std::string>(HTTP_VERSION,header_content));
        } else {
            header_name.assign(*it,0,size);
            header_content.assign(*it,size+1,it->length()-size-1);

            show_message = "get name "+header_name;
            simple_web_app_log::log("trace","simple_web_protocol_http.cpp",show_message.c_str());
            show_message = "get content "+header_content;
            simple_web_app_log::log("trace","simple_web_protocol_http.cpp",show_message.c_str());

            http_request_map_.insert(std::pair<std::string,std::string>(header_name,header_content));
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
    return get_http_request_parts(get_lines(request));
}


/***********************************************************************************************************/
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

void SimpleWebProtocolHttpResponse::set_info(std::string name, std::string content)
{
    http_response_map_.insert(std::pair<std::string,std::string>(name,content));
}

std::vector<std::string> SimpleWebProtocolHttpResponse::combine_http_response(std::map<std::string, std::string> response_map)
{
    std::vector<std::string> vec;
    // http version and response num
    vec.push_back(response_map[HTTP_VERSION] + " " + response_map[HTTP_RESPONSE_NUM]);
    // the rest
    for(std::map<std::string,std::string>::iterator it = response_map.begin(); it != response_map.end(); it++) {
        if(it->first != HTTP_VERSION && it->first != HTTP_RESPONSE_NUM) {
            vec.push_back(it->first + it->second);
        }
    }
    return vec;
}

std::string SimpleWebProtocolHttpResponse::get_http_response()
{
    std::string response = set_line(combine_http_response(http_response_map_));
    // clear the map
    http_response_map_.clear();
    return response;
}

/***********************************************************************************************/
SimpleWebProtocolHttp::SimpleWebProtocolHttp()
{

}

SimpleWebProtocolHttp::~SimpleWebProtocolHttp()
{

}

SimpleWebCoreSource* SimpleWebProtocolHttp::deal_with_request(std::string request)
{
    if (request.empty()) {
        simple_web_app_log::log("help","simple_web_protocol_http.cpp","the reques is empty");
        return NULL;
    }
    // parse the request
    if(!request_.parse_http_request(request)) {
        simple_web_app_log::log("error","simple_web_protocol_http.cpp","fail to parse the http request");
        return NULL;
    }
    // find whether the file is existed
    std::string file = request_.get_info(HTTP_REQUEST_FILE);
    // send response
    response_.set_info(HTTP_VERSION,HTTP_VERSION_1);
    response_.set_info("Server: ","Simple_Web_Server_1.0");
    response_.set_info("Content-Type: ","text/plain");
    std::string str_rp = response_.get_http_response();
    simple_web_app_log::log("trace","simple_web_protocol_http.cpp",str_rp.c_str());
    // get the source and source's state
    // now we just judge whether the file is existed
    SimpleWebCoreSource* source = SimpleWebKernelSourcesCtl::getInstance()->get_source(file);
    if(source != NULL) {
        response_.set_info(HTTP_RESPONSE_NUM,HTTP_RESPONSE_200);
    } else {
        response_.set_info(HTTP_RESPONSE_NUM, HTTP_RESPONSE_404);
    }
    // send the response
    return source;
}

bool SimpleWebProtocolHttp::deal_with_response(std::string response)
{
    if (response.empty()) {
        simple_web_app_log::log("help","simple_web_protocol_http.cpp","the response is empty");
        return false;
    }
    return true;
}
