cmake_minimum_required(VERSION 3.10)
project(projeto_final C)

set(CMAKE_C_STANDARD 99)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/users.in DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(projeto_final main.c graph.h graph.c element.h element.c list.h list.c mergesort.c mergesort.h)