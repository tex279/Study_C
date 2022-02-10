.PHONY: all build clear launch

all: clear build launch

build:
	g++ --std=gnu++20 1/training/1.cpp -o task

launch:
	./task