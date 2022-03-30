.PHONY: all build rebuild check test memtest clean coverage_tests

all: clean check build test coverage_tests memtest

BUILD_DIRECTORY = build

TARGET_TEST = ./gtest

TARGET_COVERAGE = [789]

clean:
	rm -rf build coverage-report valgrind.log test.log coverage.info

check:
	./run_linters.sh

build:
	./run_build.sh -DVALGRIND_MEMCHECK=OFF

rebuild: clean build

test:
	./run_build.sh -DVALGRIND_MEMCHECK=OFF
	./build/gtest/${TARGET_TEST}

coverage_tests:
	./run_build.sh -DVALGRIND_MEMCHECK=OFF
	./build/gtest/${TARGET_TEST}
	./run_coverage.sh $(TARGET_COVERAGE)

memtest:
	./run_build.sh -DVALGRIND_MEMCHECK=ON
	./run_memtest.sh ./build/gtest/${TARGET_TEST}

launch:
	./build/generator_data/generator 10000 tmp.txt generator_data/sets/female_name.txt generator_data/sets/male_name.txt generator_data/sets/surname.txt generator_data/sets/female_surname.txt generator_data/sets/male_surname.txt generator_data/sets/position.txt


