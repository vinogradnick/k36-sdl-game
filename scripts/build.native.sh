#!/usr/bin/bash
mkdir build
cd build
rm -rf linux && mkdir linux && cd linux
cmake ./../..  -DCMAKE_BUILD_TYPE=Release
make