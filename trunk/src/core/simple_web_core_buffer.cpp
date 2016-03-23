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
#include "simple_web_core_buffer.h"

SimpleWebCoreBuffer::SimpleWebCoreBuffer()
{

}

SimpleWebCoreBuffer::~SimpleWebCoreBuffer()
{

}

bool SimpleWebCoreBuffer::write_into_buffer(const char* data, int data_size)
{
    if (data == NULL) {
        simple_web_app_log::log("help","SimpleWebCoreBuffer.cpp","the data is NULL");
        return false;
    }
    buffer_.append(data,data_size);
    return true;
}

std::vector<std::string> SimpleWebCoreBuffer::get_lines(std::string str)
{
    std::vector<std::string> str_list;
    if(str.empty()) {
        simple_web_app_log::log("help","simple_web_core_buffer.cpp","the str is empty");
        return str_list;
    }
    size_t size = str.find_last_of("\r\n\r\n"),cur_pos = 0;
    if(size == std::string::npos) {
        simple_web_app_log::log("help","simple_web_core_buffer.cpp","the str is not end with \r\n\r\n");
        return str_list;
    }
    while(cur_pos < size - 2) {
        std::string str_line;
        size_t size_line = str.find_first_of("\r\n",cur_pos);
        if(size_line != std::string::npos && size_line != 0) {
            str_line.assign(str,cur_pos,size_line - cur_pos);
            str_list.push_back(str_line);
            cur_pos = size_line + 2;
        } else {
            break;
        }
    }
    return str_list;
}

std::string SimpleWebCoreBuffer::set_line(std::vector<std::string> vec)
{
    std::string str;
    for(std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); it++) {
        str+=*it + "\r\n";
    }
    str+="\r\n";
    return str;
}
