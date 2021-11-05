TARGET = ./main.out
HDRS_DIR = project/include

SRCS = \
       project/src/main.c \
       project/src/w_r_file.c \
       project/src/test_w_to_file.c \
       project/src/utils_for_file.c \
       project/src/std_in_out_data.c

.PHONY: all build rebuild check test memtest clean

all: clean check test memtest

$(TARGET): $(SRCS)
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)

build: $(TARGET)

rebuild: clean build

check:
	./linters/run.sh

test: $(TARGET)
	./btests/run.sh $(TARGET)

memtest: $(TARGET)
	./btests/run.sh $(TARGET) --memcheck

clean:
	rm -rf $(TARGET) *.dat
