add_executable(hello main.c)
target_link_libraries(hello PRIVATE keys)
target_link_libraries(hello PRIVATE client)
target_include_directories(hello PRIVATE ${CMAKE_SOURCE_DIR}/lib)
