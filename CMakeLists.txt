cmake_minimum_required (VERSION 3.1)
project (tdrest C CXX)
include_directories ("${PROJECT_SOURCE_DIR}/src")

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")
SET(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -Wall -std=c11   -g")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -g")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

# jsoncpp
include_directories ("${PROJECT_SOURCE_DIR}/include")
include_directories ("${PROJECT_SOURCE_DIR}/include/legacy")

set(jsoncpp_sources extern/jsoncpp-0.10.5/dist/jsoncpp.cpp)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package (Threads REQUIRED)

file(GLOB_RECURSE main_sources src/*.cpp)
file(GLOB_RECURSE pistache_sources pistache/src/*.cpp)

# Target
add_executable(tdrest ${main_sources} ${pistache_sources} ${jsoncpp_sources})

if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(tdrest PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(tdrest "${CMAKE_THREAD_LIBS_INIT}")
endif()

include_directories ("/usr/include")
target_link_libraries(tdrest "/usr/lib/x86_64-linux-gnu/libmysqlcppconn.so")
# include_directories ("/usr/local/include")
# target_link_libraries(tdrest "/usr/local/lib/libpistache.a")