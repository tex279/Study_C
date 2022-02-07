.PHONY: all build clear launch

all: clear build launch

build:
	g++ --std=gnu++17 5/5.cpp -o task

launch:
	./task