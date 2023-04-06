#include <iostream>
#include <fstream>
#include <sstream>

#include "FileReader.h"
#include "Segment.h"
#include "Station.h"

FileReader::FileReader() = default;

int FileReader::readStationsFile(const std::string &fname, Graph& g) {
    ifstream file(fname);
    if (file.is_open()) {
        // Read the first line and discard
        string row;
        getline(file, row);
        string name, district, municipality, township, line;
        while (getline(file, row)) {
            stringstream input(row);
            getline(input, name, ',');
            getline(input, district, ',');
            getline(input, municipality, ',');
            getline(input, township, ',');
            getline(input, line, ',');
            Station *s = new Station(name, district, municipality, township, line);
            g.getStationSet().push_back(s);
        }
        return 0;
    } else {
        cerr << "Could not open stations file" << endl;
        return 1;
    }
}

int FileReader::readNetworkFile(const std::string &fname, Graph &g) {
    ifstream file(fname);
    if (file.is_open()) {
        // Read the first line and discard
        string row;
        getline(file, row);
        string stationA, stationB, capacity, type;
        while (getline(file, row)) {
            stringstream input(row);
            getline(input, stationA, ',');
            getline(input, stationB, ',');
            getline(input, capacity, ',');
            getline(input, type, ',');

            Station *stA = g.getStation(stationA);
            Station *stB = g.getStation(stationB);
            Segment *s1 = new Segment(stA, stB, stod(capacity), type);
            if (type == "STANDARD\r") {
                s1->setPrice(2);
            } else {
                s1->setPrice(4);
            }
            g.getSegmentSet().push_back(s1);
            stA->addSegment(s1);
            stB->addSegment(s1);

        }
        return 0;
    } else {
        cerr << "Could not open network file" << endl;
        return 1;
    }
}