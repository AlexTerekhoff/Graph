//
//  graph.h
//  KURTKA
//
//  Created by Sergey Polischouck on 13/12/14.
//  Copyright (c) 2014 Alexander. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Node {
    
public:
    int index;
    int valence;
};

class Graph {
    uint numberOfNodes;
    uint numberOfEdges;
    uint indexForNodeWithMinValence;
    
    vector<vector<uint>> adjacencyList;
    
    vector<Node> nodes;
    vector<Node> candidates;
    
    bool theareIsEdgeBetweenNodes(uint index_1, uint index_2);
    uint countValenceForNodeWith(uint index);
    void searchIndexForNodeWithMinValenceAmongCandidates();
    bool isNodeWithIndexACandidate(uint index);
    void deleteCandidateWithIndex(uint index);
    void decrementValenceNodesForIndex(uint index);
    void removingAdjacentNodesForIndex(uint index);
    vector<uint> fetchAdjacentNodesForIndex(uint index);
    
public:
    void InitFromFileWithName(string name);
    void PrintAdjacencyList();
    vector<uint> GetMaxIndependentSet();
    bool isIndependentSet(vector<uint> set);
};

