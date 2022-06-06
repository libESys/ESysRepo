#!/bin/bash

echo "${TXT_S}Valgrind unit test starts ...${TXT_CLEAR}"
echo "pwd = "`pwd`

source scripts/start_ssh_agent

cd build_dev
mkdir -p build/cmake
cd build
cd cmake

make esysrepo_t-valgrind-html -j`nproc --all`

mkdir -p ../../../public/logs
mkdir -p ../../../public/valgrind
cp src/esysrepo/src/esys/repo/*_junit.txt ../../../public/logs
cp src/esysrepo/src/esys/repo/esysrepo_t-valgrind-out.* ../../../public/logs
cp src/esysrepo/src/esys/repo/esysrepo_t-valgrind-out.* ../../../public/valgrind
cp -R src/esysrepo/src/esys/repo/test/valgrind_html/* ../../../public/valgrind

echo "pwd = "`pwd`
echo "${TXT_S}Valgrind unit test done.${TXT_CLEAR}"
