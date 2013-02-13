CC=g++
FLAGS=-c -Wall -O2 $(shell pkg-config opencv yaml-cpp --cflags)
LIBS=$(shell pkg-config yaml-cpp opencv --libs)
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

clean:
	$(shell rm -rf bin)

$(EXECUTABLE): $(OBJECTS)
	$(CC) bin/$(OBJECTS) -o bin/$@ $(LIBS)

.cpp.o:
	$(CC) $(FLAGS) $< -o bin/$@
