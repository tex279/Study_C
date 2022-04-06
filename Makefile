.PHONY: all build clear launch build_int

all: clear build launch

TARGET = 3

TARGET_MODULE = module_1

build:
	g++ --std=gnu++20 -Wall -Wextra -Werror -Wpedantic $(TARGET_MODULE)/$(TARGET).cpp -o task

check:
	./run_linters.sh

launch:
	./task