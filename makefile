CC=g++
CFLAGS=-std=c++11 -Wall
TARGET=test

all: $(TARGET)
$(TARGET): graph.o test_graph.o
	$(CC) $(CFLAGS) -o $(TARGET) graph.o test_graph.o

graph.o: graph.cpp graph.h
	$(CC) $(CFLAGS) -c graph.cpp

test_graph.o: test_graph.cpp graph.h
	$(CC) $(CFLAGS) -c test_graph.cpp

clean:
	rm -f $(TARGET) *.o

