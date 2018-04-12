cmake_minimum_required(VERSION 2.6)

set ( PROJECT_NAME
    tests
)

set ( TEST_EXE_NAME
    tests.app
)

set ( TESTS_ROUTINES
    gtest.cpp
)

set ( TESTS_LIBRARIES
    ${GTEST_LIBRARIES} 
    pthread
)

project (${PROJECT_NAME})

find_package (GTest REQUIRED)
include_directories (${GTEST_INCLUDE_DIRS})

message ($TEST_LIBRARIES)

add_executable (${PROJECT_NAME} ${TESTS_ROUTINES})
target_link_libraries (${PROJECT_NAME} ${TEST_LIBRARIES})

set_target_properties (${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${TEST_EXE_NAME})
