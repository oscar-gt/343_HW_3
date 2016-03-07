/*
 * graphm.cpp
 *
 *  Created on: Jan 29, 2016
 *      Author: Oscar Garcia-Telles
 */

#include "graphm.h"
#include<fstream>
#include<iostream>
using namespace std;

// Implementation of graphm.h

// ----------------   No argument constructor -----------------

// Populates member data structures
GraphM::GraphM()
{
	initData(data, MAXNODES);			// Initializing string array
	initAdjacencyMatrix(C, MAXNODES);	// Initializing adjacency matrix
	size = 0;							// Number of nodes
	initTableType(T, MAXNODES);			// Initializing path info matrix
}

// -------------- initData(NodeData [], size) Helper Function -----------

// Initializes a GraphM's data[] array.
void GraphM::initData(NodeData dat[], int arraySize)
{
	NodeData nd; // Initializes to ""
	for(int i = 0; i < arraySize; i++)
	{
		dat[i] = nd;
	}
}

// ------ initAdjacencyMatrix(C[][], maxnodes) Helper Function -------

// Initializes a GraphM's adjacency matrix
void GraphM::initAdjacencyMatrix(int matrix[][MAXNODES], int nodes)
{
	for(int i = 1; i < nodes; i++)
	{
		for(int k = 1; k <= nodes; k++)
		{
			// Setting all values to INF first.
			matrix[i][k] = INF;
		}
	}
}

// ---------- initTableType(TableType T, nodes) Helper Function ---------

// Initizlizes the TableType[][] array
void GraphM::initTableType(TableType t[][MAXNODES], int nodes)
{
	// Traversing row
	for(int i = 1; i < nodes; i++)
		{	// Traversing column
			for(int k = 1; k < nodes; k++)
			{
				// Everything will not be visited at first,
				// and all distances will be infinity
				t[i][k].visited = false;
				t[i][k].dist = INF;
				t[i][k].path = 0;
			}
		}
}

//------------------------ buildGraph(file) Function ----------------

// Populating member data structures with actual data.
// ASSUMPTION: the file that we're reading data from
// will have the data correctly formatted. We will
// not check input.
void GraphM::buildGraph(ifstream &file1)
{
	// Initializing node/edge data
	int node1 = 0;
	int node2 = 0;
	int weight = 0;

	string location = "";

	// First retrieving the number of nodes
	file1 >> size;
	getline(file1, location); // Needed to consume the EOL char

	// Will now retrieve location strings
	for(int i = 1; i <= size; i++)
	{
		getline(file1, location);
		data[i] = location;
	}
	// Will now retrieve node and weight info.
	// Data is assumed to be provided as
	// node1 node2 weight. When a line of
	// 0 0 0 is reached, we will stop.
	for(;;)
	{
		file1 >> node1 >> node2 >> weight;
		// Checking if we've read all of this
		// current graph's node/edge info.
		if(node1 == 0)
		{
			break;
		}
		// Inserting edge
		(*this).insertEdge(node1, node2, weight);
	}
	// At this point, data[] and C[][] have the necessary info in them.
}

//---------------------- findShortestPath() Function ----------------

// Shortest path from all sources
// to all destination nodes using
// Dijkstra's algorithm
void GraphM::findShortestPath()
{
	int v = 0; // Node that has not been visited w/ the
			   // shortest distance so far.
	// Using Dijkstra's algorithm
	for(int source = 1; source <= size; source ++)
	{
		T[source][source].dist = 0; // Distance from node to itself..
		// We'll now find the shortest distance from source to
		// all other nodes.
		for(int i = 1; i <= size; i++)
		{
			// Finding v, the node with the shortest distance
			// so far that has not been visited.
			// findV() checks if it's been visited or not.
			v = findV(T, source);

			// v == 0 is an indicator that there are no more
			// vertices to process.
			if(v == 0)
			{
				break;
			}

			// Node with shortest dist will be visited
			T[source][v].visited = true;
			// Now iterating through nodes adjacent to T[source][v]
			for(int w = 1; w <= size; w++)
			{

				// Making sure that w has not been visited, and
				// that the edge actually exists.
				if( (T[source][w].visited == false) && (C[v][w] != INF) )
				{
					// Current min distance in T[][]
					int currDist = T[source][w].dist;
					// Dist of new path
					int pathDist = T[source][v].dist + C[v][w];

					// ----  Comparing distances ----
					if(currDist < pathDist)
					{
						T[source][w].dist = currDist;
					}
					else if(pathDist < currDist)
					{
						T[source][w].dist = pathDist;
						// We went through v to get to w.
						T[source][w].path = v;
					}
					// If distances are equal, we'll keep the distance from
					// the smaller node.
					else
					{
						T[source][w].path = T[source][w].path > v ? v:T[source][w].path;
					}

				}  // end of if block.
			} // end of w loop
		} // end of i loop
	} // end of source loop
}

// ------------------- findV() Helper Function for findShortestPath ------------

// Finds the index of the node with the shortest distance
// so far that has not been visited yet.
int GraphM::findV(TableType t[][MAXNODES], int source)
{
	int minV = INF;// Initializing to largest possible value
	int index = 0; // This will be returned in the end
	for(int i = 1; i <= size; i++)
	{
		int dist = t[source][i].dist;
		bool visit = t[source][i].visited;
		// Checking that vertex has not been visited
		// and that the distance is the smallest
		if( (visit == false) && (dist < minV) )
		{
			minV = dist;
			index = i;
		}
	}
	// If all the nodes have been visited, or
	// if the edge doesn't exist (all values
	// are INF), then the original 0 is
	// returned. This acts as a flag in
	// findShortestPath().
	return index;
}


//-------------------------- displayAll() Function ---------------------

