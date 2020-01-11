# Architektura procesoru (ACH 2016)
# Projekt c. 1 (nbody)
# Login: xlogin00

CC=/usr/local/share/intel/compilers_and_libraries/linux/bin/intel64/icpc
CFLAGS=-lpapi -std=c++11 -ansi-alias -Wl,-rpath=/usr/local/share/intel/lib/intel64_lin/
OPT=-O2 -Wall -xavx -qopenmp
REPORT=-qopt-report=5

N=1000
DT=0.001f
STEPS=1000

PARAMS=-DN=$(N) -DDT=$(DT) -DSTEPS=$(STEPS)

INPUT=../input.dat
OUTPUT=../step0.dat

PAPI_EVENTS=

all:
	$(CC) $(CFLAGS) $(OPT) $(REPORT) $(PARAMS) -c velocity.cpp
	$(CC) $(CFLAGS) $(OPT) $(REPORT) $(PARAMS) -c nbody.cpp
	$(CC) $(CFLAGS) $(OPT) $(PARAMS) -S -fsource-asm -c nbody.cpp
	$(CC) $(CFLAGS) $(OPT) $(PARAMS) velocity.o nbody.o main.cpp -o nbody
	$(CC) $(CFLAGS) gen.cpp -o gen

clean:
	rm -f *.o nbody

run:
	PAPI_EVENTS='$(PAPI_EVENTS)' ./nbody $(INPUT) $(OUTPUT)
