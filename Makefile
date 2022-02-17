.PHONY: all build clear launch build_int

all: clear build launch

TARGET = 7

TARGET_IN = 7

build:
	g++ --std=gnu++20 interview_contest/$(TARGET)/$(TARGET_IN).cpp -o task

launch:
	./task