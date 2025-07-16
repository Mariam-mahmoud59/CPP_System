@echo off
echo Building POS App with MinGW...

if not exist build mkdir build
cd build

echo Configuring with CMake...
cmake -G "MinGW Makefiles" ..

if %ERRORLEVEL% NEQ 0 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

echo Building with MinGW...
mingw32-make

if %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo Build successful!
echo Running application...
./POSApp.exe

pause 