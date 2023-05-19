#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

// Defines a graph.
class Graph {
public:
	bool isItdirected;
	vector<char> verticesList; // The order of vertices.

	vector<string> edgeList; // The order of directed edges.

	vector<vector<int>> edgeAdjacencyMatrix; // The matrix of edges.

	// First Search Processing
	vector<char> Processed;

	// The queue for Breadth First Search
	queue<char> BFSQueue;

	// The queue for Depth First Search
	//stack<char> DFSStack;
	stack<char> DFSStack;
	vector<bool> hasBeenVisited;

	// Constructors/Destructor for Graph.
	Graph(bool isDirected);
	~Graph();

	// Clears the graph and sets if the graph is directed now.
	void ClearGraph(bool isDirected);

	// Searches for the path between two names.  Returns the length of the first path found.
	int SearchForPath(char name1, char name2, bool useBFS);

	// Prints the list of vertices in the order they were added.
	void PrintVertexList();

	// Prints the list of edges in the order they were added.
	void PrintEdgeList();

	// Adds a vertex with the specified name to the graph.
	void AddVertex(char name);

	// Removes the vertex with the specified name from the graph.
	void RemoveVertex(char name);

	// Adds an edge between the two vertices to the graph.
	void AddEdge(char name1, char name2);

	void RemoveEdge(int index, char name);

	void resizeMatrix(size_t newSize);

	int DFSearch(int startingIndex, char name2);

	vector<char>::iterator SearchNode(char name);

	vector<string>::iterator SearchEdge(string name1, string name2);
};

#endif