cmake_minimum_required(VERSION 3.20)
project(diplom_domino)

set(CMAKE_CXX_STANDARD 14)

find_package(MPI REQUIRED)

set(CMAKE_CXX_COMPILER mpicxx)

add_executable(diplom_domino main.cpp Cell/Cell.cpp Cell/Cell.h Field/Field.cpp Field/Field.h Field/FieldConfig.h)