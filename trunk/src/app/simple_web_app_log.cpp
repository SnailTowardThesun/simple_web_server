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
#include "simple_web_app_log.h"
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
simple_web_app_log* simple_web_app_log::pInstance = nullptr;

simple_web_app_log* simple_web_app_log::getInstance()
{
	if(pInstance == nullptr)
		pInstance = new simple_web_app_log();
	return pInstance;
}

simple_web_app_log::simple_web_app_log() : 
	log_file_name(DEFAULT_SIMPLE_WEB_LOG_FILE),
	log_data(nullptr),
	log_file_handle(-1)
{
	log_data = new char[LOG_MAX_SIZE];
}

simple_web_app_log::~simple_web_app_log()
{
	if(log_data != nullptr) delete[] log_data;
	if(log_file_handle > 0) ::close(log_file_handle);
}

void simple_web_app_log::setLogFile(const std::string strLogFileName)
{
	if(strLogFileName.size() > 0)
		log_file_name = strLogFileName;
}
bool simple_web_app_log::generate_header(const std::string tag,int context_id, const std::string level_name, int& header_size)
{
	return true;
}
int32_t simple_web_app_log::log(std::string level_name, std::string tag, const char *fmt)
{
	int32_t ret = 0;

	return ret;
}

