#!/bin/bash

# - install depends tools
# yum -y install git
# yum -y install gcc gcc-c++ autoconf libtool automake make
#



cd projects

rm -rf include
rm -rf lib






pushd spdlog
rm -rf bin
rm -rf build
rm -rf lib
sh clean_all.sh
popd

echo "clean spdlog done ==========================================================================="


pushd uconfiglua
rm -rf bin
rm -rf build
rm -rf lib
sh clean_all.sh
popd

echo "clean uconfiglua done ==========================================================================="

