add_compile_definitions(CORE_EXPORTS=1)

set(CPP_FILES src/Core.cpp
              src/Logging.cpp
              src/Utils.cpp
              src/dllmain.cpp
              src/RAIITemplates.cpp
              src/MappedFile.cpp)

set(H_FILES include/pch.h
            include/Core.h
            include/Logging.h
            include/Utils.h 
            include/RAIITemplates.h
            include/MappedFile.h)

add_library(Core SHARED ${CPP_FILES} ${H_FILES})

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

target_precompile_headers(Core PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include/pch.h)


install(TARGETS Core
        RUNTIME DESTINATION bin)