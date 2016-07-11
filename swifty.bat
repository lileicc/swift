swift -i %* -o _target.cpp

g++ -std=c++11 -Wall src/random/*.cpp _target.cpp -o _target -O3

_target
