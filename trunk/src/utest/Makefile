all: test_main

test_main: test_main.cpp  test_http.cpp test_http.h ../protocol/simple_web_protocol_http.h ../protocol/simple_web_protocol_http.cpp ../protocol/simple_web_protocol_http_common_variables.h ../core/simple_web_core.h ../core/simple_web_core_buffer.cpp ../core/simple_web_core_buffer.cpp ../app/simple_web_app_log.cpp ../app/simple_web_app_log.h ../core/simple_web_core_source.h ../core/simple_web_core_source.cpp ../kernel/simple_web_kernel_sources_control.h ../kernel/simple_web_kernel_sources_control.cpp
	g++ test_main.cpp test_http.cpp test_http.h ../protocol/simple_web_protocol_http.h ../protocol/simple_web_protocol_http.cpp ../protocol/simple_web_protocol_http_common_variables.h ../core/simple_web_core.h ../core/simple_web_core_buffer.cpp ../core/simple_web_core_buffer.h ../app/simple_web_app_log.cpp ../app/simple_web_app_log.h  ../core/simple_web_core_source.h ../core/simple_web_core_source.cpp ../kernel/simple_web_kernel_sources_control.h ../kernel/simple_web_kernel_sources_control.cpp -o ./objs/test -lcppunit -g

clean:
	rm -rf ./objs/*
	rm -rf *.o
