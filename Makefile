.PHONY: all build clear launch

all: clear build launch

build:
	g++ --std=gnu++17 6/6.cpp -o task

launch:
	./task