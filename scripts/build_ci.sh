#!/bin/bash

echo "${TXT_S}Build ...${TXT_CLEAR}"
echo "pwd = "`pwd`

cd build_dev
mkdir build
cd build
mkdir cmake
cd cmake
pwd
cmake ../..
make esysrepo_t -j`nproc --all`

echo "pwd = "`pwd`
echo "${TXT_S}Build done.${TXT_CLEAR}"
