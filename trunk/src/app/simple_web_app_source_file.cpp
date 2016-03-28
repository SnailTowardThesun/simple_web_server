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
#include "simple_web_app_source_file.h"

SimpleWebAppSourceFile::SimpleWebAppSourceFile()
{
}

SimpleWebAppSourceFile::~SimpleWebAppSourceFile()
{
}

int SimpleWebAppSourceFile::initialize(std::string source_name, std::string url)
{
    if (source_name.empty()) {
        simple_web_app_log::log("help", "simple_web_app_source_file.cpp", "the source's name is empty");
        return RESULT_ERROR;
    }
    source_name_ = source_name;
    if (url.empty()) {
        //simple_web_app_log::log("help", "simple_web_app_source_file.cpp", "the source's name is empty");
    }
    return RESULT_OK;
}

int SimpleWebAppSourceFile::get_file_content(std::string& str, long& size)
{
    if(source_name_.empty()) {
        simple_web_app_log::log("help", "simple_web_app_source_file.cpp", "the source's name is empty");
        return RESULT_ERROR;
    }
    str = "<h1> this is a html </h1>";
    size = str.length();
    return RESULT_OK;
}
