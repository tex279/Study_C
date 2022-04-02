.PHONY: all build rebuild check test memtest clean coverage_tests

all: clean check build test coverage_tests memtest

BUILD_DIRECTORY = build

TARGET_TEST_GENERAL = ./gtest_general

TARGET_COVERAGE = [789]

NUMBER_OF_RECORDS  = 100

PATH_TO_SETS = generator_data/sets/female_name.txt generator_data/sets/male_name.txt generator_data/sets/surname.txt generator_data/sets/female_surname.txt generator_data/sets/male_surname.txt generator_data/sets/position.txt

PATH_NEW_DATABASE = generated_database.txt

PATH_OUTPUT_SORTED_DATABASE = sorted_database.txt

PATH_REPORT = report.txt

PATH_GTEST_GENERAL = build/project/CMakeFiles/gtest_general.dir

#1 - imperative mod
#2 - multi_threaded mod
TYPE_WORK = 1

clean:
	rm -rf build coverage-report valgrind.log test.log coverage.info generated_database.txt

generate:
	./build/generator_data/generator ${NUMBER_OF_RECORDS} ${PATH_NEW_DATABASE} ${PATH_TO_SETS}

check:
	./run_linters.sh

build:
	./run_build.sh

rebuild: clean build

launch_imp:
	./build/project/HW-2 ${TYPE_WORK} ${PATH_NEW_DATABASE} ${PATH_OUTPUT_SORTED_DATABASE} ${PATH_REPORT}

test_general:
	./run_build.sh
	./build/gtest/${TARGET_TEST_GENERAL}

coverage_tests_general:
	./run_build.sh
	./build/gtest/${TARGET_TEST_GENERAL}
	./run_coverage.sh ${PATH_GTEST_GENERAL} $(TARGET_COVERAGE)

memtest:
	./run_build.sh
	./run_memtest.sh ./build/gtest/${TARGET_TEST}