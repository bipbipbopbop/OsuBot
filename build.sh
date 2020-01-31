#!/bin/sh

cmake CMakeLists.txt -B build
make -C build
cp build/OsuBot .