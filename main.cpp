#include <iostream>

#include "src/FileReader.h"

using namespace std;

int main() {
    FileReader reader = FileReader();
    Graph g = Graph();
    reader.readStationsFile("../data/stations.csv", g);
    reader.readNetworkFile("../data/network.csv", g);
    for (int i = 0; i < 10; i++) {
        cout << "Name of station: " << endl;
        cout << g.StationSet[i]->getName() << endl;
        cout << "Name of first of first destination: " << endl;
        vector<Segment *> v = g.StationSet[i]->getAdj();
        cout << v.at(0)->getB()->getName() << endl;
    }
    for (auto s: g.SegmentSet)
        delete s;
    for (auto s: g.StationSet)
        delete s;
    return 0;
}
