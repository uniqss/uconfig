#!/bin/bash

# - install depends tools
# yum -y install git
# yum -y install gcc gcc-c++ autoconf libtool automake make
#



cd projects


cd spdlog
sh build.sh
cd ..

echo "build spdlog done ==========================================================================="


cd lua53
sh build.sh
cd ..

echo "build lua53 done ==========================================================================="


cd uconfiglua
sh build.sh
cd ..

echo "build uconfiglua done ==========================================================================="


cd uconfig
sh build.sh
cd ..

echo "build uconfig done ==========================================================================="




# echo continue && read -n 1
