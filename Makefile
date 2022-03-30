.PHONY: all build rebuild check test memtest clean coverage_tests

all: clean check build test coverage_tests memtest

BUILD_DIRECTORY = build

TARGET_TEST = ./gtest

TARGET_COVERAGE = [789]

NUMBER_OF_RECORDS  = 10000

PATH_TO_SETS = generator_data/sets/female_name.txt generator_data/sets/male_name.txt generator_data/sets/surname.txt generator_data/sets/female_surname.txt generator_data/sets/male_surname.txt generator_data/sets/position.txt

PATH_OUTPUT = tmp.txt

clean:
	rm -rf build coverage-report valgrind.log test.log coverage.info

generate:
	./build/generator_data/generator ${NUMBER_OF_RECORDS}  ${PATH_OUTPUT} ${PATH_TO_SETS}

check:
	./run_linters.sh

build:
	./run_build.sh

rebuild: clean build

test:
	./run_build.sh
	./build/gtest/${TARGET_TEST}

coverage_tests:
	./run_build.sh
	./build/gtest/${TARGET_TEST}
	./run_coverage.sh $(TARGET_COVERAGE)

memtest:
	./run_build.sh
	./run_memtest.sh ./build/gtest/${TARGET_TEST}
