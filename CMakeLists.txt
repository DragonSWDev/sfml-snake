cmake_minimum_required(VERSION 2.6)
project(sfmlsnake)

add_executable(sfmlsnake main.cpp)

install(TARGETS sfmlsnake RUNTIME DESTINATION bin)
