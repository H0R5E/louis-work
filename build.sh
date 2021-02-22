#!/bin/bash

rm -r bin build lib
mkdir build
cd build
conan install ..
cd ..
cmake -GNinja -Bbuild -DCMAKE_BUILD_TYPE=Release .
ninja -C build/
