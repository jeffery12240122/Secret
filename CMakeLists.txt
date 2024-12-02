# 設定 CMake 最低版本
cmake_minimum_required(VERSION 3.10)

# 設定專案名稱
project(Program)

# 設定 C++ 標準
set(CMAKE_CXX_STANDARD 11)

# 開啟詳細的 Makefile 輸出，只顯示正在編譯的檔案
set(CMAKE_VERBOSE_MAKEFILE TRUE)

# 自動收集資料夾內的所有 .cpp 文件
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/*.cpp" "${CMAKE_SOURCE_DIR}/Tool/*.cpp")

# 添加可執行文件
add_executable(LCC ${SOURCES})
