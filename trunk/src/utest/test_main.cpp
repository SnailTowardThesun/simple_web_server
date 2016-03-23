#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
int main()
{
    CppUnit::Test *suit = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
    CppUnit::TextTestRunner runner;
    runner.addTest(suit);
    runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(),std::cerr));
    return runner.run();
}
