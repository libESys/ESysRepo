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
if [ ! $? -eq 0 ]; then
   echo "${TXT_E}Build failed: cmake failed.${TXT_CLEAR}"
   exit 1
fi

make esysrepo_t -j`nproc --all`
if [ ! $? -eq 0 ]; then
   echo "${TXT_E}Build failed: make failed.${TXT_CLEAR}"
   exit 1
fi

echo "pwd = "`pwd`
echo "${TXT_S}Build done.${TXT_CLEAR}"
