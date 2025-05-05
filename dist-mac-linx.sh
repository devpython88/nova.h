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

echo "enter cmake generator name (case sensitive):"
read P_BS

cmake -G "$P_BS" ..

echo "enter cmake generator exe (* to ignore, for systems like Visual studio):"
read P_EXE

if [ "$P_EXE" != "*" ]; then
    $P_EXE
fi

# copy the files
cp ../src/*.h ./dist/include
cp ./libnova.a ./dist/lib

echo "Package the files into TAR? (y/n)"
read P_TAR

if [ "$P_TAR" = "y" ]; then
    echo "Enter tar name: "
    read P_TARNAME
    tar -czvf "$P_TARNAME.tar.gz" ./dist
    echo "Done"
fi
