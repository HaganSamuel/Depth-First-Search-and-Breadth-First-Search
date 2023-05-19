#include "graph.h"
#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

// Constructor/Destructor for Graph.
Graph::Graph(bool isDirectedGraph) {
	// If it's undirected, it's basically a doubly linked list compared to a directed, which is a singly linked list.
	isItdirected = isDirectedGraph;
}
Graph::~Graph() {
	ClearGraph(true);
}

// Clears the graph and sets if the graph is directed now.
void Graph::ClearGraph(bool isDirected) {
	isItdirected = isDirected;
	edgeAdjacencyMatrix.erase(edgeAdjacencyMatrix.begin(), edgeAdjacencyMatrix.end());
	verticesList.erase(verticesList.begin(), verticesList.end());
	edgeList.erase(edgeList.begin(), edgeList.end());
}

// Searches for the path between two names.  Returns the length of the first path found.
int Graph::SearchForPath(char name1, char name2, bool useBFS) {

	// Reset all vectors and stacks.
	while (!DFSStack.empty()) {
		DFSStack.pop();
	}

	if (verticesList.empty() || edgeList.empty())
		return -1;

	// Initialize vectors.
	Processed.erase(Processed.begin(), Processed.end());
	hasBeenVisited.erase(hasBeenVisited.begin(), hasBeenVisited.end());

	// Set the size to the # of nodes, and initialize all values to -1.
	// This will keep track of the previous path,
	vector<int> previousPath(verticesList.size(), -1);

	// Breadth First Search method.
	if (useBFS) {
		int fromNodeIndex = SearchNode(name1) - verticesList.begin();

		// Scan through all of the edges to find the children of the first node.
		for (size_t i = fromNodeIndex; i < verticesList.size(); i++) {

			// Scan through the list of vertices to find all possible edge connections.
			for (size_t k = 1; k < edgeAdjacencyMatrix[i].size(); k++) {
				// Scan in the nodes to be processed in the queue.
				if (edgeAdjacencyMatrix[i][k] == 1) {
					BFSQueue.push(verticesList[k]);

					// Build the path via the edges provided between the two nodes.
					previousPath[k] = i;
				}
			}

			// Process the queue.
			while (!BFSQueue.empty()) {
				char currentChar = BFSQueue.front();
				BFSQueue.pop();
				Processed.push_back(currentChar);
				if (currentChar == name2) {
					vector<char> path;

					int j = SearchNode(name2) - verticesList.begin();

					while (j != -1) {
						path.push_back(verticesList[j]);
						j = previousPath[j];
					}

					reverse(path.begin(), path.end());
					return path.size() - 1;
				}
			}
		}
	}
	else {

		// Initialize the visited vector
		for (size_t i = 0; i < verticesList.size(); i++) {
			hasBeenVisited.push_back(false);
		}

		// Initialize the start of the stack.
		int fromNodeIndex = SearchNode(name1) - verticesList.begin();
		DFSStack.push(name1);
		hasBeenVisited[fromNodeIndex] = true;

		// Continue processing the stack and the processed vector until the path is found.
		while (!DFSStack.empty()) {
			char currChar = DFSStack.top();

			// If we found the node, we have finished our path journey.
			if (currChar == name2)
				return Processed.size();
			else {
				DFSStack.pop();
				Processed.push_back(currChar);
			}

			for (size_t k = 1; k < edgeAdjacencyMatrix[fromNodeIndex].size(); k++) {
				if (edgeAdjacencyMatrix[fromNodeIndex][k] == 1 && !hasBeenVisited[k]) {
					hasBeenVisited[k] = true;
					DFSStack.push(verticesList[k]);
				}
			}
		}
		return Processed.size();
	}
	return 1; // If the char destination doesn't exist for whatever reason, then it can only traverse one edge length.
}

// Prints the list of vertices in the order they were added.
void Graph::PrintVertexList() {
	if (verticesList.empty())
		cout << "No vertices";
	else {
		string vertexList = "";
		for (size_t i = 0; i < verticesList.size(); i++) {
			if (vertexList == "") {
				vertexList = verticesList[i];
			}
			else {
				vertexList += " ";
				vertexList += verticesList[i];
			}
		}
		cout << vertexList;
	}
}
// Prints the list of edges in the order they were added.
void Graph::PrintEdgeList() {
	if (edgeList.empty())
		cout << "No edges";
	for (size_t i = 0; i < edgeList.size(); i++) {
		cout << "[ " << edgeList.at(i) << " ]\n";
	}
}

// Adds a vertex with the specified name to the graph.
void Graph::AddVertex(char name) {
	// Is the node already there?
	if (find(verticesList.begin(), verticesList.end(), name) == verticesList.end()) {
		verticesList.push_back(name);

		resizeMatrix(verticesList.size());
	}
}

