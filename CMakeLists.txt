cmake_minimum_required(VERSION 3.15)
project(customer)

set(CMAKE_CXX_STANDARD 14)

add_executable(customer mainCustomer.cpp customer.cpp customer.h public.cpp public.h Item.cpp Item.h)