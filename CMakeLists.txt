cmake_minimum_required(VERSION 3.17)

project(OmniliumKnox)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

add_subdirectory(core)
add_subdirectory(knoxcli)
add_subdirectory(knox)