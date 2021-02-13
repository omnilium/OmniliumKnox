set(CPP_FILES "src/KnoxC.cpp")

set(H_FILES "include/pch.h"
			"include/Resources.h"
)

add_executable(KnoxC ${CPP_FILES} ${H_FILES} "app.rc")

target_include_directories(KnoxC PRIVATE "include/")

target_precompile_headers(KnoxC PRIVATE "include/pch.h")

target_link_libraries(KnoxC Core)

install(TARGETS KnoxC RUNTIME DESTINATION bin)