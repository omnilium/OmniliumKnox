add_executable(Console Src/Console.cpp)

target_include_directories(Console PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Include)

target_link_libraries(Console Core)

target_precompile_headers(Console PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Include/pch.h)

install(TARGETS Console RUNTIME DESTINATION bin)