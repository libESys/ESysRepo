#!/bin/bash

echo "${TXT_S}Run code coverage on unit tests ...${TXT_CLEAR}"
echo "pwd = "`pwd`

source scripts/start_ssh_agent

cd build_dev
cd build
cd cmake
make esysrepo_coverage -j`nproc --all`
RESULT_UT=$?

mkdir -p ../../../public/coverage
mkdir -p ../../../public/logs
cp -R src/esysrepo/src/esys/repo/esysrepo_coverage/* ../../../public/coverage
cp src/esysrepo/src/esys/repo/report.junit ../../../public/logs/esysrepo_junit.txt

if [ ! ${RESULT_UT} -eq 0 ]; then
   echo "${TXT_E}Code coverage on unit tests failed.${TXT_CLEAR}"
   exit 1
fi

echo "pwd = "`pwd`
echo "${TXT_S}Run code coverage on unit tests done.${TXT_CLEAR}"
