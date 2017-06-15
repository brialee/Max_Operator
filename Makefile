.PHONY: clean
CFLAGS = -ansi -pedantic -O0 -Wall

all: maxOperator

maxOperator: main.o line.o node.o graph.o
	g++ -g -o maxOperator $(CFLAGS) main.o line.o node.o graph.o

main.o: main.cpp
	g++ -c -g -o main.o $(CFLAGS) main.cpp

line.o: line.cpp
	g++ -c -g -o line.o $(CFLAGS) line.cpp

node.o: node.cpp
	g++ -c -g -o node.o $(CFLAGS) node.cpp

graph.o: graph.cpp
	g++ -c -g -o graph.o $(CFLAGS) graph.cpp

clean:
	rm -f *.o maxOperator
