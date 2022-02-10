.PHONY: all build clear launch

all: clear build launch

build:
	g++ --std=gnu++20 3/training/3.cpp -o task

launch:
	./task