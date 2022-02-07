.PHONY: all build clear launch

all: clear build launch

build:
	g++ --std=gnu++17 2/2.cpp -o task

launch:
	./task