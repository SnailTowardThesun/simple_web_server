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

#include <simple_web_kernel_sources_control.h>
#include <simple_web_app_source_file.h>

SimpleWebKernelSourcesCtl::SimpleWebKernelSourcesCtl()
{

}

SimpleWebKernelSourcesCtl::~SimpleWebKernelSourcesCtl()
{
    if (!source_list.empty()) {
        for (std::map<std::string, SimpleWebCoreSource*>::iterator it = source_list.begin();
                it != source_list.end(); ++it) {
         delete it->second;
        }
        source_list.clear();
    }
}

SimpleWebKernelSourcesCtl* SimpleWebKernelSourcesCtl::pInstance = NULL;

SimpleWebKernelSourcesCtl* SimpleWebKernelSourcesCtl::getInstance()
{
    if(pInstance == NULL) {
        pInstance = new SimpleWebKernelSourcesCtl();
    }
    return pInstance;
}

SimpleWebCoreSource* SimpleWebKernelSourcesCtl::get_source(std::string file_url)
{
    if (file_url.empty()) {
        simple_web_app_log::log("help", "simple_web_kernel_sources_control.cpp", "the file_url is empty");
        return NULL;
    }
    return source_list[file_url];
}

long SimpleWebKernelSourcesCtl::initialize(std::string base_folder_path)
{
    // get the www folder path
    if (base_folder_path.empty()) {
        simple_web_app_log::log("error", "simple_web_core.cpp", "the base folder's path is empty");
        return RESULT_ERROR;
    }
    current_path = base_folder_path;

    // make a static source as test case
    SimpleWebCoreSource* pIndex = new SimpleWebAppSourceFile();
    pIndex->initialize("/index.html", current_path + "/index.html");
    source_list.insert(std::pair<std::string,SimpleWebCoreSource*>("/index.html",pIndex));
    // add the http protocol source like 404,500 etc.
    SimpleWebCoreSource* p404Index = new SimpleWebAppSourceFile();
    p404Index->initialize("/404.html", current_path + "/404.html");
    source_list.insert(std::pair<std::string,SimpleWebCoreSource*>("/404.html",p404Index));

    return RESULT_OK;
}
