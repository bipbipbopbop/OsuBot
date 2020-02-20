#!/bin/sh

checkMSYS=${MSYSTEM}
checkVS="${VSCMD_VER}"

if [[ -n $checkVS ]]; then
    cmake -G "NMake Makefiles" CMakeLists.txt -B build -DENABLE_TESTS=ON
elif [[ "$checkMSYS" == "MINGW64" ]] || [[ "$checkMSYS" == "MINGW32" ]]; then
    cmake -G "MSYS Makefiles" CMakeLists.txt -B build -DENABLE_TESTS=ON
elif [[ -z "$checkMSYS" ]]; then
    cmake CMakeLists.txt -B build -DENABLE_TESTS=ON
fi

if [[ -n $checkVS ]]; then
    cd build
    nmake
    cd ..
else
    make -C build
fi

mkdir logs
cp build/OsuBot .
