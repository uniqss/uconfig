#!/bin/bash

# - install depends tools
# yum -y install git
# yum -y install gcc gcc-c++ autoconf libtool automake make
#

# pushd thirdparty/depends_path
# libtoolize && aclocal && autoheader && autoconf && automake --add-missing
# sh configure
# popd

rm -rf build
mkdir -p build
pushd build

BAT_BUILD_TYPE=relwithdebinfo

cmake -DCMAKE_BUILD_TYPE=$BAT_BUILD_TYPE ..
cmake --build . --config $BAT_BUILD_TYPE

popd


mkdir -p ../../bin/$BAT_BUILD_TYPE/
cp -R ./bin/$BAT_BUILD_TYPE/* ../../bin/$BAT_BUILD_TYPE/

# popd

# echo continue && read -n 1
