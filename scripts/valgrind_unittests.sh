#!/bin/bash

echo "${TXT_S}Valgrind unit test starts ...${TXT_CLEAR}"
echo "pwd = "`pwd`

source scripts/start_ssh_agent

cd build_dev

valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./build/cmake/bin/esysrepo_t --logger=HRF,test_suite,stdout:JUNIT,all,report_junit.txt

mkdir ../public/logs
cp *_junit.txt ../public/logs
cp valgrind-out.txt ../public/logs

echo "pwd = "`pwd`
echo "${TXT_S}Valgrind unit test done.${TXT_CLEAR}"