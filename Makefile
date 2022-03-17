.PHONY: all build rebuild check test memtest clean coverage_tests

all: clean check build test coverage_tests memtest

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
	./build/test.out

coverage_tests:
	./run_coverage.sh

memtest:
	./memtest.sh $(TARGET_TEST)
