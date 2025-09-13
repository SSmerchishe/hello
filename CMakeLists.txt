cmake_minimum_required(VERSION 3.10)
project(hello VERSION 1.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(hello hello.c)

target_compile_definitions(hello PRIVATE PROJECT_VERSION=\"${PROJECT_VERSION}\")

execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_HASH
)

add_definitions(-DGIT_HASH="${GIT_HASH}")
