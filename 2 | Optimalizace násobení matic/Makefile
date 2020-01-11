INTEL_HOME=/usr/local/share/intel/compilers_and_libraries_2019/linux
INTEL_COMPILERS=$(INTEL_HOME)/bin/intel64
CXX=$(INTEL_COMPILERS)/icpc -std=c++11 -g -xavx -qopt-report=5 -qopt-report-phase=loop,vec
CXXFLAGS=-O0 #-qopenmp-simd
TARGET=lab2
PAPI_EVENTS="PAPI_L1_DCM"
N="1000"

all: matmul

matmul:clean-papi
	$(CXX) $(CXXFLAGS) $(TARGET).cpp -o matmul

gen:
	$(CXX) gen-matrix.cpp -o gen

matmul-papi:clean-papi
	$(CXX) -DPAPI -lpapi $(CXXFLAGS) $(TARGET).cpp -o matmul-papi

matmul-mkl:
	$(CXX) -DPAPI -lpapi -static-intel -mkl=sequential $(CXXFLAGS) $(TARGET)-mkl.cpp -o matmul-mkl

A: gen Makefile
	./gen $N A
B: gen Makefile
	./gen $N B

run: A B matmul-papi Makefile 
	 ./matmul-papi $N A B C 


clean:
	rm -f matmul-mkl matmul-papi gen matmul *.optrpt
clean-papi:
	rm -f matmul-papi matmul *.optrpt
