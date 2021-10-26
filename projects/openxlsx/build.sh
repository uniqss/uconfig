#!/bin/bash

# - install depends tools
# yum -y install git
# yum -y install gcc gcc-c++ autoconf libtool automake make
#

cd OpenXLSX-0.3.1

BAT_BUILD_TYPE=Release

rm -rf build
mkdir -p build
cd build


cmake -DCMAKE_BUILD_TYPE=$BAT_BUILD_TYPE ..
cmake --build . --config $BAT_BUILD_TYPE


cd ..

mkdir -p ../../include/headers/
cp -R ./OpenXLSX/OpenXLSX.hpp ../../include/

mkdir -p ../../include/headers/
cp -R ./OpenXLSX/headers/* ../../include/headers/

mkdir -p ../../lib/
cp -R ./build/output/$BAT_BUILD_TYPE/*.lib ../../lib/

mkdir -p ../../../bin/$BAT_BUILD_TYPE/
cp -R ./build/output/$BAT_BUILD_TYPE/*.dll ../../../bin/$BAT_BUILD_TYPE/

cd ..

# echo continue && read -n 1
