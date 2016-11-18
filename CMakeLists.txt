cmake_minimum_required(VERSION 3.2)
project(Assignment5-2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -Wextra -pedantic -pedantic-errors")

# Include the GoogleTest directory
set(GTEST_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/googletest/googletest)
# Add GoogleTest as a build subdirectory
add_subdirectory(lib/googletest)
# Include the GoogleTest header directory
include_directories(${GTEST_DIRECTORY}/include)

# Define the source files and dependencies for testing executable
set(SOURCE_FILES
        tests/driver.cpp
        ${GTEST_DIRECTORY}/include/gtest/gtest.h
        src/Object.cpp
        src/ObjectFactory.cpp
        src/Parser.cpp
        src/Visitor.cpp
        src/Universe.cpp
        tests/vectorTest.cpp
        tests/visitorTest.cpp
        tests/intertiaTest.cpp
        tests/UMCTest.cpp)
# Make the project root directory the working directory when we run
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_executable(Testing ${SOURCE_FILES})
target_link_libraries(Testing gtest)
