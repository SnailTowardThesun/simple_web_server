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
#ifndef __SIMPLE_WEB_APP_LOG_HEADER__
#define __SIMPLE_WEB_APP_LOG_HEADER__

#include "../core/simple_web_core.h"
#include <string>

#define DEFAULT_SIMPLE_WEB_LOG_FILE "simple_web.log"
#define LOG_MAX_SIZE 4096

class simple_web_app_log
{
public:
    simple_web_app_log();
    virtual ~simple_web_app_log();
public:
    static simple_web_app_log* getInstance();
    static simple_web_app_log* pInstance;

private:
    std::string log_file_name;
    char* log_data;
    int log_file_handle;
protected:
    bool generate_header(const std::string tag,int context_id, const std::string level_name, int& header_size);
public:
    void setLogFile(const std::string strLogFileName);
    int32_t log(std::string level_name, std::string tag, const char *fmt);
};

#endif
