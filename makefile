CC = g++
CFLAGS = -std=c++17 
INC_FLAGS += -Ilibs/cpr/include/
INC_FLAGS += -Ilibs/cpr/cpr_generated_includes/

LD_FLAGS += -Llibs/cpr/lib/
LD_FLAGS += -lcpr

CL_FLAGS +=,-rpath=./libs/cpr/lib


.PHONY: all clean

all: dirs libs build
dirs:
	mkdir -p bin
libs:
	cd libs/cpr && cmake -DCMAKE_BUILD_TYPE=Release -DCPR_BUILD_TESTS=OFF . && make
build:
	$(CC) main.cpp $(CFLAGS) $(INC_FLAGS) -Wl$(CL_FLAGS) $(LD_FLAGS) -o bin/main
run: all
	./bin/main
