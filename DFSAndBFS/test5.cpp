#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

// Undirected = No direction, edges reach both nodes. (a, b) & (b, a)
// Directed = One direction, edges reach one direction (a, b).

/* You may use this file to test your program.
	This file will not be submitted, as a different test5.cpp will be used.
  Every required method is included here so that you can verify that
		you have included everything the test engine will call. */
int main(int argv, char** argc) {
	Graph mainGraph(true);	// Graph to use for testing

	//	mainGraph.ClearGraph(false);

		// Calls involving vertices.
	mainGraph.AddVertex('a');
	mainGraph.AddVertex('b');
	mainGraph.AddVertex('c');
	mainGraph.AddVertex('d');
	mainGraph.AddVertex('e');

	mainGraph.AddEdge('a', 'b');

	mainGraph.AddEdge('b', 'c');

	mainGraph.AddEdge('c', 'd');

	mainGraph.AddEdge('c', 'e');

	mainGraph.AddEdge('d', 'a');

	cout << "The distance between A and D is: " << mainGraph.SearchForPath('a', 'e', false) << endl;

	//// Other calls.
	//mainGraph.PrintVertexList();
	mainGraph.PrintEdgeList();
}
