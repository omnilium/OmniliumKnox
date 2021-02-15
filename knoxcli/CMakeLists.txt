set(EXE_NAME KnoxCLI)

set(PRIVATE_H_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/private")

set(CPP_FILES
		"KnoxCLI.cpp"
		)

set(PRIVATE_H_FILES
		"${PRIVATE_H_FOLDER}/pch.h"
		"${PRIVATE_H_FOLDER}/Resources.h"
		)

add_executable(${EXE_NAME}
		${CPP_FILES}
		${PRIVATE_H_FILES}
		"app.rc")

target_include_directories(${EXE_NAME} PRIVATE
		"${CMAKE_CURRENT_SOURCE_DIR}"
		"${PRIVATE_H_FOLDER}"
		)

target_precompile_headers(${EXE_NAME} PRIVATE
		"private/pch.h"
		)

target_link_libraries(${EXE_NAME} PUBLIC
		Core
		)

install(TARGETS ${EXE_NAME}
		DESTINATION bin
		)