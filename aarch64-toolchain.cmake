# toolchains/aarch64-gcc10-sysroot.cmake

# Указываем платформу
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Используем компиляторы версии 10
set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc-10)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++-10)

# Указываем sysroot
set(SYSROOT ${CMAKE_SOURCE_DIR}/vendor/k36-sysroot)
set(CMAKE_SYSROOT ${SYSROOT})

# Опции для компиляции и линковки
set(CMAKE_C_FLAGS "--sysroot=${SYSROOT}" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "--sysroot=${SYSROOT}" CACHE STRING "" FORCE)

# Настройка поиска файлов
set(CMAKE_FIND_ROOT_PATH ${SYSROOT})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)