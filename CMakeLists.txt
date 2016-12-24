cmake_minimum_required(VERSION 2.6)
project(sfmlsnake)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

set(SFMLSNAKE_SOURCES main.cpp Game.cpp Snake.cpp DoubleVector2.cpp Food.cpp Wall.cpp)
set (CMAKE_CXX_FLAGS "-Wall -pedantic")
set (CMAKE_BUILD_TYPE "Release")

add_executable(sfmlsnake ${SFMLSNAKE_SOURCES})

TARGET_LINK_LIBRARIES(sfmlsnake sfml-graphics sfml-window sfml-system)

install(TARGETS sfmlsnake RUNTIME DESTINATION bin)
