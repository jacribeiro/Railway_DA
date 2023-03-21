//
// Created by Joao Ribeiro on 21/03/2023.
//

#ifndef RAILWAY_DA_STATION_H
#define RAILWAY_DA_STATION_H

#include <string>

using namespace std;

class Station {
    string name;
    string district;
    string municipality;
    string township;
    string line;

public:
    Station(string n, string d, string m, string t, string l);
    Station(Station& s);

    string getName();
    string getDistrict();
    string getMunicipality();
    string getTownship();
    string getLine();


};




#endif //RAILWAY_DA_STATION_H
