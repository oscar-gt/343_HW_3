/*
 * graphl.h
 *
 *  Created on: Feb 13, 2016
 *      Author: Oscar Garcia-Telles
 */

#ifndef GRAPHL_H_
#define GRAPHL_H_

#include "nodedata.h"

// A GraphL object will be used to represent
// a network of nodes. It will be represented
// with an adjacency list: an array where
// the index corresponds to the node #,
// and each node will then contain a
// linked list with adjacent node info.
// A depth first search will be implemented
// using the adjacency list.

// ASSUMPTIONS: throughout this implementation,
// we are assuming that the data files will contain
// correctly formatted data. We will not check for
// the validity of input, i.e., we won't make sure
// that integers are actually integers, or that we
// have the correct number of nodes.

// Please note that although the max number of nodes
// is 100, i will initialize the arrays to be of size
// 101 since we won't be using the 0 index in the arrays.

class GraphL
{
public:

	// Maximum nodes global constant. Please note
	// that the actual maximum is MAXNODES - 1
	// since we won't use the 0 index.
	static const int MAXNODES = 101;

	// Constructor
	GraphL();

	// Destructor
	~GraphL();

	// Populates adjacency list
	void buildGraph(ifstream &file1);

	void depthFirstSearch();

	void displayGraph();

private:
	struct EdgeNode;		// Forward reference to compiler
	struct GraphNode		// Node with linked list
	{
		EdgeNode *edgeHead;		// Head of the list of edges
		NodeData *data;			// Data info about each node
		bool visited;
	};

	struct EdgeNode
	{
		int adjGraphNode;		// Subscript of the adjacent graph node
		EdgeNode *nextEdge;		// Link to the next node
	};

	// Array of graph nodes. We'll simply create one
	// array with the max allowable nodes and track the
	// actual size of the array
	GraphNode gNodes[MAXNODES];
	int size; // Number of actual nodes

	// Utility functions

	// Helper for destructor
	void clearList(EdgeNode * &head);
	// inserting an edge
	void insertEdge(int node1, int node2);
	// helper for depthFirstSearch()
	void dfs(GraphNode gn[], EdgeNode *currentEdge, int currentIndex);
};

#endif /* GRAPHL_H_ */
