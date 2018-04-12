cmake_minimum_required (VERSION 2.8)
project (tdrest)
include_directories ("${PROJECT_SOURCE_DIR}/src")

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
IF(CMAKE_COMPILER_IS_GNUCC)
	SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Wall -std=c11   -g")
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -g")
ENDIF(CMAKE_COMPILER_IS_GNUCC)

# jsoncpp
include_directories ("${PROJECT_SOURCE_DIR}/include")
set(jsoncpp_sources extern/jsoncpp-0.10.5/dist/jsoncpp.cpp)

# Main
file(GLOB_RECURSE main_sources src/*.cpp)

# Target
add_executable(tdrest ${main_sources} ${jsoncpp_sources})

# libmicrohttpd
include_directories ("${PROJECT_SOURCE_DIR}/extern/libmicrohttpd/include")
target_link_libraries(tdrest "${PROJECT_SOURCE_DIR}/extern/libmicrohttpd/lib/libmicrohttpd.so")

include_directories ("/usr/include")
target_link_libraries(tdrest "/usr/lib/x86_64-linux-gnu/libmysqlcppconn.so")