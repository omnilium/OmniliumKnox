add_compile_definitions(CORE_EXPORTS=1)

set(CPP_FILES Src/Core.cpp
              Src/Logging.cpp
              Src/Utils.cpp
              Src/dllmain.cpp
              Src/RAIITemplates.cpp
              Src/MappedFile.cpp)

set(H_FILES Include/Core.h
            Include/Logging.h
            Include/Utils.h 
            Include/RAIITemplates.h
            Include/MappedFile.h)

add_library(Core SHARED ${CPP_FILES} ${H_FILES})

target_include_directories(Core PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Include)

target_precompile_headers(Core PRIVATE ${CMAKE_CURRENT_LIST_DIR}/Include/pch.h)


install(TARGETS Core
        RUNTIME DESTINATION bin)