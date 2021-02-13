include(cmake/App.cmake)

set(SOURCES "app.rc"
            "app.ico"
            "assets/app.html"
            "include/pch.h"
            "include/Resources.h"
            "include/Knox.h"
            "src/Knox.cpp"
            "src/main.cpp")

set(ENABLE_INSPECTOR true)

add_app(Knox "${SOURCES}")

target_include_directories(Knox PRIVATE "include/")

target_precompile_headers(Knox PRIVATE "include/pch.h")

target_link_libraries(Knox Core)

install(TARGETS Knox RUNTIME DESTINATION bin)