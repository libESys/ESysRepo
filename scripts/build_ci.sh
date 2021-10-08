#!/bin/bash

echo "${TXT_S}Build ...${TXT_CLEAR}"
echo "pwd = "`pwd`

cd build_dev
mkdir build
cd build
mkdir cmake
cd cmake
pwd

if [ -z "${SKIP_CODE_COVERAGE}" ]; then
   cmake ../.. -DESYSREPO_COVERAGE=On -DCMAKE_BUILD_TYPE=Debug
else
   cmake ../.. -DCMAKE_BUILD_TYPE=Debug
fi

if [ ! $? -eq 0 ]; then
   echo "${TXT_E}Build failed: cmake failed.${TXT_CLEAR}"
   exit 1
fi

make esysrepo_t -j`nproc --all`
if [ ! $? -eq 0 ]; then
   echo "${TXT_E}Build failed: esysrepo_t.${TXT_CLEAR}"
   exit 1
fi

make esysrepoexe -j`nproc --all`
if [ ! $? -eq 0 ]; then
   echo "${TXT_E}Build failed: esysrepoexe.${TXT_CLEAR}"
   exit 1
fi

echo "pwd = "`pwd`
echo "${TXT_S}Build done.${TXT_CLEAR}"
