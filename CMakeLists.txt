cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project(k36-game LANGUAGES CXX)

# C++ стандарт
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Флаги для всех сборок
add_compile_options(-O3 -Wall -Wextra -Werror -fno-exceptions -fdata-sections
  -ffunction-sections)
add_link_options(-Wl,--gc-sections)

# -------------------------------
# Clang-tidy и санитайзеры (для хоста)
# -------------------------------
if(NOT CMAKE_CROSSCOMPILING)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

    if(ENABLE_SANITIZERS)
        add_compile_options(-fsanitize=address,undefined -g -O0)
        add_link_options(-fsanitize=address,undefined)
    endif()
endif()

# -------------------------------
# SDL2: путь вручную (если кросс-компиляция)
# -------------------------------
set(SDL2_FOUND FALSE)

if(CMAKE_CROSSCOMPILING)
    message(STATUS "Cross-compiling: locating SDL2 in sysroot")

    set(SYSROOT ${CMAKE_SYSROOT})
    set(SDL2_INCLUDE_DIR ${SYSROOT}/usr/include/SDL2)

    # Найдём первую подходящую .so
    file(GLOB SDL2_LIB_CANDIDATES "${SYSROOT}/usr/lib/libSDL2.so*")
    list(LENGTH SDL2_LIB_CANDIDATES _sdl2_lib_count)

    if(EXISTS ${SDL2_INCLUDE_DIR} AND _sdl2_lib_count GREATER 0)
        list(GET SDL2_LIB_CANDIDATES 0 SDL2_LIBRARY)
        set(SDL2_FOUND TRUE)
        message(STATUS "Found SDL2 include: ${SDL2_INCLUDE_DIR}")
        message(STATUS "Found SDL2 lib: ${SDL2_LIBRARY}")
    else()
        message(FATAL_ERROR "SDL2 not found in sysroot: ${SDL2_INCLUDE_DIR} or .so file")
    endif()
else()
    # Хостовая сборка
    set(SDL2_INCLUDE_DIR /usr/include/SDL2)
    set(SDL2_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2.so)
    set(SDL2_FOUND TRUE)
endif()



# -------------------------------
# Подключаем Vendor библиотеки
# -------------------------------
# set(YYJSON_DISABLE_NON_STANDARD ON CACHE INTERNAL "")
# add_subdirectory(vendor/yyjson)



# -------------------------------
# Исходники и таргет
# -------------------------------
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

# -------------------------------
# Подключаем SDL2
# -------------------------------
if(SDL2_FOUND)
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARY})
endif()

if(YYJSON_DISABLE_NON_STANDARD)
    target_include_directories(${PROJECT_NAME} PRIVATE /home/vinograd/vendor/yyjson/src)
    target_link_libraries(${PROJECT_NAME} PRIVATE yyjson)
endif()