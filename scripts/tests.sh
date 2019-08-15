#!/bin/bash
cd ../bin
make -j4
cp test/check .
./check -l
./check -d yes

rm check
