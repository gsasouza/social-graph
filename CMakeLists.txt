cmake_minimum_required(VERSION 3.10)
project(projeto_final C)

set(CMAKE_C_STANDARD 99)

add_executable(projeto_final main.c graph.h graph.c graph_test.cpp)