.PHONY: all build clear launch

all: clear build launch

build:
	g++ --std=gnu++20 interview_contest/1/1.cpp -o task

launch:
	./task