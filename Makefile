.PHONY: all build clear launch build_int

all: clear build launch

TARGET = 7

TARGET_IN = 7

TARGET_MODULE = mudule_1

build:
	g++ --std=gnu++20 $(TARGET_MODULE)/$(TARGET)/$(TARGET_IN).cpp -o task

launch:
	./task