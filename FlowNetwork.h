/*
 * FlowNetwork.h
 *
 *  Last Modified: March 25, 2020
 *  Author: Dr. Barbara Anthony
 */

#ifndef FLOWNETWORK_H_
#define FLOWNETWORK_H_

#include <set>
#include <map>
#include <string>
#include <vector>

using namespace std;

/*
 * This class provides the data structure for a basic flow
 * network: a weighted directed graph with labeled source
 * and sink nodes.
 *
 * Sufficient functionality needed for solving the network
 * flow problem is included this class through public accessor
 * functions. This includes the ability to add and remove edges
 * edges in the graph and set capacities. The network also
 * stores the source and sink nodes. Methods for printing the
 * network are provided to help in debugging.
 *
 * The graph is stored by keeping a set of neighboring nodes
 * for each node in the graph, i.e. if the graph contains
 * edge A->B, then vertex B is saved in the set of neighbors
 * associated with A. So for a given vertex, we have efficient
 * access to the forward pointing neighbors.
 *
 * For storing sets of integers, this class uses the set class in
 * the C++ standard template library. The set class is not an array
 * (or stl vector) so indexed access (i.e. myobject[i]) is not
 * available. It is an ordered container and can be traversed with
 * iterators in a very similar fashion to the stl vector. For more
 * information on using the set class, see:
 *
 * http://www.cplusplus.com/reference/set/set/
 *
 * Edge capacities are stored by mapping pairs of nodes associated
 * with an edge to the capacity. (Note: in c++ std::pair is an
 * ordered object so we can store weights for A->B and B->A.)
 *
 * For more information on using a map, see
 * http://www.cplusplus.com/reference/map/map/
 *
 * Zero capacity edges are NOT stored in the data structure. Rather,
 * zero capacity edges are just removed from the graph. If for some
 * reason, you need to differentiate between the case where a zero
 * capacity edge exists and the case that no edge exists, you will
 * need a more complex data structure. But you should not need that
 * for this network flow exercise.
 */

class FlowNetwork
{
public:
    FlowNetwork();
    ~FlowNetwork() {}

    int getSource() {return source;}
    void setSource(int newSource) {source = newSource;}
    int getSink() {return sink;}
    void setSink(int newSink) {sink = newSink;}

    int getCapacity(int fromNode, int toNode);
    // Note: the setCapacity will CREATE an edge if the capacity is non-zero
    //       and REMOVE an edge if the capacity is set to zero
    void setCapacity(int fromNode, int toNode, int capacity);

    // this function returns the set of nodes that can be
    // reached from the input node via an outbound edge
    const set<int> & getNeighbors(int node);

    // print info about the entire netowrk
    void print();
    // print info about a given path
    void printPath(vector<int> & path);

private:

    int source;
    int sink;
    map<int,set<int> > directedEdges;
    map<pair<int,int>,int> edgeCapacity;
    set<int> emptySet;
};


#endif
