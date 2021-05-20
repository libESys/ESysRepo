#!/bin/bash

echo "${TXT_S}Build ...${TXT_CLEAR}"
echo "pwd = "`pwd`

cd build_dev
mkdir build
cd build
mkdir cmake
cd cmake
pwd

cmake ../.. -DESYSREPO_BUILD_DOC=On
echo "    ${TXT_S}Build esysrepo_t ...${TXT_CLEAR}"
make esysrepo_t -j`nproc --all`
if [ ! $? -eq 0 ]; then
   echo "${TXT_E}Cmake failed.${TXT_CLEAR}"
   exit 1
fi
echo "    ${TXT_S}Build esysrepo_t done.${TXT_CLEAR}"

echo "    ${TXT_S}Build esysrepo_doc ...${TXT_CLEAR}"
make esysrepo_doc -j`nproc --all`
if [ ! $? -eq 0 ]; then
   echo "${TXT_E}Build esysrepo_doc failed.${TXT_CLEAR}"
   exit 1
fi
echo "    ${TXT_S}Build esysrepo_doc done.${TXT_CLEAR}"

mkdir ../../../public/cpp_api
cp -R src/esysrepo/doc/html ../../../public/cpp_api

echo "pwd = "`pwd`
echo "${TXT_S}Build done.${TXT_CLEAR}"
