/*
 * graphl.cpp
 *
 *  Created on: Feb 13, 2016
 *      Author: Oscar Garcia-Telles
 */

#include "graphl.h"
#include<fstream>
#include<iostream>
using namespace std;

// Implementation of graphl.h

// --------------------------- Constructor ---------------------------

// No arg constructor
GraphL::GraphL()
{
	// Each element is a GraphNode. Each GraphNode has the following

	// *edgeHead		EdgeNode Struct
	// *data			NodeData struct
	// visited			bool

	// EdgeNodes have
	// adjGraphNode		int that's the subscript
	// *nextEdge		EdgeNode struct. Link to next

	// MAXNODES is 101 in this case.
	// Not using 0 index
	for(int i = 1; i < MAXNODES; i++)
	{
		gNodes[i].edgeHead = NULL;
		gNodes[i].data = NULL;
		gNodes[i].visited = false;
	}
	// No actual nodes at this time.
	size = 0;
}

// --------------------------- Destructor ---------------------------

GraphL::~GraphL()
{
	for(int i = 1; i < MAXNODES; i++)
	{
		GraphNode curr = gNodes[i]; // Current node to process
		clearList(curr.edgeHead);
		// Delete data pointer
		delete curr.data;
	}
}

// ------------------ clearList() Helper for Destructor ----------

// Recursively clearing a GraphNode's linked
// list
void GraphL::clearList(EdgeNode * &head)
{
	if(head == NULL)
	{
		// Nothing
	}
	else
	{
		clearList(head -> nextEdge);
		// Then delete the current node
		delete head;
		head = NULL;
	}
}

// ------------------- buildGraph() Function -----------------

// Populates a GraphL's adjacency list with edge info.
// ASSUMPTION: data files are assumed to be
// correctly formatted, so we won't check any
// input values.
void GraphL::buildGraph(ifstream &file1)
{
	// Initializing input variables
	int node1 = 0;
	int node2 = 0;
	string location = "";

	// First retrieving the number of nodes
	file1 >> size;
	// Getting rid of line
	getline(file1, location);

	// Setting locations in array.
	for(int i = 1; i <= size; i++)
	{
		NodeData *curr = new NodeData(""); // Initializing
		getline(file1, location);
		*curr = location;			// Overriding value
		gNodes[i].data = curr;
	}

	// Will now retrieve node information.
	// Data is assumed to be provided as
	// node1 node1 in each line. When a line
	// of 0 0 is reached, we will stop.
	for(;;)
	{
		file1 >> node1 >> node2;
		// Checking if we're done receiving node info
		// for the current graph
		if(node1 == 0)
		{
			break;
		}
		// Inserting edge info.
		(*this).insertEdge(node1, node2);
	}
}


// ------------------------ insertEdge() Function -------------------

// Inserts an edge at the front of a GraphNode's list.
void GraphL::insertEdge(int node1, int node2)
{
	if(gNodes[node1].edgeHead == NULL)
	{
		// Creating new edge if list is empty
		gNodes[node1].edgeHead = new EdgeNode;
		gNodes[node1].edgeHead -> adjGraphNode = node2;
		gNodes[node1].edgeHead -> nextEdge = NULL;
	}
	// When there are edges in the list already, will do the following
	else
	{
		EdgeNode *newEdge = new EdgeNode;	// Allocating
		newEdge -> adjGraphNode = node2;	// Setting value
		// Inserting in front
		newEdge->nextEdge = gNodes[node1].edgeHead;
		// Adjusting head
		gNodes[node1].edgeHead = newEdge;

	}
}

// ----------------------- depthFirstSearch() Function --------------

// Outputs the graph's depth first search traversal
void GraphL::depthFirstSearch()
{
	cout << "Depth-first ordering:  ";
	// Calling helper
	dfs(gNodes, gNodes[1].edgeHead, 1);
	cout << endl;
	cout << endl;
}

// -------------- dfs() Helper Function for depthFirstSearch()-------

void GraphL::dfs(GraphNode gn[], EdgeNode *currentEdge, int currentIndex)
{
	// Base case, when we're at the end of the list
	// or if the graph is empty
	if(gn[currentIndex].visited == true)
	{
		// do nothing :P
	}
	else
	{
		// First mark as visited
		gn[currentIndex].visited = true;
		cout.setf(ios::left);
		cout.width(3);
		cout << currentIndex;
		// Now traverse list of current GraphNode
		while( currentEdge != NULL)
		{
			int nextIndex = currentEdge -> adjGraphNode;
			dfs(gn, gn[nextIndex].edgeHead, nextIndex);
			currentEdge = currentEdge->nextEdge;

		}
	}

}

// ----------------- displayGraph() Function ----------------

void GraphL::displayGraph()
{
	cout << "Graph: " << endl;
	for(int node = 1; node <= size; node++)
	{
		GraphNode current = gNodes[node];
		cout << "Node ";
		cout.setf(ios::left);
		cout.width(12);
		cout << node;
		cout << *current.data << endl;
		cout << endl;

		EdgeNode *currEdge = current.edgeHead;
		while(currEdge != NULL)
		{
			cout << "  edge ";
			cout.setf(ios::left);
			cout.width(4);
			cout << node;
			cout.width(4);
			cout << currEdge -> adjGraphNode;
			currEdge = currEdge -> nextEdge;
			cout << endl;

		}
	} // End of for loop
	cout << endl;
}


