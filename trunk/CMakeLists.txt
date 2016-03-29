CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules)

PROJECT(SIMPLE_WEB_SERVER)
SET(CMAKE_BUILD_TYPE Debug)

if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -g -Wall -Wno-unused-variable -fpermissive")
else( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set(CMAKE_BUILD_TYPE "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -O2  -fopenmp")
endif( CMAKE_BUILD_TYPE STREQUAL "Debug" )

include_directories("./3rdparty/st-1.9/obj/")

SET(APP_SOCKET ./src/app/simple_web_app_socket.cpp)
SET(APP_CONF ./src/app/simple_web_app_conf.cpp)
SET(APP_LOG ./src/app/simple_web_app_log.cpp)
SET(APP_SOURCE_FILE ./src/app/simple_web_app_source_file.cpp)
SET(APP_THREAD ./src/app/simple_web_app_thread.h ./src/app/simple_web_app_thread.cpp)
SET(APP_FUNCTION ${APP_SOCKET} ${APP_CONF} ${APP_LOG} ${APP_THREAD} ${APP_SOURCE_FILE})

SET(APP_CORE ./src/core/simple_web_core.h ./src/core/simple_web_core.cpp)
SET(CORE_SOURCE ./src/core/simple_web_core_source.h)
SET(CORE_BUFFER ./src/core/simple_web_core_buffer.h ./src/core/simple_web_core_buffer.cpp)
SET(CORE_FUNCTION ${APP_CORE} ${CORE_BUFFER} ${CORE_SOURCE})

SET(KERNEL_SOURCE_CONTROL ./src/kernel/simple_web_kernel_sources_control.cpp ./src/kernel/simple_web_kernel_sources_control.h)
SET(KERNEL_HTTP_SERVER src/kernel/simple_web_kernel_http_server.cpp src/kernel/simple_web_kernel_http_server.h)
SET(KERNEL_FUNCTION ${KERNEL_HTTP_SERVER} ${KERNEL_SOURCE_CONTROL})

SET(PROTOCOL_HTTP ./src/protocol/simple_web_protocol_http.h ./src/protocol/simple_web_protocol_http.cpp ./src/protocol/simple_web_protocol_http_common_variables.h)
SET(PROTOCOL_FUNCTION ${PROTOCOL_HTTP})

SET(SIMPLE_WEB_SERVER_BINARY_DIR "./objs/")
SET(EXECUTABLE_OUTPUT_PATH ${SIMPLE_WEB_SERVER_BINARY_DIR})
SET(LIBRARY_OUTPUT_PATH ${SIMPLE_WEB_SERVER_BINARY_DIR})

SET(SIMPLE_WEB_SERVER "./src/simple_web_server.cpp")
ADD_EXECUTABLE(simple_web_server ${SIMPLE_WEB_SERVER} ${APP_FUNCTION} ${CORE_FUNCTION} ${KERNEL_FUNCTION} ${PROTOCOL_FUNCTION})
TARGET_LINK_LIBRARIES(simple_web_server "${CMAKE_SOURCE_DIR}/3rdparty/st-1.9/obj/libst.a")
