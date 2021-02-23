#!/bin/bash

rm -rf bin build lib
mkdir build
cd build
conan install ..
cd ..
cmake -GNinja -Bbuild -DCMAKE_BUILD_TYPE=Release .
ninja -C build/
sudo ninja install -C build/
