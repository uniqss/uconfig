#!/bin/bash

# - install depends tools
# yum -y install git
# yum -y install gcc gcc-c++ autoconf libtool automake make
#

cd spdlog-1.8.5

BAT_BUILD_TYPE=Release

rm -rf build
mkdir -p build
cd build


cmake -DCMAKE_BUILD_TYPE=$BAT_BUILD_TYPE ..
cmake --build . --config $BAT_BUILD_TYPE


cd ..

mkdir -p ../../include/
cp -R ./include/* ../../include/

mkdir -p ../../lib/
cp -R ./build/*.a ../../lib/


cd ..

# echo continue && read -n 1
