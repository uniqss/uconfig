


cd projects

rm -rf include
rm -rf lib

pushd spdlog
rm -rf bin
rm -rf build
rm -rf lib
call clean_all.bat
popd

echo "clean spdlog done ==========================================================================="

pushd lua53
call clean_all.bat
popd
echo "clean lua53 done ==========================================================================="

pushd openxlsx
call clean_all.bat
popd
echo "clean openxlsx done ==========================================================================="



pushd uconfiglua
rm -rf bin
rm -rf build
rm -rf lib
call clean_all.bat
popd

echo "clean uconfiglua done ==========================================================================="

pushd uconfig
call clean_all.bat
popd
echo "clean uconfig done ==========================================================================="

