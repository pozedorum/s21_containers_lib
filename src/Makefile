#CC = gcc
#CFLAGS := -lstdc++ -std=c++17 -Wall -Werror -Wextra

CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++17
TEST_FLAGS = -lgtest -pthread #-lgtest_main 

EXECUTABLE = test

CONTAINERS = containers/*.h
TEST_MAP = tests/test_map.cc
TEST_SET = tests/test_set.cc
TEST_STACK = tests/test_stack.cc
TEST_LIST = tests/test_list.cc
TEST_VECTOR = tests/test_vector.cc
TEST_QUEUE = tests/test_queue.cc
TEST_START = tests/test_start.cc

ALL_TESTS = $(TEST_LIST) $(TEST_STACK) $(TEST_VECTOR) $(TEST_QUEUE) $(TEST_MAP) $(TEST_SET) $(TEST_START)

all: clean gcov_report

test: clean
	mkdir binaries
	$(CXX) $(CXXFLAGS) $(ALL_TESTS) -o binaries/testing $(TEST_FLAGS)
	./binaries/testing

valgrind: test
	valgrind --tool=memcheck --leak-check=yes ./binaries/testing

gcov_report: clean
	#mkdir binaries
	$(CXX) $(CXXFLAGS) --coverage $(ALL_TESTS)  $(TEST_FLAGS) -o binaries/testing_gcov
	./binaries/testing_gcov
	lcov -t "test" -c -d . -o test_report.info --rc lcov_branch_coverage=1
	lcov --remove test_report.info '*c++/*' '*gtest/*' '*tests/*' --output-file test_report.info
	genhtml -o report test_report.info
	open ./report/index.html


clang_check:
	cp ../materials/linters/.clang-format .
	clang-format -n containers/*.h tests/*.cc
	rm .clang-format

clean:
	rm -rf main *.o testing binaries/*
	rm -rf *.o *.a *.gch *.gcno *.gcda test_report.info report