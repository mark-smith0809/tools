rm -rf ./build
rm -rf ./bin
mkdir ./build
mkdir ./bin

cd ./build
export CC=/c/msys64/mingw64/bin/gcc
export CXX=/c/msys64/mingw64/bin/g++
cmake .. -G "Unix Makefiles"
cmake --build .

cp ./test_serial ../bin/
