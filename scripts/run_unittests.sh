#!/bin/bash

echo "${TXT_S}Run unit tests ...${TXT_CLEAR}"
echo "pwd = "`pwd`

source scripts/start_ssh_agent

cd build_dev

build/cmake/bin/esysrepo_t --logger=HRF,test_suite,stdout:JUNIT,all,report_junit.txt

mkdir ../public/logs
cp *_junit.txt ../public/logs

echo "pwd = "`pwd`
echo "${TXT_S}Run unit tests done.${TXT_CLEAR}"