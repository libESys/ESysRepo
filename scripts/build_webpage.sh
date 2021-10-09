#!/bin/bash

echo "${TXT_S}Build webpage ...${TXT_CLEAR}"
echo "pwd = "`pwd`

PWD_DIR=`pwd`
mkdir -p public
# cd build_dev
# cd src/esysrepo/doc/web
# ls -als themes/

# hugo -b /esysrepo/esysrepo -d ${PWD_DIR}/public

cd build_dev
mkdir -p build/cmake
cd build/cmake

export ESYSREPO_HUGO_PUBLIC_DIR=${PWD_DIR}/public
cmake ../.. -DESYSREPO_BUILD_DOC=On
if [ ! $? -eq 0 ]; then
   echo "${TXT_E}Cmake configuration failed.${TXT_CLEAR}"
   exit 1
fi

make esysrepo_hugo -j`nproc --all`
if [ ! $? -eq 0 ]; then
   echo "${TXT_E}Build webpage failed: Hugo returned an error.${TXT_CLEAR}"
   exit 1
fi

echo "pwd = "`pwd`
echo "${TXT_S}Build webpage done.${TXT_CLEAR}"
