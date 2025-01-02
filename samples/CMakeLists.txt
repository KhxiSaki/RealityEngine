#samples for unit test

add_executable(sample win32_entry.cpp)

target_link_libraries(sample PRIVATE engine::engine)
#target_include_directories(sample PRIVATE ${CMAKE_SOURCE_DIR}/srcs)

