.PHONY: all build clear launch

all: clear build launch

build:
	g++ --std=gnu++20 5/training/5_old.cpp -o task

launch:
	./task