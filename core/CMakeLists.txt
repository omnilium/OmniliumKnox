include(generate_version_rc)

generate_version_rc(DLL ${CMAKE_CURRENT_SOURCE_DIR}/private)

set(LIB_NAME Core)

add_compile_definitions(CORE_EXPORTS=1)

set(PRIVATE_H_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/private")

set(CPP_FILES
        "Core.cpp"
        "Logging.cpp"
        "Utils.cpp"
        "dllmain.cpp"
        "RAIITemplates.cpp"
        "MappedFile.cpp"
        )

set(PUBLIC_H_FILES
        "Core.h"
        "Logging.h"
        "Utils.h"
        "RAIITemplates.h"
        "MappedFile.h"
        )

set(PRIVATE_H_FILES
        "${PRIVATE_H_FOLDER}/pch.h"
        "${VERSION_INFO_FILE}"
        )

add_library(${LIB_NAME} SHARED
        ${CPP_FILES}
        ${PUBLIC_H_FILES}
        ${PRIVATE_H_FILES}
        "${VERSION_RC_FILE}"
        )

target_include_directories(${LIB_NAME} PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
        )

target_include_directories(${LIB_NAME} PRIVATE
        "${PRIVATE_H_FOLDER}"
        )

target_precompile_headers(${LIB_NAME} PRIVATE
        "${PRIVATE_H_FOLDER}/pch.h"
        )

install(TARGETS ${LIB_NAME}
        RUNTIME DESTINATION bin
        )