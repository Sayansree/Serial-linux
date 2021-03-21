cmake_minimum_required(VERSION 3.1.0)
project(Serial-linux)
add_compile_options(-std=c++11)

add_executable(serialTest example.cpp lib/Serial.cpp lib/Serial.h)
