CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=process.cpp system.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=c3316165A3

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o : %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o core
