all: test5

test5: test5.o graph.o
	g++ -Wall -o test5 test5.o graph.o

test5.o: test5.cpp
	g++ -Wall -c test5.cpp

graph.o: graph.cpp
	g++ -Wall -c graph.cpp

clean:
	rm -f test5 *.o

run: test5
	./test5