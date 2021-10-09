#!/bin/bash

cd doc/web
git clone --branch develop --single-branch https://gitlab.com/libesys/esys_hugo_theme.git themes/esys_hugo_theme
hugo  -b /  --gc --minify -d ../../public
