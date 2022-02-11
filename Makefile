.PHONY: all build clear launch

all: clear build launch

TARGET = 3

build:
	g++ --std=gnu++20 interview_contest/$(TARGET)/$(TARGET).cpp -o task

launch:
	./task