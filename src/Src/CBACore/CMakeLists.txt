set(OUT_NAME CBACore)

add_definitions(-DCBACore_LIB)

include_directories(${INSTALL_INCLUDE_PATH})
include_directories(${ROOT_SRC_DIR})
link_directories(${INSTALL_LIB_PATH})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)


file(GLOB_RECURSE UI_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)

file(GLOB_RECURSE RC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.rc)

file(GLOB_RECURSE QRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)

qt5_add_resources(QRC_FILES ${QRC_FILES})

QT5_WRAP_UI(xxx ${UI_FILES})

source_group("ui" FILES ${UI_FILES})
source_group("qrc" FILES ${RC_FILES})
source_group("generate_file/ui" FILES ${UI_FILES})
source_group("generate_file/moc" FILES ${MOC_FILES})
source_group("generate_file/qrc" FILES ${QRC_FILES})

add_library(
        ${OUT_NAME} SHARED
        ${HEADER_FILES}
        ${SRC_FILES}
)
if(ANDROID)
target_link_libraries(
        ${OUT_NAME}
        Qt5::Core
        Qt5::Sql
        GLESv2
        log
        z
)
else()
target_link_libraries(
		${OUT_NAME}
		Qt5::Core
		Qt5::Sql
)
endif()