// Removes the vertex with the specified name from the graph.
void Graph::RemoveVertex(char name) {
	// Iterator "it" will find the vertice within the list. If it defines it as the end of the list, then it doesn't exist.

	auto it = SearchNode(name);

	if (it != verticesList.end()) {

		// Locate the integer index.
		int index = it - verticesList.begin(); // Overloading to convert to an numerical index.

		// We're sending the vertex index. (In our example, it's b, which is 2).
		RemoveEdge(index, name);

		// Removing the column of the row.
		for (auto& column : edgeAdjacencyMatrix) {
			column.erase(column.begin() + index);
		}

		// Remove the entire row that consists of the edge (The first vector)
		edgeAdjacencyMatrix.erase(edgeAdjacencyMatrix.begin() + index);

		// Remove it from the vertice list.
		verticesList.erase(it);

	}
}

// Remove the edges.
void Graph::RemoveEdge(int index, char name) {
	for (int i = 0; i < edgeAdjacencyMatrix[index].size(); i++) {
		if (edgeAdjacencyMatrix[index][i] == 1 || edgeAdjacencyMatrix[i][index]) {
			auto itE = SearchEdge(string(1, name), string(1, verticesList[i]));

			// If it does exist remove it from the edgeList vector. First option.
			if (itE != edgeList.end()) {

				int indexItE = itE - edgeList.begin();
				edgeList.erase(edgeList.begin() + indexItE);
				edgeAdjacencyMatrix[index][i] = 0;
			}

			// This has to be positioned here because edgeList would be updated after erasing one object.
			auto itETwo = SearchEdge(string(1, verticesList[i]), string(1, name));

			// Couldn't find it. Reversing it to find the second option.
			if (itETwo != edgeList.end()) {
				int indexItE = itETwo - edgeList.begin();
				edgeList.erase(edgeList.begin() + indexItE);
			}
		}
		if (!isItdirected && edgeAdjacencyMatrix[i][index] == 1) {
			if (edgeAdjacencyMatrix[i][index] == 1 && !isItdirected) {
				edgeAdjacencyMatrix[i][index] = 0;
			}
		}
	}
}

// Adds an edge between the two vertices to the graph.
void Graph::AddEdge(char name1, char name2) {
	auto toNodeIt = SearchNode(name2);
	auto fromNodeIt = SearchNode(name1);

	int fromNodeIndex = SearchNode(name1) - verticesList.begin();
	int toNodeIndex = SearchNode(name2) - verticesList.begin();

	// If the node doesn't exist on the graph, add it.
	if ((toNodeIt != verticesList.end() && fromNodeIt != verticesList.end())) {
		// If the edge doesn't exist proceed.
		if ((isItdirected && (edgeAdjacencyMatrix[fromNodeIndex][toNodeIndex] != 1)) || (!isItdirected && (edgeAdjacencyMatrix[fromNodeIndex][toNodeIndex] != 1) && (edgeAdjacencyMatrix[toNodeIndex][fromNodeIndex] != 1))) {
			string edgeName = string(1, name1) + " " + string(1, name2);

			// Overloading the values to get the index. This is because the iterators (Similiar to pointers but more abstract) are subtracted and result in the distance between the two iterators.
			int fromNodeIndex = SearchNode(name1) - verticesList.begin();
			int toNodeIndex = SearchNode(name2) - verticesList.begin();

			edgeAdjacencyMatrix[fromNodeIndex][toNodeIndex] = 1;

			//cout << "Adding: " << edgeName << " To the edgeList\n";

			edgeList.push_back(edgeName);

			// If it's undirected connect it in the matrix.
			if (!isItdirected) {
				edgeAdjacencyMatrix[toNodeIndex][fromNodeIndex] = 1;
			}

		}
	}
	else if (toNodeIt == verticesList.end() && fromNodeIt == verticesList.end()) {
		cout << "No vertices";
	}
	//else {
	//	cout << "No edges";
	//}
}
void Graph::resizeMatrix(size_t newSize) {

	// Create a template of the old matrix.
	vector<vector<int>> oldMatrix = edgeAdjacencyMatrix;

	// Every size in the matrix row will be newSize, and then each vector column will also be new size set to 0.
	edgeAdjacencyMatrix = vector<vector<int>>(newSize, vector<int>(newSize, 0));

	// Resizing the matrix.
	for (size_t row = 0; row < min(newSize, oldMatrix.size()); row++) {
		for (size_t column = 0; column < min(newSize, oldMatrix.size()); column++) {
			edgeAdjacencyMatrix[row][column] = oldMatrix[row][column];
		}
	}
}

vector<char>::iterator Graph::SearchNode(char name) {
	return find(verticesList.begin(), verticesList.end(), name);
}

vector<string>::iterator Graph::SearchEdge(string name1, string name2) {
	//cout << "Searching for: " << name1 << " " << name2 << endl;
	return find(edgeList.begin(), edgeList.end(), name1 + " " + name2);
}