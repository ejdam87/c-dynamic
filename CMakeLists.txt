cmake_minimum_required(VERSION 3.15)
project(structures C)

set(CMAKE_C_STANDARD 99)

add_executable(structures main.c linked_list.h linked_list.c)
