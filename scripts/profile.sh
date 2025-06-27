#!/bin/bash

# Проверка аргументов
if [ $# -lt 1 ]; then
  echo "Usage: $0 path_to_executable [args...]"
  exit 1
fi

EXEC="$1"
shift

# Запуск valgrind massif
echo "Running massif for $EXEC ..."
valgrind --tool=massif --time-unit=ms "$EXEC" "$@"

# Ищем последний файл massif.out.*
OUTFILE=$(ls -t massif.out.* 2>/dev/null | head -n 1)

if [ -z "$OUTFILE" ]; then
  echo "massif output file not found!"
  exit 1
fi

echo "massif output file: $OUTFILE"
echo "Massif report:"
ms_print "$OUTFILE"
