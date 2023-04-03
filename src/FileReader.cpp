#include <iostream>
#include <fstream>
#include <sstream>
#include "FileReader.h"

int FileReader::readStationsFile(const std::string &fname, vector<Station *> &stations) {
    ifstream file(fname);
    if (file.is_open()) {
        // Read the first line and discard
        string row;
        getline(file, row);
        string name, district, municipality, township, line;
        while (getline(file, line)) {
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
        cerr << "Could not open airlines file" << endl;
    }
}