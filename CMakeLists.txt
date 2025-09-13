cmake_minimum_required(VERSION 3.10)

project(hello VERSION 1.0.0)

add_executable(hello hello.c)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_compile_definitions(hello PRIVATE PROJECT_VERSION=\"${PROJECT_VERSION}\")

execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT GIT_HASH)
    set(GIT_HASH "unknown")
endif()

target_compile_definitions(hello PRIVATE GIT_HASH=\"${GIT_HASH}\")
