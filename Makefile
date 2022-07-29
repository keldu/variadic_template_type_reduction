.PHONY: all run clean

all: matching

matching: main.cpp matching.h
	clang++ -std=c++17 main.cpp -o matching

run: all
	./matching

clean:
	rm matching
