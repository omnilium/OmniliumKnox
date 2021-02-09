cmake_minimum_required(VERSION 3.10)

project(OmniliumKnox VERSION 0.1)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

add_subdirectory(Core)
add_subdirectory(Console)