.PHONY: all build rebuild check test memtest clean coverage_tests

all: clean check build test coverage_tests memtest

BUILD_DIRECTORY = build

TARGET_TEST = ./test.out

TARGET_COVERAGE = [789]

clean:
	rm -rf build && rm -rf coverage-report

check:
	./run_linters.sh

build:
	./run_build.sh -DVALGRIND_MEMCHECK=OFF

rebuild: clean build

test:
	./run_build.sh -DVALGRIND_MEMCHECK=OFF
	./build/${TARGET_TEST}

coverage_tests:
	./run_build.sh -DVALGRIND_MEMCHECK=OFF
	./build/${TARGET_TEST}
	./run_coverage.sh $(TARGET_COVERAGE)

memtest:
	./run_build.sh -DVALGRIND_MEMCHECK=ON
	./run_memtest.sh ./build/${TARGET_TEST}


