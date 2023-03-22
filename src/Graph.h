#ifndef RAILWAY_GRAPH_H
#define RAILWAY_GRAPH_H 

#include "Station.h"
#include "Segment.h"
#include <vector>

using namespace std;

class Graph {
    vector<Station*> StationSet;
public:
    Graph(/* args */);
    ~Graph();
};

#endif
