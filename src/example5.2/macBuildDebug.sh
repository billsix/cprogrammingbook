mkdir build
mkdir buildInstall
cd build

cmake -DCMAKE_INSTALL_PREFIX=../buildInstall -DCMAKE_BUILD_TYPE=Debug -GXcode ../
cmake --build  . --target all
cmake --build  . --target install

open example5.2.xcodeproj
cd ..
