cmake_minimum_required(VERSION 3.0)

project(MeuJogo)



add_executable(MeuJogo src/tutorial.cpp)

include_directories(include)

add_library(func src/func.cpp)
target_link_libraries(MeuJogo PUBLIC func)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

target_link_libraries(MeuJogo PUBLIC SDL2)
target_link_libraries(MeuJogo PUBLIC SDL2_image)
