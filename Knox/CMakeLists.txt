include(cmake/App.cmake)

set(SOURCES "assets/app.html"
            "include/pch.h"
            "include/Knox.h"
            "src/Knox.cpp"
            "src/main.cpp")

set(ENABLE_INSPECTOR true)

add_app(Knox "${SOURCES}")

target_include_directories(Knox PRIVATE "include/")

target_precompile_headers(Knox PRIVATE "include/pch.h")

install(TARGETS Knox RUNTIME DESTINATION bin)