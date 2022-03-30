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

mkdir -p ../../include/openxlsx/
cp -R ./OpenXLSX/OpenXLSX.hpp ../../include/openxlsx/

mkdir -p ../../include/openxlsx/headers/
cp -R ./OpenXLSX/headers/* ../../include/openxlsx/headers/

cp -R ./build/OpenXLSX/OpenXLSX-Exports.hpp ../../include/openxlsx/

mkdir -p ../../lib/
cp -R ./build/output/$BAT_BUILD_TYPE/*.lib ../../lib/

mkdir -p ../../../bin/$BAT_BUILD_TYPE/
cp -R ./build/output/$BAT_BUILD_TYPE/*.dll ../../../bin/$BAT_BUILD_TYPE/

cd ..

# echo continue && read -n 1
