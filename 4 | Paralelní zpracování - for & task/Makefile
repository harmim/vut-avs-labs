INTEL_HOME=/usr/local/share/intel/compilers_and_libraries_2019/linux
INTEL_COMPILERS=$(INTEL_HOME)/bin/intel64
CXX=$(INTEL_COMPILERS)/icpc
CXXFLAGS= -std=c++11 -g -xavx -qopt-report=5 -qopt-report-phase=loop,vec -qopenmp -O3 -static-intel -Wl,-rpath=/usr/local/share/intel/lib/intel64_lin/
LIBS=-lpapi

TARGET=lab4
SOURCES=TinyPngOut.cpp Colormap.cpp

.PHONY all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) $(SOURCES) $(TARGET).cpp -o $(TARGET) $(LIBS)

.PHONY clean:
	rm -f lab4 mandelbrot.png
