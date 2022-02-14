.PHONY: all build clear launch build_int

all: clear build launch

TARGET = 1

build:
	g++ --std=gnu++20 my_interview/$(TARGET)/$(TARGET).cpp -o task

launch:
	./task