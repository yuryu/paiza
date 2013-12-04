CXX=c++
CXXFLAGS=-g -Wall

.PHONY: test all

test: all
	prove -v

all: paiza-ec

paiza-ec: paiza-ec.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

