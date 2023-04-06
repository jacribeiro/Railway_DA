#include "Graph.h"

Graph::Graph() = default;

Station* Graph::getStation(std::string name) {
    for (auto s: StationSet) {
        if (s->getName() == name) {
            return s;
        }
    }
    return nullptr;
}

vector<Station*> Graph::getStationSet() {
    return this->StationSet;
}

vector<Segment*> Graph::getSegmentSet() {
    return this->SegmentSet;
}