#!/usr/bin/bash
cd build
rm -rf k36
mkdir k36
cd k36
cmake ./../.. -DCMAKE_TOOLCHAIN_FILE=./toolchain/aarch64-toolchain.cmake 
make
