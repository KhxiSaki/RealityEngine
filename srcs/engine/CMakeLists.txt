file(GLOB_RECURSE srcs 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)


add_library(engine STATIC ${srcs})
add_library(engine::engine ALIAS engine)

target_include_directories(engine PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/srcs>
    $<INSTALL_INTERFACE:include>
)

function(add_vs_filter root_dir files)
    foreach(file ${files})
        file(RELATIVE_PATH path ${root_dir} ${file})
        get_filename_component(filter_path ${path} DIRECTORY)
        string(REPLACE "/" "\\" filter_path ${filter_path})
        source_group(${filter_path} FILES ${file})
        message("[config] add filter : ${filter_path} : ${r_path}")
    endforeach()
endfunction()

if(MSVC)
    message("[build] msvc createing filters ...")
    add_vs_filter(${CMAKE_CURRENT_SOURCE_DIR} "${srcs}")
endif()
