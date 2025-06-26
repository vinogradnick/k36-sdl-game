cmake_minimum_required(VERSION 3.13)
project(K36GCC10App CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------------------------------
 message( "CHECK STATUS CROSS-COMPILATION ${CMAKE_CROSSCOMPILING}")

if(CMAKE_CROSSCOMPILING)
    message(STATUS "Cross-compiling: manually locating SDL2 in sysroot")

    # Путь к sysroot из toolchain
    set(SYSROOT ${CMAKE_SYSROOT})

    set(SDL2_INCLUDE_DIR ${SYSROOT}/usr/include/SDL2)
    set(SDL2_LIBRARY ${SYSROOT}/usr/lib/libSDL2.so)

    if(NOT EXISTS ${SDL2_INCLUDE_DIR})
        message(WARNING "SDL2 include not found in sysroot, trying host includes")
        set(SDL2_INCLUDE_DIR /usr/include/SDL2)
    endif()

    if(EXISTS ${SDL2_INCLUDE_DIR} AND EXISTS ${SDL2_LIBRARY})
        message(STATUS "Found SDL2 include: ${SDL2_INCLUDE_DIR}")
        message(STATUS "Found SDL2 lib: ${SDL2_LIBRARY}")
        set(SDL2_FOUND TRUE)
    else()
        message(FATAL_ERROR "SDL2 not found in sysroot at ${SDL2_INCLUDE_DIR} or ${SDL2_LIBRARY}")
    endif()
else()
    set(SDL2_FOUND TRUE)
    set(SDL2_INCLUDE_DIR /usr/include/SDL2)
    set(SDL2_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2.so)

endif()



# ---------------------------------------


# Общие флаги для всех режимов
add_compile_options(-O2 -Wall -Wextra -Werror)

# Рекурсивно ищем все .cpp в src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Собираем бинарь
add_executable(main ${SOURCES})



# -------------------------------------------------

message("LINK SDL2 ${SDL2_INCLUDE_DIR} ${SDL2_LIBRARY}")

if(SDL2_FOUND)
    target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIR})
    target_link_libraries(main PRIVATE ${SDL2_LIBRARY})
endif()


# Если нужны include'ы из других папок, добавь их так:
# target_include_directories(main PRIVATE include/)
