cmake_minimum_required(VERSION 3.26)
project(MIT6_S081)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(lab1)

add_executable(MIT6_S081
        lab1/sleep.c
        README.md
        lab1/pingpong.c
        lab1/primes.c)
