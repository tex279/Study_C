.PHONY: all build rebuild check test memtest clean

all: clean check build test memtest

clean:
	rm -rf build && rm -rf coverage-report

check:
	./run_linters.sh

build:
	./run_build.sh

rebuild: clean build

test:
	./run_tests.sh

memtest:
	./run_build.sh -DWITH_MEMCHECK=ON
	./run_tests.sh --memcheck
