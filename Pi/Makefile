CC=g++
FLAGS=-c -Wall -O2 $(shell pkg-config opencv yaml-cpp --cflags)
LIBS=$(shell pkg-config yaml-cpp opencv --libs)
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(FLAGS) $< -o $@
