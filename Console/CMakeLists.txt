set(CPP_FILES src/KnoxC.cpp)

set(H_FILES include/pch.h)

add_executable(KnoxC ${CPP_FILES} ${H_FILES})

target_include_directories(KnoxC PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)

target_precompile_headers(KnoxC PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include/pch.h)

target_link_libraries(KnoxC Core)

install(TARGETS KnoxC RUNTIME DESTINATION bin)