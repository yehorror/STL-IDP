cmake_minimum_required(VERSION 3.5)

project(STL-IDP)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(STL-IDP 
	src/main.cpp
    src/Sorting.cpp)

target_link_libraries(STL-IDP gtest gmock)
