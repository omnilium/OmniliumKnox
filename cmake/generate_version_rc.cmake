MACRO(generate_version_rc IN_FILE_TYPE OUT_DIR)
    if(DEFINED ENV{VERSION_MAJOR})
        set(VERSION_MAJOR $ENV{VERSION_MAJOR})
    else()
        set(VERSION_MAJOR 0)
    endif()

    if(DEFINED ENV{VERSION_MINOR})
        set(VERSION_MINOR $ENV{VERSION_MINOR})
    else()
        set(VERSION_MINOR 1)
    endif()

    if(DEFINED ENV{VERSION_PATCH})
        set(VERSION_PATCH $ENV{VERSION_PATCH})
    else()
        set(VERSION_PATCH 0)
    endif()

    if(DEFINED ENV{VERSION_BUILD})
        set(VERSION_BUILD $ENV{VERSION_BUILD})
    else()
        set(VERSION_BUILD 1)
    endif()

    if(NOT DEFINED FILE_VERSION_MAJOR)
        set(FILE_VERSION_MAJOR ${VERSION_MAJOR})
    endif()

    if(NOT DEFINED FILE_VERSION_MINOR)
        set(FILE_VERSION_MINOR ${VERSION_MINOR})
    endif()

    if(NOT DEFINED FILE_VERSION_PATCH)
        set(FILE_VERSION_PATCH ${VERSION_PATCH})
    endif()

    set(FILE_TYPE ${IN_FILE_TYPE})

    set(VERSION_INFO_FILE ${OUT_DIR}/version.h)
    set(VERSION_RC_FILE ${OUT_DIR}/version.rc)

    configure_file(${PROJECT_SOURCE_DIR}/version.h ${VERSION_INFO_FILE} @ONLY)
    configure_file(${PROJECT_SOURCE_DIR}/version.rc ${VERSION_RC_FILE} @ONLY)
    configure_file(${PROJECT_SOURCE_DIR}/app.ico ${OUT_DIR}/app.ico COPYONLY)
endmacro()