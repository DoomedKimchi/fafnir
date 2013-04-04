CC=g++
LIBS=opencv yaml-cpp
FLAGS=-c -Wall -O2 --std=c++11 $(shell pkg-config $(LIBS) --cflags)
LDFLAGS=$(shell pkg-config $(LIBS) --libs)
SOURCES=main.cpp image_processing.cpp target_processing.cpp client.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

clean:
	$(shell rm -rf bin)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(FLAGS) $< -o $@
