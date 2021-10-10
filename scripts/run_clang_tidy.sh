#!/bin/bash

echo "${TXT_S}Run cland-tidy ...${TXT_CLEAR}"
echo "pwd = "`pwd`

source scripts/start_ssh_agent

cd build_dev
cd build
cd cmake
make tidy-esysrepo-cleanup -j`nproc --all`
RESULT_TIDY=$?

mkdir -p ../../../public/clang_tidy
cp -R src/esysrepo/src/esys/repo/esysrepo-clang_tidy.html ../../../public/clang_tidy
cp -R src/esysrepo/src/esys/repo/esysrepo-clang_tidy.log ../../../public/clang_tidy

if [ ! ${RESULT_TIDY} -eq 0 ]; then
   echo "${TXT_W}Clang-tidy failed.${TXT_CLEAR}"
fi

echo "pwd = "`pwd`
echo "${TXT_S}Run cland-tidy done.${TXT_CLEAR}"
