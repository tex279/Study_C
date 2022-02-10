.PHONY: all build clear launch

all: clear build launch

build:
	g++ --std=gnu++20 5/training/5.cpp -o task

launch:
	./task