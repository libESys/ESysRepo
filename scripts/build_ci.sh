#!/bin/bash

echo "Build ..."
echo "PATH = $PATH"

mkdir build
cd build
mkdir cmake
cd cmake
pwd
cmake ../..
make esysrepo_t -j`nproc --all`

echo "Build done."
