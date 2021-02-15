cmake_minimum_required(VERSION 3.17)

project(OmniliumKnox VERSION 0.1)
configure_file(Config.h.in core/include/Config.h)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

add_subdirectory(core)
add_subdirectory(knoxcli)
add_subdirectory(knox)