cmake_minimum_required(VERSION 2.6)
project(sfmlsnake)

set(SFMLSNAKE_SOURCES main.cpp Game.cpp Snake.cpp DoubleVector2.cpp Food.cpp Wall.cpp)
set (CMAKE_CXX_FLAGS "-Wall -pedantic")

add_executable(sfmlsnake ${SFMLSNAKE_SOURCES})

TARGET_LINK_LIBRARIES(sfmlsnake sfml-graphics sfml-window sfml-system)

install(TARGETS sfmlsnake RUNTIME DESTINATION bin)
