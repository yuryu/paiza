CXX=c++
CXXFLAGS=-g -Wall

.PHONY: test all clean

test: all
	prove -v

all: paiza-ec

clean:
	rm -rf paiza-ec
	rm -rf *.dSYM

paiza-ec: paiza-ec.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

