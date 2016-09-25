//
//  graph.cpp
//  KURTKA
//
//  Created by Sergey Polischouck on 13/12/14.
//  Copyright (c) 2014 Alexander. All rights reserved.
//

#include "graph.h"

void Graph::InitFromFileWithName(string name)
{
    ifstream file(name);
    if (!file) {
        cout << "Error opening file!" << endl;
        exit(1);
    }
    string word;
    file >> word >> word >> numberOfNodes >> numberOfEdges;
    
    for (uint i=1; i<=numberOfNodes; i++)
    {
        vector<uint> row;
        adjacencyList.push_back(row);
    }
    
    for (uint i=0; i<numberOfEdges; i++)
    {
        uint index, connectedToNode;
        file >> word >> index >> connectedToNode;
        adjacencyList[index-1].push_back(connectedToNode);
    }
    file.close();
    
    for (uint indexForNode = 1; indexForNode <= adjacencyList.size(); indexForNode++)
    {
        for (uint j = 0; j < adjacencyList[indexForNode-1].size(); j++)
        {
            uint indexAdjacentNode = adjacencyList[indexForNode-1][j];
            if (!theareIsEdgeBetweenNodes(indexAdjacentNode, indexForNode)) {
                adjacencyList[indexAdjacentNode-1].push_back(indexForNode);
            }
        }
    }
    
    for (uint index=1; index<=numberOfNodes; index++)
    {
        Node node;
        node.index=index;
        node.valence=countValenceForNodeWith(index);
        nodes.push_back(node);
    }
}

bool Graph::theareIsEdgeBetweenNodes(uint index_1, uint index_2)
{
    bool value=false;
    for (uint indexAdjecentNode = 1; indexAdjecentNode <= adjacencyList[index_1-1].size(); indexAdjecentNode++) {
        if (adjacencyList[index_1-1][indexAdjecentNode-1] == index_2) {
            value = true;
        }
    }
    return value;
}

void Graph::PrintAdjacencyList()
{
    for (uint indexForNode=1; indexForNode<=adjacencyList.size(); indexForNode++) {
        printf("%d: ", indexForNode);
        for (uint j=0; j<adjacencyList[indexForNode-1].size(); j++) {
            printf("%3.d ", adjacencyList[indexForNode-1][j]);
        }
        printf("\n");
    }
}



uint Graph::countValenceForNodeWith(uint index)
{
    uint valence=0;
    valence = (uint)adjacencyList[index-1].size();
    return valence;
}

void Graph::searchIndexForNodeWithMinValenceAmongCandidates()
{
    uint minValence=(uint)candidates.size()-1;
    indexForNodeWithMinValence = 0;
    
    for (uint index=0; index<candidates.size(); index++)
    {
        if (candidates[index].valence <= minValence)
        {
            minValence=candidates[index].valence;
            indexForNodeWithMinValence=candidates[index].index;
        }
    }
}


void Graph::deleteCandidateWithIndex (uint index)
{
    for (uint i=0; i<candidates.size(); i++)
    {
        if (candidates[i].index==index)
        {
            candidates.erase(candidates.begin()+i);
            break;
        }
    }
}

void Graph::decrementValenceNodesForIndex(uint index)
{
    for (uint i=0; i<candidates.size(); i++)
    {
        if (candidates[i].index==index)
        {
            candidates[i].valence--;
        }
    }
}

bool Graph::isNodeWithIndexACandidate(uint index)
{
    bool value=false;
    for (uint i=0; i<candidates.size(); i++)
    {
        if (candidates[i].index==index) {
            value=true;
        }
    }
    return value;
}

vector<uint> Graph::fetchAdjacentNodesForIndex(uint index)
{
    
    vector<uint> adjacentNodes;
    adjacentNodes = adjacencyList[index-1];
    return adjacentNodes;
}

void Graph::removingAdjacentNodesForIndex(uint index)
{
    vector<uint> adjacentNodesForIndex;
    vector<uint> childrenForAdjacentNodesForIndex;
    
    adjacentNodesForIndex=fetchAdjacentNodesForIndex(index);
    
    for (int i=0; i<adjacentNodesForIndex.size(); i++)
    {
        if (isNodeWithIndexACandidate(adjacentNodesForIndex[i])) {
            childrenForAdjacentNodesForIndex=fetchAdjacentNodesForIndex(adjacentNodesForIndex[i]);
            
            for (int j=0; j<childrenForAdjacentNodesForIndex.size(); j++)
            {
                decrementValenceNodesForIndex(childrenForAdjacentNodesForIndex[j]);
            }
        }
    }
    for (int i=0; i<adjacentNodesForIndex.size(); i++)
    {
        deleteCandidateWithIndex(adjacentNodesForIndex[i]);
    }
    
}


vector<uint> Graph::GetMaxIndependentSet()
{
    candidates=nodes;
    vector<uint> independentSet;
    
    while (candidates.size()!=0)
    {
        searchIndexForNodeWithMinValenceAmongCandidates();
        independentSet.push_back(indexForNodeWithMinValence);
        removingAdjacentNodesForIndex(indexForNodeWithMinValence);
        deleteCandidateWithIndex(indexForNodeWithMinValence);
        
    }
    return independentSet;
}

bool Graph::isIndependentSet(vector<uint> set)
{
    candidates=nodes;
    bool value = true;
    vector<uint> adjacentNodes;
    
    for (uint index = 1; index <= set.size(); index++) {
        adjacentNodes=fetchAdjacentNodesForIndex(set[index-1]);
        for (uint j = 0; j < adjacentNodes.size(); j++) {
            if (adjacentNodes[j] == set[index-1]) {
                value = false;
            }
        }
    }
    return value;
}














