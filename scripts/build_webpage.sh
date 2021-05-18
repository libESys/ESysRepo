#!/bin/bash

echo "${TXT_S}Build webpage ...${TXT_CLEAR}"
echo "pwd = "`pwd`

PWD_DIR=`pwd`
cd build_dev
cd src/esysrepo/doc/web
ls -als themes/

hugo -b https://libesys.gitlab.io/esysrepo/esysrepo -d ${PWD_DIR}/public

echo "pwd = "`pwd`
echo "${TXT_S}Build webpage done.${TXT_CLEAR}"