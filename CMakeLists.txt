cmake_minimum_required(VERSION 3.15)
project(jnp1_zad3)

set(CMAKE_CXX_STANDARD 17)

add_executable(jnp1_zad3 main.cpp fibo.cc fibo.h)
add_executable(test test.cpp fibo.cc fibo.h)