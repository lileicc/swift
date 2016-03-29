#!/bin/bash

./swift -i example/$1.blog -o src/$1.cpp

cd src

g++ -Ofast -std=c++11 $1.cpp random/*.cpp -o $1 -larmadillo

mv $1.cpp ../out
mv $1 ../out

echo "Running "$1
cd ..

./out/$1
