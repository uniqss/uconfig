@echo off

cd projects


pushd spdlog
call build.bat
popd

echo "build spdlog done ==========================================================================="


cd uconfiglua
call build.bat
cd ..

echo "build uconfiglua done ==========================================================================="



rem pause