// Displays all paths and associated info
void GraphM::displayAll()
{
	// initializing array to hold path info
	int pathInfo[size];
	// If there's no path, nothing will be displayed
	bool displayPath = true;
	cout << "Description              From node To node Dijkstra's   Path" << endl;
	// Source node
	for(int src = 1; src <= size; src ++)
	{
		// Displaying location name.
		cout << data[src] << endl;

		// Destination node
		for(int dst = 1; dst <= size; dst++)
		{
			// We don't want to show a node going to itself,
			// so we skip it.
			if(dst == src)
			{
				dst++;
			}
			// Making sure we don't travel to non-existing nodes
			if(dst > size)
			{
				break;
			}
			// Displaying source node and shortest distance.
			cout << "                              ";
			cout.setf(ios::left);
			cout.width(7);
			cout << src;
			cout.width(7);
			cout << dst;
			cout.width(12);
			if(T[src][dst].dist == INF)
			{
				displayPath = false;
				cout << "---";
			}
			else
			{
				displayPath = true;
				cout << T[src][dst].dist;
			}


			// --- Displaying path info ----
			// Well first collect the path data in an
			// array in reverse order. Then it'll be
			// displayed in the correct order

			int tempDst = dst;
			// The first element is the destination.
			pathInfo[0] = dst;
			int count = 1;

			// Storing path info starting with destination.
			// Array elements are the reverse path. So the
			// last element input will be the source node.

			int currPath = 0; // Initializing current path info
			for(int i = 1; i < size; i++)
			{
				currPath = T[src][tempDst].path;
				// Seeing if we're at the beginning of
				// the path
				if(currPath == src)
				{
					pathInfo[i] = src;
					break; // Done collecting path info
				}
				// else if we're still backtracking..
				pathInfo[i] = currPath;
				count++;
				tempDst = currPath;
			}

			// Now actually displaying the path
			for(int k = count; (k >= 0) && displayPath; k--)
			{
				cout.setf(ios::left);
				cout.width(3);
				cout << pathInfo[k];
			}
			cout << endl;
		} // end of destination loop
		cout << endl;
	}
	cout << endl;
	cout << endl;
}

//----------------------- display(node1, node2) Function ----------------

// Displays path between 2 nodes
void GraphM::display(int src, int dst)
{
	// Checking of nodes are out of bounds
	if( (src > size) || (dst > size))
	{
		cout << "    ";
		cout.setf(ios::left);
		cout.width(5);
		cout << src;
		cout.width(5);
		cout << dst;
		cout << "---" << endl;
	}
	// If nodes are 0 or negative..
	else if( (src < 1) || (dst < 1) )
	{
		// Do nothing for negatives
	}
	// Source to source..
	else if(src == dst)
	{
		cout << "    ";
		cout.setf(ios::left);
		cout.width(9);
		cout << src;
		cout.width(9);
		cout << src;
		cout.width(9);
		cout << 0 << endl;
		cout << data[src];
		cout << endl;
	}
	// If there's no edge between nodes..
	else if(T[src][dst].dist == INF)
	{
		cout << "    ";
		cout.setf(ios::left);
		cout.width(9);
		cout << src;
		cout.width(9);
		cout << dst;
		cout << "---" << endl;
		//cout << data[src] << endl;;
	}
	else
	{
		cout << "    ";
		cout.setf(ios::left);
		cout.width(9);
		cout << src;
		cout.width(9);
		cout << dst;
		cout.width(9);
		cout << T[src][dst].dist;
		cout << "       ";

		// initializing array to hold path info
		int pathInfo[size];

		// Displaying path info
		int tempDst = dst;
		// The first element is the destination.
		pathInfo[0] = dst;
		int count = 1;
		// Storing path info starting with destination.
		// Array elements are the reverse path. So the
		// last element input will be the source node.
		for(int i = 1; i < size; i++)
		{
			int currPath = T[src][tempDst].path;
			// Seeing if we're at the beginning of
			// the path
			if(currPath == src)
			{
				pathInfo[i] = src;
				break;
			}
			pathInfo[i] = currPath;
			count++;
			tempDst = currPath;
		}

		// Now actually displaying the path
		for(int k = count; k >= 0; k--)
		{
			cout.setf(ios::left);
			cout.width(3);
			cout << pathInfo[k];
			//cout << endl;
		}
		cout << endl;
		// Location path
		for(int m = count; m >= 0; m--)
		{
			int currentLoc = pathInfo[m];
			cout <<  data[currentLoc] << endl;
			cout << endl;
		}
	}
	cout << endl;
}

//---------------- insertEdge(node1, node2, weight) Function -------------

// Inserting edge to graph, which means that the
// adjacency matrix
void GraphM::insertEdge(int node1, int node2, int weight)
{
	// We will check for he validity of the nodes.

	// Same node
	if(node1 == node2)
	{
		return;
	}
	// Next 2 else ifs check if out of bounds.
	// I made separate ifs to not have one long
	// if
	else if( (node1 > size) || (node2 > size))
	{
		return;
	}
	else if((node1 < 1) || (node2 < 1))
	{
		return;
	}

	C[node1][node2] = weight;

}

//-------------------- removeEdge(node1, node2) Function ------------------

// Removing edge from graph
void GraphM::removeEdge(int node1, int node2)
{
	// Making sure we don't change a weight
	// of zero to infinity.
	if(node1 == node2)
	{
		return;
	}
	// Next 2 else ifs check if out of bounds
	else if( (node1 > size) || (node2 > size))
	{
		return;
	}
	else if((node1 < 1) || (node2 < 1))
	{
		return;
	}
	// If the edge doesn't exist, then the value is
	// already INF. Otherwise, it's changed in INF.
	C[node1][node2] = INF;
}



