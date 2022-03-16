TARGET = ./main.out

KEYS = -Wextra -Werror -g -std=gnu99 -Wall \
	-Wcast-align -Wcast-qual -Wconversion -Wduplicated-branches -Wduplicated-cond \
	-Wfloat-equal -Wlogical-op -Wredundant-decls -Wsign-conversion

VALGRIND_LOG = "valgrind.log"

HDRS = \
	   project/include

SRCS = \
       project/src/*.c

.PHONY: all check build test memtest rebuild clean

all: clean check build test memtest

check:
	./run_linters.sh

build: $(TARGET)

test: $(TARGET)
	./tests/run.sh $(TARGET)

memtest: $(TARGET)
	./tests/run.sh $(TARGET) --memcheck

rebuild: clean build

$(TARGET): $(SRCS)
	$(CC)  $(KEYS) $(addprefix -I,$(HDRS)) -o $(TARGET) $(CFLAGS) $(SRCS)

clean:
	rm -f $(TARGET) ${VALGRIND_LOG}