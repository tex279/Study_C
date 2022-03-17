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
	./run_test.sh

coverage_tests:
	./run_coverage.sh

memtest:
	./run_memtest.sh $(TARGET_TEST)
