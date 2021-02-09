cmake_minimum_required(VERSION 3.10)

project(OmniliumKnox VERSION 0.1)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

add_subdirectory(Core)
add_subdirectory(Console)

add_custom_target(LOCAL_INSTALL ALL "${CMAKE_COMMAND}"
                  -D CMAKE_INSTALL_PREFIX:string=${CMAKE_CURRENT_BINARY_DIR}/install
                  -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_install.cmake"
                  DEPENDS Console Core)