EXAMPLE_DIR=$(pwd)
mkdir buildInstall
cd build


# Link agaist musl
cmake --build  . --target all
cmake --build  . --target install
cd ../buildInstall
emacs --eval '(gdb "gdb -i=mi ./bin/example8.2")'
