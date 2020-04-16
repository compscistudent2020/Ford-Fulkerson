/*
 * FlowNetwork.cpp
 *
 * Last Modified: March 25, 2020
 * Author: Dr. Barbara Anthony
 */
#include <iostream>
#include <algorithm>

#include "FlowNetwork.h"

FlowNetwork::FlowNetwork()
{
    source = -1;
    sink = -1;
}

int FlowNetwork::getCapacity(int fromNode, int toNode)
{
    map<pair<int,int>,int>::iterator mapIterator =
            edgeCapacity.find(pair<int,int>(fromNode,toNode));
    if (mapIterator != edgeCapacity.end())
        return mapIterator->second;
    return 0;
}

void FlowNetwork::setCapacity(int fromNode, int toNode, int capacity)
{
    if (capacity != 0)
    {
        // add the edge and store its capacity
        directedEdges[fromNode].insert(toNode);
        edgeCapacity[pair<int,int>(fromNode,toNode)] = capacity;
    }
    else
    {
        // if capacity is 0, remove the edge and all associated data
        set<int>::iterator setIterator =
                directedEdges[fromNode].find(toNode);
        if (setIterator != directedEdges[fromNode].end())
            directedEdges[fromNode].erase(setIterator);
        map<pair<int,int>,int>::iterator mapIterator =
                edgeCapacity.find(pair<int,int>(fromNode,toNode));
        if (mapIterator != edgeCapacity.end())
            edgeCapacity.erase(mapIterator);
    }
}

const set<int> & FlowNetwork::getNeighbors(int node)
{
    if (directedEdges.find(node) != directedEdges.end())
        return directedEdges[node];
    return emptySet;
}

void FlowNetwork::print()
{
    cout << "-- Source = " << source << endl;
    cout << "-- Edges In Flow Network --" << endl;
    for (map<int,set<int> >::iterator mIt = directedEdges.begin();
            mIt != directedEdges.end(); ++mIt)
    {
        for (set<int>::iterator sIt = mIt->second.begin();
             sIt != mIt->second.end(); ++sIt)
            cout << "     " << mIt->first << "->" << *sIt
                 << " has capacity " << getCapacity(mIt->first, *sIt)
                 << endl;
    }
    cout << "-- Sink = " << sink << endl;
}

void FlowNetwork::printPath(vector<int> & path)
{
    cout << "Path: ";
    for (unsigned i=0; i<path.size()-1; i++)
        cout << path[i] << "--("
             << getCapacity(path[i], path[i+1])
             << ")-->";
    cout << path[path.size()-1];
    cout << endl;
}
