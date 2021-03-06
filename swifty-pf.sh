#!/bin/bash

./swift -e ParticleFilter -i example/$1.blog -o src/$1.cpp

cd src

g++ -Ofast -std=c++11 $1.cpp random/*.cpp -o $1 -larmadillo

echo "Running "$1
./$1

cd ..
