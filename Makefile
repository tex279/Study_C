.PHONY: all build rebuild check test memtest clean memtest_TEST

all: clean check build test memtest

TARGET_TEST = ./build/test.out
TARGET_MAIN = ./build/main

clean:
	rm -rf build && rm -rf coverage-report

check:
	./run_linters.sh

build:
	./run_build.sh

rebuild: clean build

test:
	./run_build.sh
	./run_tests.sh

memtest:
	./run_build.sh
	./run_memtest.sh

memtest_TEST:
	./run_build.sh
	./memtest.sh $(TARGET_TEST)
