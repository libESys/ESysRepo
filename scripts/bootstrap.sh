#!/bin/bash

echo "${TXT_S}ESysRepo Boostrap ...${TXT_CLEAR}"
echo "pwd = "`pwd`

git clone https://gitlab-ci-token:${CI_JOB_TOKEN}@gitlab.com/libesys/esysbuild/dev.git _ci_dev
_ci_dev/scripts/bootstrap.sh
cd build_dev
cd src
cd esysrepo
git checkout ${CI_COMMIT_BRANCH}
cd ../..

echo "pwd = "`pwd`
echo "${TXT_S}ESysRepo Boostrap Done.${TXT_CLEAR}"