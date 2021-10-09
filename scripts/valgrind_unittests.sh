#!/bin/bash

echo "${TXT_S}Valgrind unit test starts ...${TXT_CLEAR}"
echo "pwd = "`pwd`

source scripts/start_ssh_agent

cd build_dev
mkdir -p build/cmake
cd build
cd cmake

make valgrind-html-esysrepo_t -j`nproc --all`

# valgrind --leak-check=full \
#          --show-leak-kinds=all \
#          --track-origins=yes \
#          --verbose \
#          --log-file=valgrind-out.txt \
#          ./build/cmake/bin/esysrepo_t --logger=HRF,test_suite,stdout:JUNIT,all,report_junit.txt \
#          --xml-file=valgrind-out.xml

# valgrind-ci valgrind-out.xml --number-of-errors

mkdir -p ../../../public/logs
mkdir -p ../../../public/valgrind
cp src/esysrepo/src/esys/repo/*_junit.txt ../../../public/logs
cp src/esysrepo/src/esys/repo/esysrepo_t-valgrind-out.* ../../../public/logs
cp src/esysrepo/src/esys/repo/esysrepo_t-valgrind-out.* ../../../public/valgrind
cp -R src/esysrepo/src/esys/repo/test/valgrind_html/* ../../../public/valgrind

echo "pwd = "`pwd`
echo "${TXT_S}Valgrind unit test done.${TXT_CLEAR}"
