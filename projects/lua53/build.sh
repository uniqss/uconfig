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


set TMP_DEST_PATH=../include/lua/
set TMP_SRC_PATH=./src/
mkdir -p %TMP_DEST_PATH%
cp -R %TMP_SRC_PATH%lua.hpp %TMP_DEST_PATH%
cp -R %TMP_SRC_PATH%lua.h %TMP_DEST_PATH%
cp -R %TMP_SRC_PATH%luaconf.h %TMP_DEST_PATH%
cp -R %TMP_SRC_PATH%lualib.h %TMP_DEST_PATH%
cp -R %TMP_SRC_PATH%lauxlib.h %TMP_DEST_PATH%

mkdir -p ../include/lua/
cp -R ./include/* ../include/lua/

# mkdir -p ../../bin/$BAT_BUILD_TYPE
# cp -R ./bin/$BAT_BUILD_TYPE/* ../../bin/$BAT_BUILD_TYPE/

mkdir -p ../lib/
xcopy /Y /S /Q ./bin/$BAT_BUILD_TYPE/*.lib ../lib/




# popd

# echo continue && read -n 1
