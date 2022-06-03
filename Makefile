.PHONY: all build_dz build_rk launch build_module_3

all: build launch

TARGET_DZ = 3

TARGET_RK = C

TARGET_MODULE = module_3

build_dz:
	g++ --std=gnu++20  $(TARGET_MODULE)/$(TARGET_DZ).cpp -o task

build_rk:
	g++ -g --std=gnu++20 -Wall -Wextra -Werror -Wpedantic $(TARGET_MODULE)/RK/$(TARGET_RK).cpp -o task

launch:
	./task

HDRS_DIR = module_3/1/include

SRCS = \
       module_3/1/*.cpp

build_module_3:
	g++ --std=gnu++20  -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) $(SRCS) -o task