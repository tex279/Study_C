.PHONY: all build clear launch

all: clear build launch

build:
	g++ --std=gnu++17 4/4.cpp -o task

launch:
	./task