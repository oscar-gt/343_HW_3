/*
 * graphm.h
 *
 *  Created on: Jan 29, 2016
 *      Author: Oscar Garcia-Telles
 */

#ifndef GRAPHM_H_
#define GRAPHM_H_

// A GraphM object will be used to represent
// a network of nodes. It will be represented
// with an adjacency matrix containing the
// weights of the edges between nodes.
// Dijkstra's algorithm will be used to
// calculate the shortest distance between
// nodes. This data will be kept in a TableType
// struct.

// ASSUMPTIONS: throughout this implementation,
// we are assuming that the data files will contain
// correctly formatted data. We will not check for
// the validity of input, i.e., we won't make sure
// that integers are actually integers, or that we
// have the correct number of nodes.

// Please note that although the max number of nodes
// is 100, i will initialize the arrays to be of size
// 101 since we won't be using the 0 index in the arrays.

#include "nodedata.h"
#include<climits>
class GraphM
{

public:

	// Maximum nodes global constant. Actual nodes will
	// be (MAXNODES - 1) since we do not use the 0th index
	static const int MAXNODES = 101;
	// Global const for our representation
	// of infinity.
	static const int INF = INT_MAX;

	// Constructor
	GraphM();

	// Populating member data structures
	void buildGraph(ifstream &file1);
	// Shortest path from all sources
	//to all destination nodes
	void findShortestPath();
	// Displays all paths
	void displayAll();
	// Displays path between 2 nodes
	void display(int node1, int node2);
	// Inserting edge to graph
	void insertEdge(int node1, int node2, int weight);
	// Removing edge from graph
	void removeEdge(int node1, int node2);

private:
	struct TableType{
		bool visited;	// Node is visited or not
		int dist;		// Min dist from source so far
		int path;		// Previous node to reach current node
	};
	NodeData data[MAXNODES];	// Locations
	int C[MAXNODES][MAXNODES];	// Adj. matrix
	int size;					// # of nodes
	TableType T[MAXNODES][MAXNODES];	// Path info

	// Private functions

	// Initializers.
	void initData(NodeData dat[], int arraySize);
	void initAdjacencyMatrix(int matrix[][MAXNODES], int nodes);
	void initTableType(TableType t[][MAXNODES], int nodes);
	// Finding the unvisited vertex w/ the shortest
	// distance so far.
	int findV(TableType t[][MAXNODES], int source);
};

#endif /* GRAPHM_H_ */
