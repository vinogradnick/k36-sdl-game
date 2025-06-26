#!/usr/bin/bash
rm -rf build-native && mkdir build-native && cd build-native
cmake ..  -DCMAKE_BUILD_TYPE=Release
make