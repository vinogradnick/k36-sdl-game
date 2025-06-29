


cmake .. \
  -DCMAKE_SYSTEM_NAME=Linux \
  -DCMAKE_C_COMPILER=clang \
  -DCMAKE_CXX_COMPILER=clang++ \
  -DCMAKE_C_FLAGS="--sysroot=/home/vinograd/vendor/k36-sysroot --target=aarch64-linux-gnu -mcpu=cortex-a35" \
  -DCMAKE_CXX_FLAGS="--target=aarch64-linux-gnu -mcpu=cortex-a35" \
  -DCMAKE_EXE_LINKER_FLAGS="--target=aarch64-linux-gnu -mcpu=cortex-a35" \
  -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
  -DBUILD_SHARED_LIBS=OFF \
  -DCMAKE_BUILD_TYPE=Release