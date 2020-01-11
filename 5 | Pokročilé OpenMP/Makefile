# /**
# * @File        Makefile
# * @Author      Marta Cudova
# * @Affiliation FIT, Brno University of Technology
# * @Email       icudova@fit.vutbr.cz
# * @Comments    Linux makefile for OpenMP Lab 5
# * 
# * @Tool        AVS lab 5 2019
# * @Created     18 March  2018, 18:40
#
# */


CXX = g++

CXXFLAGS   = -std=c++11 -O0 -fopenmp -g -I.
LDFLAGS    = -g -std=c++11 -O0 -fopenmp

TARGET_LCK = sections-locks
TARGET_CRT = sections-critical

all:    $(TARGET_LCK) $(TARGET_CRT) 

# ==============================================

example1: $(TARGET_CRT)
 
$(TARGET_CRT): $(TARGET_CRT).o		\

	$(CXX) $(LDFLAGS) $(TARGET_CRT).o 	\
	-o $@

$(TARGET_CRT).o: $(TARGET_CRT).cpp
	$(CXX) $(CXXFLAGS) -c $(TARGET_CRT).cpp
    
# ==============================================

example2: $(TARGET_LCK)

$(TARGET_LCK): $(TARGET_LCK).o		\

	$(CXX) $(LDFLAGS) $(TARGET_LCK).o 	\
	-o $@

$(TARGET_LCK).o: $(TARGET_LCK).cpp
	$(CXX) $(CXXFLAGS) -c $(TARGET_LCK).cpp
    
# ==============================================

clean:
	rm -f *.o sections-locks sections-critical
