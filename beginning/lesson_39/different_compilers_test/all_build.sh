#!/bin/bash

rm -rf bin_compare
mkdir bin_compare

./clang_build.sh
./gcc_build.sh
./icc_build.sh

cp -rf clang/bin/test_clang bin_compare
cp -rf gcc/bin/test_gcc bin_compare
cp -rf icc/bin/test_icc bin_compare
