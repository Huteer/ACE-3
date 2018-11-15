cmake_minimum_required(VERSION 3.12)
project(ACE3 C)

set(CMAKE_C_STANDARD 99)

add_executable(ACE3 main.c instructions.c instructions.h structreg.h helpfunctions.c helpfunctions.h)