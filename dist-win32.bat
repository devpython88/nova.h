@echo off
@rem make directories if they dont exist
@rem `build`
if not exist ".\build" mkdir build

@rem `dist`

set /p dist_directory=Enter dist directory name:

if not exist ".\build\%dist_directory%" mkdir "build\%dist_directory%"
if not exist ".\build\%dist_directory%\include" mkdir "build\%dist_directory%\include"
if not exist ".\build\%dist_directory%\lib" mkdir "build\%dist_directory%\lib"

@rem compile
cd build

echo List of generators:
echo [-NAME------------------------EXE--]
echo [Unix Makefiles             - make]
echo [Ninja                      - ninja]
echo [Ninja Multi-Config         - ninja]
echo [NMake Makefiles            - nmake]
echo [MSYS Makefiles             - make]
echo [MinGW Makefiles            - mingw32-make]
echo [-----------------------------------]

set /p build_system=Enter cmake generator name (case sensitive): 
cmake -G "%build_system%" ..
set /p build_system_exe=Enter cmake generator exe (*=ignore for systems like msvc): 

if not "%build_system_exe%"=="*" (
    %build_system_exe%
)

@rem copy files
copy ..\src\*.h %dist_directory%\include
copy .\libnova.a %dist_directory%\lib


echo Done!