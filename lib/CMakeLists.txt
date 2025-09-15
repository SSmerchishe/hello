add_library(keys STATIC keys.c)
target_include_directories(keys PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})