cmake_minimum_required(VERSION 3.25)
project(practice C)

set(CMAKE_C_STANDARD 11)

add_executable(practice main.c sha.c sha.h menuInterface.c menuInterface.h)
