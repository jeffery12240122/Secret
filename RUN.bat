@echo off

cmake -S . -B build -DCMAKE_VERBOSE_MAKEFILE:BOOL=ON

if %ERRORLEVEL% NEQ 0 (
    echo "CMake configuration failed"
    exit /b %ERRORLEVEL%
)

cmake --build build --verbose

if %ERRORLEVEL% NEQ 0 (
    echo "Build failed"
    exit /b %ERRORLEVEL%
)

echo "Done"
