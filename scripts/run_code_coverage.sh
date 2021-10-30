#!/bin/bash

echo "${TXT_S}Run code coverage on unit tests ...${TXT_CLEAR}"
echo "pwd = "`pwd`

source scripts/start_ssh_agent

cd build_dev
cd build
cd cmake
make esysrepo_coverage-cleanup -j`nproc --all`
RESULT_UT=$?

lcov --list src/esysrepo/src/esys/repo/esysrepo_coverage.info

mkdir -p ../../../public/coverage
mkdir -p ../../../public/logs
cp -R src/esysrepo/src/esys/repo/esysrepo_coverage/* ../../../public/coverage
cp src/esysrepo/src/esys/repo/esysrepo_coverage.info ../../../public/logs/esysrepo_coverage.info
cp src/esysrepo/src/esys/repo/report.junit ../../../public/logs/esysrepo_junit.txt
bash <(curl -s https://codecov.io/bash) -f src/esysrepo/src/esys/repo/esysrepo_coverage.info || echo "${TXT_W}Codecov did not collect coverage reports.${TXT_CLEAR}"

if [ ! ${RESULT_UT} -eq 0 ]; then
   echo "${TXT_E}Code coverage on unit tests failed.${TXT_CLEAR}"
   exit 1
fi

echo "pwd = "`pwd`
echo "${TXT_S}Run code coverage on unit tests done.${TXT_CLEAR}"
