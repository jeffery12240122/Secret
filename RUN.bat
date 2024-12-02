@echo off
rem 執行 CMake 配置，生成詳細的 Makefile 或建構系統
cmake -S . -B build -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON

rem 執行 CMake 編譯，啟用詳細輸出
cmake --build build --verbose

rem 運行生成的可執行文件
build\Debug\LCC.exe