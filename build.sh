#!/bin/sh

checkMSYS=${MSYSTEM}
if [[ -z "$checkMSYS" ]]; then
    cmake CMakeLists.txt -B build -DENABLE_TESTS=ON
elif [[ "$checkMSYS" == "MINGW64" ]] || [[ "$checkMSYS" == "MINGW32" ]]; then
    cmake -G "MSYS Makefiles" CMakeLists.txt -B build -DENABLE_TESTS=ON
fi
make -C build
cp build/OsuBot .