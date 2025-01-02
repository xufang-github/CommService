set(OUT_NAME CBAClient)

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

add_executable(
        ${OUT_NAME}
        ${HEADER_FILES}
        ${SRC_FILES}
        ${UI_FILES}
        ${RC_FILES}
        ${QRC_FILES}
)

target_link_libraries(
        ${OUT_NAME}
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        Qt5::Network
)
# 去除控制台窗口
SET_PROPERTY(TARGET ${OUT_NAME} PROPERTY LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
SET_PROPERTY(TARGET ${OUT_NAME} PROPERTY LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
