CC=g++
CC_FLAGS=-Wall -Werror -pedantic -std=c++11
EXEC=bin/rshell
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

$(EXEC): $(OBJECTS)
	mkdir -p bin
	$(CC) $(OBJECTS) -o $(EXEC)

debug: $(SOURCES)
	mkdir -p bin
	$(CC) $(CC_FLAGS) -DDEBUG $(SOURCES) -o $(EXEC)_debug

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

clean:
	rm -f $(EXEC) $(OBJECTS)

test:
	tests/run_tests.sh
