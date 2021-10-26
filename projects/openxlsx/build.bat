cd OpenXLSX-0.3.1

set BAT_BUILD_TYPE=RelWithDebInfo


rmdir /S /Q build
mkdir build
cd build


cmake -A x64 -DCMAKE_BUILD_TYPE=%BAT_BUILD_TYPE% ..
cmake --build . --config %BAT_BUILD_TYPE%


cd ..

xcopy /Y /Q .\OpenXLSX\OpenXLSX.hpp ..\..\include\openxlsx\
xcopy /Y /S /Q .\OpenXLSX\headers\* ..\..\include\openxlsx\headers\

xcopy /Y /S /Q .\build\output\%BAT_BUILD_TYPE%\*.lib ..\..\lib\
xcopy /Y /S /Q .\build\output\%BAT_BUILD_TYPE%\*.dll ..\..\..\bin\%BAT_BUILD_TYPE%\

cd ..

rem pause