@echo off
@rem make directories if they dont exist
@rem `build`
if not exist ".\build" mkdir build

@rem `dist`
if not exist ".\build\dist" mkdir build\dist
if not exist ".\build\dist\include" mkdir build\dist\include
if not exist ".\build\dist\lib" mkdir build\dist\lib

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

set /p P_BS=Enter cmake generator name (case sensitive): 
cmake -G %P_BS% ..
set /p P_BS_EXE=Enter cmake generator exe (*=ignore for systems like msvc): 

if not "%P_BS_EXE%"=="*" (
    %P_BS_EXE%
)

@rem copy files
copy ..\src\*.h dist\include
copy .\libnova.a dist\lib


echo Done!