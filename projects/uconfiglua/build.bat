
set BAT_BUILD_TYPE=RelWithDebInfo


rm -rf build
mkdir build
cd build


cmake -A x64 -DCMAKE_BUILD_TYPE=%BAT_BUILD_TYPE% ..
cmake --build . --config %BAT_BUILD_TYPE%


cd ..


xcopy /Y /S /Q .\bin\%BAT_BUILD_TYPE%\*.lib ..\lib\


@REM pause
