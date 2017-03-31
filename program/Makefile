INCLUDES = -I. -I./common
CXX=g++
CXXFLAGS=-c -Wall 

CC=gcc
CCFLAGS=-c -Wall -std=gnu99
LDFLAGS= -Wall -lpthread -lm `pkg-config opencv --cflags --libs` 

CXXSOURCES= $(wildcard *.cpp)
CSOURCES= $(wildcard *.c) $(wildcard common/*.c)
CXXOBJECTS= $(CXXSOURCES:%.cpp=build/%.o)
COBJECTS= $(CSOURCES:%.c=build/%.o)
EXECUTABLE=build/main


.PHONY: directories clean techo

all: $(CSOURCES) $(CXXSOURCES) $(EXECUTABLE)

techo:
	@echo $(COBJECTS)
	@echo $(INCLUDES)
	@echo $(CSOURCES)
	@echo $(wildcard common/*.c)

$(EXECUTABLE): $(CXXOBJECTS) $(COBJECTS)
	$(CXX) $(LDFLAGS) $(CXXOBJECTS) $(COBJECTS) -o $@

$(CXXOBJECTS): build/%.o : %.cpp directories
	$(CXX) $(CXXFLAGS) $(INCLUDES) $< -o $@

$(COBJECTS): build/%.o : %.c directories
	$(CC) $(CCFLAGS) $(INCLUDES) $< -o $@

directories:
	mkdir -p build
	mkdir -p build/common

clean:
	rm -r build
