CC=g++
FLAGS=-c -Wall -O2 $(shell pkg-config opencv --cflags)
LIBS=$(shell pkg-config opencv --libs)
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(FLAGS) $< -o $@
