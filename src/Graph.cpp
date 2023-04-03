#include "Graph.h"

Station* Graph::getStation(std::string name) {
    for (auto s: StationSet) {
        if (s->getName() == name) {
            return s;
        }
    }
    return nullptr;
}