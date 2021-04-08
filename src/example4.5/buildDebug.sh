mkdir build
mkdir buildInstall
cd build

cmake -DCMAKE_INSTALL_PREFIX=../buildInstall -DCMAKE_BUILD_TYPE=Debug ../
cmake --build  . --target all
cmake --build  . --target install
cd ../buildInstall
emacs --eval '(gdb "gdb -i=mi ./bin/example4.5")'
