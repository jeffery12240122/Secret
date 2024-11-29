@echo off
rem 執行 CMake 配置
cmake -S . -B build

rem 執行 CMake 編譯
cmake --build build

rem 運行生成的可執行文件
build\Debug\LCC.exe