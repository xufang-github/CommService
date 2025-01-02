#添加自定义筛选器
function(add_filter FILTER_NAME)
        foreach(FILE_NAME ${ARGN})
                file(GLOB_RECURSE My_FILES ${CMAKE_CURRENT_SOURCE_DIR}/${FILE_NAME})
                source_group(${FILTER_NAME} FILES ${My_FILES})
        endforeach(FILE_NAME)
endfunction(add_filter FILTER_NAME)
