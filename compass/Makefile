COMPILE_FLAGS = -Wall -mcpu=native -O2 --std=c++11 -lm
LINKER_FLAGS = -Wall -mcpu=native -O2 --std=c++11 -lm
BUILD_DIR = build

vpath %.cpp source
vpath bcm2835/src
INC_FLAGS := -I include

SRCS := $(wildcard source/*.cpp)
$(info $(SRCS))

OBJS := $(patsubst source/%.cpp, build/%.o, $(SRCS))
$(info $(OBJS))

exec: $(OBJS)
	gcc -o $(BUILD_DIR)/$@ $^ bcm2835/src/bcm2835.o -lm



$(BUILD_DIR)/%.o: %.cpp $(BUILD_DIR)
	gcc $(COMPILE_FLAGS) $(INC_FLAGS) -c $< -o $@


build:
	mkdir build

clean:
	rm -rf build
