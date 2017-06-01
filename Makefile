CC=g++
CC_FLAGS=-Wall -Werror -pedantic -std=c++11
EXEC=bin/rshell
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

$(EXEC): $(OBJECTS)
	mkdir -p bin
	$(CC) $(OBJECTS) -o $(EXEC) -lboost_regex

debug: $(SOURCES)
	mkdir -p bin
	$(CC) $(CC_FLAGS) -DDEBUG $(SOURCES) -o $(EXEC)_debug -lboost_regex

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@ -lboost_regex

clean:
	rm -f $(EXEC) $(OBJECTS) vgcore.*

test:
	tests/run_tests.sh
