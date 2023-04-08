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
    /**
     * Default constructor for the class Graph
     */
    Graph();

    /**
     * Returns the vector of stations in the network
     * @return Vector of stations in the network
     */
    vector<Station*>& getStationSet();

    /**
     * Returns the vector of segments in the network
     * @return Vector of segments in the network
     */
    vector<Segment*>& getSegmentSet();

    /**
     * Returns a pointer to a Station within the graph
     * @param name Name of the station to be searched
     * @return Pointer to the station in case of success, nullptr otherwise
     */
    Station* getStation(string name);

    /**
     * Deletes all allocated objects in SegmentSet
     */
    void clearSegments();

    /**
     * Deletes all allocated objects in StationSet
     */
    void clearStations();

};

#endif
