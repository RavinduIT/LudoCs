cmake_minimum_required(VERSION 3.29)
project(LudoCs C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(LudoCs
    game.c
    logic.c
    logic.h
    types.c
    types.h)
