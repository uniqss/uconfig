cd spdlog-1.8.5

set BAT_BUILD_TYPE=Release


rmdir /S /Q build
mkdir build
cd build


cmake -A x64 -DCMAKE_BUILD_TYPE=%BAT_BUILD_TYPE% ..
cmake --build . --config %BAT_BUILD_TYPE%


cd ..

xcopy /Y /S /Q .\include\* ..\..\include\
xcopy /Y /S /Q .\build\%BAT_BUILD_TYPE%\* ..\..\lib\

xcopy /Y /S /Q .\build\include\* ..\..\include\

cd ..

rem pause