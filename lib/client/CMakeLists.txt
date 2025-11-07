add_library(client STATIC client.c)
target_include_directories(client PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR} #путь для client.h
    ${PROJECT_SOURCE_DIR}/lib/error #путь для error.h
)

find_package(OpenSSL REQUIRED)
target_link_libraries(client PRIVATE OpenSSL::SSL OpenSSL::Crypto)
