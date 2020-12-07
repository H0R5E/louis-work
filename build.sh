#!/bin/bash

rm -r bin build lib
mkdir build
cd build
conan install ..
cd ..
cmake -GNinja -Bbuild .
ninja -C build/
