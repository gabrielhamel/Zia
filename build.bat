@echo off

:: CMake exist ?
where cmake.exe>NUL 2>NUL
if %ERRORLEVEL% neq 0 (
    echo Cmake isn't not installed or isn't not in environment: https://cmake.org/download/
    cmd /k
    exit 0
)

:: Conan exist ?
where conan.exe>NUL 2>NUL
if %ERRORLEVEL% neq 0 (
    echo Conan isn't installed or isn't in environment: https://conan.io/downloads.html
    cmd /k
    exit 0
)

:: Bincrafters is added ?
conan remote list | findstr "bincrafters:">NUL 2>NUL
if %ERRORLEVEL% neq 0 (
    conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
)

:: Atolab is added ?
conan remote list | findstr "atolab:">NUL 2>NUL
if %ERRORLEVEL% neq 0 (
    conan remote add atolab https://api.bintray.com/conan/atolab/public-conan
)

:: Remove if exist
if exist build (
    rd /S /Q build
)

mkdir build
cd build
conan install .. --build=missing
if %ERRORLEVEL% neq 0 (
    cmd /k
    exit 0
)
cmake .. -DCMAKE_GENERATOR_PLATFORM=x64
cmake --build . --target ALL_BUILD --config Release

:: Go back
cd ..

:: Copy dependencies
FOR /F delims^=^; %%i IN ('conan config home') DO set CONAN=%%i
set CRITERION=%CONAN%\data\criterion\2.3.2\atolab\stable\package\31d36f265a443e5a60bf134581a5b3a52e2f8c00\bin\criterion.dll
copy "%CRITERION%" "build\bin\criterion.dll">NUL 2>NUL

:: End
cmd /k
exit 0
