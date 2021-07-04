#!/bin/bash

echo "${TXT_S}ESysRepo Boostrap ...${TXT_CLEAR}"
echo "pwd = "`pwd`

git clone https://gitlab-ci-token:${CI_JOB_TOKEN}@gitlab.com/libesys/esysbuild/dev.git _ci_dev
_ci_dev/scripts/bootstrap.sh
cd build_dev
cd src
cd esysrepo

if [ ! -z ${CI_COMMIT_BRANCH+x} ];
then
    echo "Commit branch : ${CI_COMMIT_BRANCH}"
    TO_CHECKOUT=${CI_COMMIT_BRANCH}
elif [ ! -z ${CI_MERGE_REQUEST_REF_PATH+x} ];
then
    echo "Merge request : ${CI_MERGE_REQUEST_REF_PATH}"
    TO_CHECKOUT=${CI_COMMIT_SHA}
else
    echo "${TXT_E}Neither a branch commit nor a merge request?!${TXT_CLEAR}"
    exit 1
fi

echo "Checking out : ${TO_CHECKOUT}"
git checkout ${TO_CHECKOUT}
if [ ! $? -eq 0 ]; then
   echo "${TXT_E}Git checkout failed.${TXT_CLEAR}"
   exit 1
fi
cd ../..

echo "pwd = "`pwd`
echo "${TXT_S}ESysRepo Boostrap Done.${TXT_CLEAR}"