cmake_minimum_required(VERSION 3.23)
project(cppProjects-TicTacToe)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_executable(cppProjects-TicTacToe main.cpp)
