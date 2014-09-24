#!/bin/bash

./swift -i example/$1.blog -o src/$1.cpp

cd src

g++ -larmadillo -O2 -std=c++11 $1.cpp random/*.cpp -o $1

echo "Running "$1
./$1

cd ..
