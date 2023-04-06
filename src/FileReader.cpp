#include <iostream>
#include <fstream>
#include <sstream>
#include "FileReader.h"
#include "Segment.h"
#include "Station.h"

FileReader::FileReader() = default;

int FileReader::readStationsFile(const std::string &fname, vector<Station *> &stations) {
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
            Station s(name, district, municipality, township, line);
            Station* sp = &s; stations.push_back(sp);
        }
    } else {
        cerr << "Could not open stations file" << endl;
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
            auto stA = g.getStation(stationA);
            auto stB = g.getStation(stationB);
            Segment s1 = Segment(stA, stB, stoi(capacity), type);
            if (type == "STANDARD") {
                s1.setPrice(2);
            }
            else {
                s1.setPrice(4);
            }
            stA->addSegment(&s1);
            stB->addSegment(&s1);
        }
    } else {
        cerr << "Could not open network file" << endl;
    }
}