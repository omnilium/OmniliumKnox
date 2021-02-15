include(cmake/App.cmake)

set(EXE_NAME Knox)

set(PRIVATE_H_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/private")

set(CPP_FILES
        "main.cpp"
        "Knox.cpp"
        )

set(PUBLIC_H_FILES
        "Knox.h"
        )

set(PRIVATE_H_FILES
        "${PRIVATE_H_FOLDER}/pch.h"
        "${PRIVATE_H_FOLDER}/Resources.h"
        )

set(ASSETS
        "app.rc"
        "app.ico"
        "assets/app.html"
        )

set(SOURCE_FILES
        ${CPP_FILES}
        ${PUBLIC_H_FILES}
        ${PRIVATE_H_FILES}
        ${ASSETS}
        )

if(CMAKE_BUILD_TYPE MATCHES DEBUG)
        set(ENABLE_INSPECTOR True)
endif(CMAKE_BUILD_TYPE MATCHES DEBUG)

add_app(${EXE_NAME} "${SOURCE_FILES}")

target_include_directories(${EXE_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${PRIVATE_H_FOLDER}"
        )

target_precompile_headers(Knox PRIVATE
        "${PRIVATE_H_FOLDER}/pch.h"
        )

target_link_libraries(${EXE_NAME} Core)

install(TARGETS ${EXE_NAME}
        DESTINATION bin
        )