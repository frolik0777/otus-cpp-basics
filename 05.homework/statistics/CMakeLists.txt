cmake_minimum_required(VERSION 3.5)

project(05.homework)

add_executable(statistics statistics.cpp
    Min.h Min.cpp
    Max.h Max.cpp
    Mean.h Mean.cpp
    Std.h Std.cpp
    Pct.h Pct.cpp
)
set_target_properties(statistics PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
