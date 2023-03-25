CC=g++
# CC=clang++

CXXFLAGS=-std=c++17 -Wall -Wextra

SOURCES=main.cpp markov_model.cpp
OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
