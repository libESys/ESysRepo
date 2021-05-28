#!/bin/bash

cd doc/web
git clone https://github.com/matcornic/hugo-theme-learn.git themes/hugo-theme-learn
hugo  -b /  --gc --minify -d ../../public
