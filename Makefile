.PHONY: all build rebuild check test memtest clean

all: clean check build test memtest

clean:
	rm -rf build

check:
	./linters/run_linters.sh

build:
	./run_build.sh

rebuild: clean build

test:
	./build.sh -DWITH_MEMCHECK=OFF
	./run_tests.sh

memtest:
	./build.sh -DWITH_MEMCHECK=ON
	./run_tests.sh --memcheck
