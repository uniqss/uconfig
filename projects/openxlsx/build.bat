cd OpenXLSX-0.3.1

set BAT_BUILD_TYPE=RelWithDebInfo


rm -rf build
mkdir build
cd build


cmake -A x64 -DCMAKE_BUILD_TYPE=%BAT_BUILD_TYPE% ..
cmake --build . --config %BAT_BUILD_TYPE%


cd ..

mkdir ..\..\include\openxlsx\
cp -R .\OpenXLSX\OpenXLSX.hpp ..\..\include\openxlsx\

mkdir ..\..\include\openxlsx\headers\
cp -R ./OpenXLSX/headers/*.hpp ..\..\include\openxlsx\headers\

cp -R .\build\OpenXLSX\OpenXLSX-Exports.hpp ..\..\include\openxlsx\

mkdir ..\..\lib\
cp -R ./build/output/%BAT_BUILD_TYPE%/*.lib ..\..\lib\

mkdir ..\..\..\bin\%BAT_BUILD_TYPE%\
cp -R ./build/output/%BAT_BUILD_TYPE%/*.dll ..\..\..\bin\%BAT_BUILD_TYPE%\

cd ..

rem pause