all: random-number

random-number: main.cc
	g++ -Wall -O2 -o random-number main.cc

clean:
	rm -f random-number *.exe