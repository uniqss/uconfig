
rmdir /S /Q build
mkdir build
cd build


cmake -A x64 -DCMAKE_BUILD_TYPE=relwithdebinfo ..
cmake --build . --config relwithdebinfo


cd ..


xcopy /Y /S /Q .\bin\*.exe ..\..\bin\
xcopy /Y /S /Q .\bin\*.pdb ..\..\bin\


rem pause