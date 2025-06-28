# K36 SDL Game

Проект простой 2D-игры для ретро-консоли **K36**, использующей прошивку **EmuELEC** (Amlogic, AArch64), написан на **C++ с использованием SDL2**.


### На хосте (Linux x86_64):
- `cmake`
- `ninja` (опционально)
- `clang++ или aarch64-linux-gnu-g++-10` (или `gcc-10`, `g++-10`)
- `qemu-user-static`
- `clang-format`, `clang-tidy` (опционально)
- `SDL2` (для нативной сборки)
- `valgrind` (анализ сборки по памяти)
- `zip` (для создания архивов)

### Консоль:
- Прошивка **EmuELEC** (тестировалось на Amlogic-ng.aarch64 4.7)
- Поддержка запуска бинарников из пользовательской директории (`/storage/downloads` или аналогичной)

## 🛠 Структура проекта

```text
.
├── CMakeLists.txt
├── toolchains/
│   ├── native-gcc10.cmake
│   └── aarch64-gcc10-sysroot.cmake
├── vendor/
│   └── k36-sysroot/          # sysroot для EmuELEC
├── src/
│   ├── main.cpp
│   └── CoreModule/
│       ├── Game.h
│       └── Game.cpp
├── build/
├── build-k36/
└── .clang-tidy

```



## 🧱 Сборка
🔧 1. Нативная сборка (для запуска на хосте)


```bash
cmake -B build -DCMAKE_TOOLCHAIN_FILE=toolchains/native-gcc10.cmake -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j
```
🔧 2. Кросс-сборка под K36 (aarch64 с sysroot)

```bash
cmake -B build-k36 -DCMAKE_TOOLCHAIN_FILE=toolchains/aarch64-gcc10-sysroot.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build build-k36 -j
```
SDL2 ищется вручную: путь к libSDL2.so и headers должен быть доступен в sysroot. Иногда нужно делать симлинки в vendor/k36-sysroot/usr/include/SDL2.

## ▶ Запуск
✅ На хосте:
bash
```
./build/main
```
✅ В QEMU:
bash
```
qemu-aarch64-static -L ./vendor/k36-sysroot ./build-k36/main
```
✅ На консоли:

Скопируй build-k36/main на SD-карту (например, в /storage/downloads)

Через терминал EmuELEC:


```bash
cd /storage/downloads
chmod +x main
./main
```
### 🧹 Автоматизация и Стат. Анализ
Автоформат: clang-format -i src/**/*.cpp src/**/*.h

Анализ: clang-tidy src/main.cpp -- -I./vendor/k36-sysroot/usr/include

### 🧪 Отладка и ресурсы
Используй valgrind, massif (с qemu или на x86)

Смотри /proc/self/status для оценки памяти

Можно использовать текстовый логгер или SDL overlay