#!/usr/bin/bash
rm -rf build-k36
mkdir build-k36
cd build-k36
cmake .. -DCMAKE_TOOLCHAIN_FILE=./toolchain/aarch64-toolchain.cmake 
make
