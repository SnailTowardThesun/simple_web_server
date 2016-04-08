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
#include <simple_web_app_source_file.h>
#include <simple_web_protocol_http_common_variables.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

SimpleWebAppSourceFile::SimpleWebAppSourceFile() : file_pointer(0)
{
}

SimpleWebAppSourceFile::~SimpleWebAppSourceFile()
{
    close_file();
}

int SimpleWebAppSourceFile::read_file()
{
    file_content.clear();
    if (file_pointer == NULL) {
        simple_web_app_log::log("error", "simple_web_app_source_file.cpp", "the file netfd is NULL, read file failed");
        return RESULT_ERROR;
    }
    while (read(file_pointer, buffer, 1024) == 1024) {
        file_content += buffer;
        memset(buffer, 0, 1024);
    }
    file_content += "this is html file";
    return RESULT_OK;
}

long SimpleWebAppSourceFile::open_file()
{
    if (file_pointer != NULL) {
        simple_web_app_log::log("warning", "simple_web_app_source_file.cpp", "the file has been opened");
        if (close_file() == RESULT_ERROR) return RESULT_ERROR;
    }
    if ((file_pointer = open(file_path.c_str(), O_CREAT|O_WRONLY|O_TRUNC, 0644)) == NULL) {
        simple_web_app_log::log("error", "simple_web_app_source_file.cpp", "open the file pointer failed");
        return RESULT_ERROR;
    }
    return RESULT_OK;
}

long SimpleWebAppSourceFile::close_file()
{
    close(file_pointer);
    file_pointer = NULL;
    file_pointer = NULL;
    return RESULT_OK;
}

int SimpleWebAppSourceFile::initialize(std::string source_name, std::string url)
{
    if (source_name.empty()) {
        simple_web_app_log::log("help", "simple_web_app_source_file.cpp", "the source's name is empty");
        return RESULT_ERROR;
    }
    source_name_ = source_name;
    if (url.empty()) {
        simple_web_app_log::log("help", "simple_web_app_source_file.cpp", "the source's name is empty");
        return RESULT_ERROR;
    }
    file_path = url;
    if (open_file() == RESULT_ERROR) {
        simple_web_app_log::log("error", "simple_web_app_source_file.cpp", "the source open failed");
        return RESULT_ERROR;
    }
    return RESULT_OK;
}

int SimpleWebAppSourceFile::get_file_content(std::string& str, long& size)
{
    if (read_file() != RESULT_ERROR) {
        str = file_content;
    } else {
        simple_web_app_log::log("error", "simple_web_app_source_file.cpp", "the source's name is empyt or read from source failed");
        str = SimpleWebHttp::HTTP_404_RESPONSE_HTML;
    }
    size = str.length();
    return RESULT_OK;
}
