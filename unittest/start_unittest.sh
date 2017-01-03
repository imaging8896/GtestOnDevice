#!/bin/sh

make clean
make
./unittest  --gtest_color=yes
make clean
