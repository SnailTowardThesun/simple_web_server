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

#include "simple_web_kernel_sources_control.h"
#include "../app/simple_web_app_source_file.h"
#include "../core/simple_web_core_source.h"
SimpleWebKernelSourcesCtl::SimpleWebKernelSourcesCtl()
{

}

SimpleWebKernelSourcesCtl::~SimpleWebKernelSourcesCtl()
{

}

SimpleWebKernelSourcesCtl* SimpleWebKernelSourcesCtl::pInstance_ = NULL;

SimpleWebKernelSourcesCtl* SimpleWebKernelSourcesCtl::getInstance()
{
    if(pInstance_ == NULL) {
        pInstance_ = new SimpleWebKernelSourcesCtl();
    }
    return pInstance_;
}

SimpleWebCoreSource* SimpleWebKernelSourcesCtl::get_source(std::string file_url)
{
    if (file_url.empty()) {
        simple_web_app_log::log("help","simple_web_kernel_sources_control.cpp","the file_url is empty");
        return NULL;
    }
    return source_list_[file_url];
}

long SimpleWebKernelSourcesCtl::initialize()
{
    // make a static source as test case
    SimpleWebCoreSource* pIndex = new SimpleWebAppSourceFile();
    pIndex->initialize("/index.html", "");
    source_list_.insert(std::pair<std::string,SimpleWebCoreSource*>("/index.html",pIndex));
    // add the http protocol source like 404,500 etc.
    SimpleWebCoreSource* p404Index = new SimpleWebAppSourceFile();
    p404Index->initialize("/404.html", "");
    source_list_.insert(std::pair<std::string,SimpleWebCoreSource*>("/404.html",p404Index));

    return RESULT_OK;
}
