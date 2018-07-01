cmake_minimum_required(VERSION 3.1)
project(create_samples)

set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")

include_directories(/usr/local/include ext)

add_executable(create_samples create_samples.cpp)

set(CMAKE_LIBRARY_PATH "${CMAKE_LIBRARY_PATH} /usr/local/lib")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework OpenGL -framework GLUT /usr/local/lib/libpng.a -lz")
