#ifndef RAILWAY_GRAPH_H
#define RAILWAY_GRAPH_H 

#include "Station.h"
#include "Segment.h"
#include <vector>

using namespace std;

class Graph {
    vector<Station*> StationSet;
    vector<Segment*> SegmentSet;
    
public:
    Graph();

    vector<Station*> getStationSet();
    vector<Segment*> getSegmentSet();

    /**
     * Returns a pointer to a Station within the graph
     * @param name Name of the station to be searched
     * @return Pointer to the station in case of success, nullptr otherwise
     */
    Station* getStation(string name);

};

#endif
