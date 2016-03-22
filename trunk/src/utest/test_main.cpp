#include <iostream>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include "test_http.h"
int main()
{
    //CppUnit::Test *suit = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
    CppUnit::TextTestRunner runner;
    std::cout<<"this is the main function of utest"<<std::endl;
    return 0;
}
