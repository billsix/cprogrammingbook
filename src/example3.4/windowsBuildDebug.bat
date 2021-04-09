mkdir build
mkdir buildInstall
cd build

cmake -DCMAKE_INSTALL_PREFIX=..\buildInstall -DCMAKE_BUILD_TYPE=Debug ..\
cmake --build  . --target all
cmake --build  . --target install

"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\devenv.exe" example3.4.sln
