cmake_minimum_required(VERSION 3.22)

project(4-func-calc)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# have to add this because of a gcc bug that creates fake errors
set(CMAKE_C_FLAGS_RELEASE_INIT "-Wno-Stringop-overflow")

execute_process(
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
)

add_executable(${PROJECT_NAME}
	src/main.c
	src/display.c
	src/calc.c
	src/value.c)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib m)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror)
