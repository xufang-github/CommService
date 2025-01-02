#添加插件宏定义
function(INSTALLTO TARGET)

FOREACH(FLOAD_PATH ${ARGN})
    install(
        TARGETS  ${TARGET}
		RUNTIME DESTINATION bin
        DESTINATION ${INSTALL_BIN_PATH}/../${FLOAD_PATH} #StarBasic项目的INSTALL安装的文件有相对目录，此处有路径修改
    )
    #message(${INSTALL_BIN_PATH}/${FLOAD_PATH})
ENDFOREACH(FLOAD_PATH ${OUTPUT_PATHS} )

endfunction(INSTALLTO)
