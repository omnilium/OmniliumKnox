add_compile_definitions(CORE_EXPORTS=1)

add_library(Core SHARED Src/Core.cpp
                        Src/Logging.cpp
                        Src/Utils.cpp
                        Src/dllmain.cpp)

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Include)

target_precompile_headers(Core PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Include/pch.h)


install(TARGETS Core
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION bin)