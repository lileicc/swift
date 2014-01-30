#!/bin/bash

cd src

g++ -O2 -std=c++11 $1.cpp random/*.cpp -o $1

./$1

cd ..