# Create directories if they do not exist

if [ ! -d "build-linx" ]; then
    mkdir build-linx
fi

if [ ! -d "dist" ]; then
    mkdir dist
fi

if [ ! -d "dist/include" ]; then
    mkdir dist/include
fi

if [ ! -d "dist/lib" ]; then
    mkdir dist/lib
fi

# cd into the build-linx directory
cd build-linx

# ask for generator
echo "List of generators:"

echo "[-NAME------------------------EXE---------]"
echo "[Unix Makefiles             - make        ]"
echo "[Ninja                      - ninja       ]"
echo "[Ninja Multi-Config         - ninja       ]"
echo "[NMake Makefiles            - nmake       ]"
echo "[MSYS Makefiles             - make        ]"
echo "[MinGW Makefiles            - mingw32-make]"
echo "[-----------------------------------------]"

P_BS=""
P_EXE=""

if [ -z "$1" ]; then
    echo "enter cmake generator name (case sensitive):"
    read P_BS
else
    P_BS="$1"
fi

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -G "$P_BS" ..

if [ -z "$2" ]; then
    echo "enter cmake generator exe (*=ignore for systems like msvc):"
    read P_EXE
else
    P_EXE="$2"
fi

if [ "$P_EXE" != "*" ]; then
    $P_EXE
fi

# copy the files
cp ../src/*.h ./dist/include
cp ../src/*.hpp ./dist/include
cp ./libnova.a ./dist/lib

echo "Package the files into TAR? (y/n)"
read P_TAR

if [ "$P_TAR" = "y" ]; then
    echo "Enter tar name: "
    read P_TARNAME
    tar -czvf "$P_TARNAME.tar.gz" ./dist
    echo "Done"
fi
