//
//  main.cpp
//  KURTKA
//
//  Created by Alexander on 13/12/14.
//  Copyright (c) 2014 Alexander. All rights reserved.
//

#include "graph.h"

int main(int argc, char* argv[])
{
    Graph graph;
    vector<uint> independentSet;
    string nameInputFile = "1dc_64.txt";
    string nameOutputFile = "output.txt";
    
    graph.InitFromFileWithName(nameInputFile);
    independentSet=graph.GetMaxIndependentSet();
    
    if (graph.isIndependentSet(independentSet))
    {
        ofstream outputFile(nameOutputFile);
        outputFile << independentSet.size() << "\n";
        
        for (uint i = 0; i < independentSet.size(); i++)
        {
            outputFile << independentSet[i] << "\n";
        }
    }
    
    return 0;
}