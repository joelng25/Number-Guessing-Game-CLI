CXX ?= g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

all: random-number

random-number: main.cc game.h
	$(CXX) $(CXXFLAGS) -o random-number main.cc

test: tests/test_game.cc game.h
	$(CXX) $(CXXFLAGS) -o test_game tests/test_game.cc
	./test_game

clean:
	rm -f random-number test_game *.exe

.PHONY: all test clean
