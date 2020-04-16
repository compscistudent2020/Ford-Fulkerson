
#include <iostream>
#include <fstream>
#include <algorithm>

#include "FlowNetwork.h"

//
// Instructions: Implement the Ford-Fulkerson algorithm
// within the framework provided.
// Represent paths from the source to the sink as
// vectors of integers (representing node ids) so
// that you can use the printPath(...)
// function in the FlowNetwork class for debugging.


// this is a temporary struct for holding edges
// before adding them to the network
struct EdgeCapacity
{
	EdgeCapacity(int from, int to, int cap) :
		fromNode(from), toNode(to), capacity(cap) {}
	int fromNode;
	int toNode;
	int capacity;
};

bool operator<(const EdgeCapacity & lhs, const EdgeCapacity & rhs)
{
	if (lhs.capacity > rhs.capacity)
		return true;
	else if (lhs.capacity == rhs.capacity)
	{
		if (lhs.fromNode < rhs.fromNode)
			return true;
		else if (lhs.fromNode == rhs.fromNode)
		{
			if (lhs.toNode < rhs.toNode)
				return true;
		}
	}
	return false;
}

// read data from file into a list of sorted edges
// as well as a source and sink node
void readDataFromFile(string filename,
		vector<EdgeCapacity> & edges,
		int & source, int & sink)
{
	ifstream fin(filename.c_str());

	int numEdges;
	fin >> numEdges;

	for (int i=0; i<numEdges; i++)
	{
		int fromNode, toNode, capacity;
		fin >> fromNode >> toNode >> capacity;
		EdgeCapacity ec(fromNode, toNode, capacity);
		edges.push_back(ec);
	}
	fin >> source;
	fin >> sink;

	sort(edges.begin(), edges.end());
}

// Put data read from the file into the
// FlowNetwork class which gives more efficient
// access to edge capacities and node neighbors
void fillNetwork(FlowNetwork & network,
		vector<EdgeCapacity> & edges,
		int & source, int & sink)
{
	network.setSource(source);
	network.setSink(sink);
	for (unsigned i=0; i<edges.size(); i++)
	{
		network.setCapacity(edges[i].fromNode,
				edges[i].toNode,
				edges[i].capacity);
	}
}


// Standard depth first search implementation
// Recursively searches the network
// for a path from the currentNode to the sink
bool depthFirstSearch(int currentNode, int sink,
		FlowNetwork & network,
		vector<int> & path,
		set<int> visited)
{
	const set<int> & neighbors = network.getNeighbors(currentNode);
	for (set<int>::iterator it = neighbors.begin(); it != neighbors.end(); ++it)
	{
		int neighbor = *it;
		path.push_back(neighbor);

		if (neighbor == sink)
			return true;

		if (visited.find(neighbor) == visited.end())
		{
			visited.insert(neighbor);
			if (depthFirstSearch(neighbor, sink, network, path, visited))
				return true;
			visited.erase(neighbor);
		}
		path.pop_back();
	}
	return false;
}


// find a simple path from the source node to the
// sink node using a depth first search
bool findSimplePath(FlowNetwork & network,
		vector<int> & path)
{
	// TODO Update the 0s to appropriate values
	int source = 0;
	int sink =0;

	set<int> visited;

	// TODO Ensure that path is initialized appropriately
	path.push_back(source);

	return depthFirstSearch(source, sink, network, path, visited);
}


int getMaxFlowForPath(FlowNetwork & network,
		vector<int> & path)
{
	int minCapacity = -1;

	// TODO Fill in the body of this function
	// and provide an appropriate description in the comments

	return minCapacity;
}

void augmentNetwork(FlowNetwork & network,
		vector<int> & path,
		int flow)
{
	for (unsigned i=0; i<path.size()-1; i++)
	{
		int v0 = path[i];
		int v1 = path[i+1];

		// TODO Fill in the body of this function
		// Note the getCapacity and setCapacity functions
		// available for a FlowNetwork
		// Be sure to provide an appropriate description in the comments
	}
}


int fordFulkerson(FlowNetwork & network)
{
	int totalFlow = 0;
	int iterations = 0;

	// TODO Update this function.
	// It should run, but with incorrect answers now.
	// Change the condition for the while loop
	// and 0s below to correctly implement fordFulkerson.
	// The resulting code should provide sufficient information throughout
	// that the user can see what flow is being sent along which edges.

	vector<int> path;
	while (false) {
		int flow = 0;
		totalFlow += 0;

		network.printPath(path);
		cout << "Flow Pushed: " << flow << endl;

		augmentNetwork(network, path, flow);
		network.print();
		iterations++;
	}



	cout << "Finished Ford-Fulkerson" << endl;
	cout << "Max Flow For Network: " << totalFlow << endl;
	cout << "Iterations: " << iterations << endl << endl;

	return totalFlow;
}

// The main function only processes a single network at a time.
// If you wish to update it to handle all of the provided files, you may.
// Or you can manually test each by altering the file name in main.

int main()
{
	vector<EdgeCapacity> edges;
	int source;
	int sink;
	readDataFromFile("network.txt", edges, source, sink);

	FlowNetwork network;
	fillNetwork(network, edges, source, sink);

	fordFulkerson(network);

	return 0;
}


