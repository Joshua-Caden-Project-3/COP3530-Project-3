cmake_minimum_required(VERSION 3.27)
project(COP3530_Project_3)

set(CMAKE_CXX_STANDARD 17)


include_directories("C:/Users/caden/AppData/Local/JetBrains/CLion 2023.3.1/bin/mingw/include")

add_executable(COP3530_Project_3
        main.cpp
        Data.cpp
        Mergesort.cpp
        Quicksort.cpp
)

target_include_directories(COP3530_Project_3 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)