
set BAT_BUILD_TYPE=RelWithDebInfo


rm -rf build
mkdir build
cd build


cmake -DCMAKE_BUILD_TYPE=$BAT_BUILD_TYPE ..
cmake --build . --config $BAT_BUILD_TYPE


cd ..

mkdir -p ../lib/
cp -R ./bin/$BAT_BUILD_TYPE/*.lib ../lib/

