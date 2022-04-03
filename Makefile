.PHONY: all build rebuild check test memtest_general clean coverage_tests_general test_imperative coverage_tests_imperative memtest_imperative

all: clean check build generate test_general coverage_tests_general memtest_general test_imperative coverage_tests_imperative memtest_imperative

NUMBER_OF_RECORDS  = 100
GENERATOR = ./build/generator_data/generator
SETS_FOR_GEN = generator_data/sets/female_name.txt generator_data/sets/male_name.txt generator_data/sets/surname.txt generator_data/sets/female_surname.txt generator_data/sets/male_surname.txt generator_data/sets/position.txt

NEW_DATABASE = generated_database.txt
SORTED_DATABASE = sorted_database.txt
REPORT = report.txt

TARGET_TEST_GENERAL = ./build/gtest/gtest_general
TARGET_TEST_IMPERATIVE = ./build/gtest/gtest_imperative


TARGET_COVERAGE = [6789]
GTEST_GENERAL_COVERAGE = build/project/CMakeFiles/GENERAL.dir/general/src
GTEST_IMPERATIVE_COVERAGE = build/project/CMakeFiles/IMPERATIVE_MODEL.dir/pattern/imperative_model/src

#1 - imperative mod
#2 - multi_threaded mod

clean:
	rm -rf build coverage-report valgrind.log test.log coverage.info generated_database.txt report.txt sorted_database.txt

check:
	./run_linters.sh

build:
	./run_build.sh

rebuild: clean build

launch_imp:
	mkdir -p report
	./build/HW-2 1 ${NEW_DATABASE} ${SORTED_DATABASE} ${REPORT}

launch_multi:
	mkdir -p report
	./build/HW-2 2 ${NEW_DATABASE} ${SORTED_DATABASE} ${REPORT}

generate:
	./run_build.sh
	${GENERATOR} ${NUMBER_OF_RECORDS} ${NEW_DATABASE} ${SETS_FOR_GEN}

test_general:
	./run_build.sh
	${GENERATOR} ${NUMBER_OF_RECORDS} ${NEW_DATABASE} ${SETS_FOR_GEN}
	${TARGET_TEST_GENERAL}

coverage_tests_general:
	./run_build.sh
	./run_build.sh
	${GENERATOR} ${NUMBER_OF_RECORDS} ${NEW_DATABASE} ${SETS_FOR_GEN}
	${TARGET_TEST_GENERAL}
	./run_coverage.sh ${GTEST_GENERAL_COVERAGE} ${TARGET_COVERAGE}

memtest_general:
	./run_build.sh
	${GENERATOR} ${NUMBER_OF_RECORDS} ${NEW_DATABASE} ${SETS_FOR_GEN}
	./run_memtest.sh ${TARGET_TEST_GENERAL}

test_imperative:
	./run_build.sh
	${GENERATOR} ${NUMBER_OF_RECORDS} ${NEW_DATABASE} ${SETS_FOR_GEN}
	${TARGET_TEST_IMPERATIVE}

coverage_tests_imperative:
	./run_build.sh
	./run_build.sh
	${GENERATOR} ${NUMBER_OF_RECORDS} ${NEW_DATABASE} ${SETS_FOR_GEN}
	${TARGET_TEST_IMPERATIVE}
	./run_coverage.sh ${GTEST_IMPERATIVE_COVERAGE} ${TARGET_COVERAGE}

memtest_imperative:
	./run_build.sh
	${GENERATOR} ${NUMBER_OF_RECORDS} ${NEW_DATABASE} ${SETS_FOR_GEN}
	./run_memtest.sh ${TARGET_TEST_IMPERATIVE}

1coverage_tests_general:
	./run_coverage.sh ${GTEST_GENERAL_COVERAGE} ${TARGET_COVERAGE}