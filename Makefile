exec = main

all: $(exec)
.PHONY: all

clean:
	rm $(exec)

% : %.cc
	g++ -g -std=c++17 $< -o $@.exe

