#!/bin/sh

cmake CMakeLists.txt -B build -DENABLE_TESTS=ON
make -C build
cp build/OsuBot .