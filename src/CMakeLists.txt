cmake_minimum_required(VERSION 3.8)
# 解决方案名
project(CommService)
# 添加lib目录
link_directories(${CMAKE_INSTALL_PREFIX}/lib)
# 设置输出路径
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)

set(INSTALL_LIB_PATH ${CMAKE_INSTALL_PREFIX}/lib)
set(INSTALL_BIN_PATH ${CMAKE_INSTALL_PREFIX}/bin)
set(INSTALL_INCLUDE_PATH ${CMAKE_INSTALL_PREFIX}/include)

#src文件夹
set(ROOT_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Src)

# 安卓设备
if(ANDROID)
set(CMAKE_SYSTEM_NAME Android)
set(CMAKE_SYSTEM_VERSION 21)  # 或其他你目标设备的 SDK 版本
#set(CMAKE_ANDROID_ARCH_ABI arm64-v8a)  # 或其他架构
#set(CMAKE_ANDROID_NDK "C:/Program Files/Java/android-sdk_r24.4.1-windows/android-sdk-windows")
#set(CMAKE_ANDROID_SDK "F:/install/android-ndk-r21e-windows-x86_64/android-ndk-r21e")



set(CMAKE_PREFIX_PATH F:/Qt/Qt5.13.2/5.13.2/android_arm64_v8a/lib/cmake/Qt5)
endif()

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")





find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Sql REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)
#find_package(Qt5 COMPONENTS Core REQUIRED)
#find_package(Qt5 COMPONENTS Sql REQUIRED)
#find_package(Qt5 COMPONENTS Widgets REQUIRED)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 添加子工程
add_subdirectory(Src)
