#!/bin/bash

rm -rf bin build lib
mkdir build
cd build
conan install ..
cd ..
cmake -GNinja -Bbuild -DCMAKE_BUILD_TYPE=Release .
ninja -C build/ -j7 louis
cmake -GNinja -Bbuild -DCMAKE_BUILD_TYPE=Release -DESPEAKNG_BUILD=OFF .
sudo ninja install -C build/
