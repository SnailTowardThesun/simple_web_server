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
#ifndef __SIMPLE_WEB_CORE_HEADER__
#define __SIMPLE_WEB_CORE_HEADER__

// common header
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <simple_web_app_log.h>
#define SIMPLE_WEB_SERVER_NAME "Simple_Web_Server_1,0"

// common veriable
#define RESULT_OK 0
#define RESULT_ERROR 1

// common function
extern long simple_web_initialize(std::string base_folder_path);
extern void *process_signals(void *arg);
extern std::string get_version();

//compile switch
#define USING_ST

#endif
