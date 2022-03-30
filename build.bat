@echo off

cd projects


pushd spdlog
call build.bat
popd

echo "build spdlog done ==========================================================================="


pushd lua53
call build.bat
popd

echo "build lua53 done ==========================================================================="


pushd openxlsx
call build.bat
popd

echo "build openxlsx done ==========================================================================="


pushd uconfiglua
call build.bat
popd

echo "build uconfiglua done ==========================================================================="


pushd uconfig
call build.bat
popd

echo "build uconfig done ==========================================================================="



rem pause