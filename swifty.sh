#!/bin/bash

fname=example/$1.blog
fname=${fname##*/}
fname=${fname%.*}

if [[ ! -f example/$1.blog ]] ; then
    echo 'File' example/$1.blog ' is not there, aborting.'
    exit
fi

./swift -i example/$1.blog -o src/$fname.cpp --model-output data

cd src

g++ -Ofast -std=c++11 $fname.cpp random/*.cpp -o $fname -larmadillo

mv $fname.cpp ../out
mv $fname ../out

echo "Running "$fname
cd ..

./out/$fname
