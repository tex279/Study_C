TARGET = ./main.out

KEYS = -Wextra -Werror -g -std=gnu99 -Wall \
	-Wcast-align -Wcast-qual -Wconversion -Wduplicated-branches -Wduplicated-cond \
	-Wfloat-equal -Wlogical-op -Wredundant-decls -Wsign-conversion

VALGRIND_LOG = "valgrind.log"

HDRS = \
	   project/include

SRCS = \
       project/src/*.c

.PHONY: all check build test memtest rebuild clean build_cmake

all: clean check build test memtest

check:
	./linters/run_linters.sh

build: $(TARGET)

test: $(TARGET)
	./tests/run.sh $(TARGET)

memtest: $(TARGET)
	./tests/run.sh $(TARGET) --memcheck

rebuild: clean build

build_cmake:
	./build.sh

$(TARGET): $(SRCS)
	$(CC)  $(KEYS) $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS)

clean:
	rm -rf build