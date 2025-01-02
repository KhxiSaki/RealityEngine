file(GLOB_RECURSE srcs 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)


add_library(engine STATIC ${srcs})
add_library(engine::engine ALIAS engine)

target_include_directories(engine PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/srcs>
    $<INSTALL_INTERFACE:include>
)

