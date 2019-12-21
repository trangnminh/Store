cmake_minimum_required(VERSION 3.15)
project(Store)

set(CMAKE_CXX_STANDARD 14)

add_executable(Store main.cpp item.h LinkedList.h customer.h)