#!/bin/bash

echo "Build ..."
echo "PATH = $PATH"

PATH=/snap/bin:$PATH
echo "PATH = $PATH"

mkdir build
cd build
mkdir cmake
cd cmake
pwd
cmake ../..
make esysrepo_t

echo "Build done."
