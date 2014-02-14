FLAGS=-O2 -std=c++11

BENCHMARK_DIR=src/benchmark/handcompile/

all: urnball hurricane

urnball:
	g++ ${FLAGS} rejsampler_urnball.cpp LWSamplerUrnBall.cpp execute_urnball.cpp -o execute_urnball

hurricane:
	g++ ${FLAGS} rejsampler_hurricane.cpp lwsampler_hurricane.cpp execute_hurricane.cpp -o execute_hurricane 
  
burglary:
	g++ ${FLAGS} LWSamplerBurglary.cpp -o execute_burglary

csi:
	g++ ${FLAGS} LWSamplerCSI.cpp -o execute_csi

run:
	./execute_urnball 1000000
	./execute_burglary
	./execute_csi
	./execute_hurricane