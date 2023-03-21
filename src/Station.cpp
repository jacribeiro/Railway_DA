//
// Created by Joao Ribeiro on 21/03/2023.
//

#include "Station.h"

Station::Station(string n, string d, string m, string t, string l):
    name(n), district(d), municipality(m), township(t), line(l) {};

Station::Station(Station& s) {
    this->name = s.name;
    this->district = s.district;
    this->municipality = s.municipality;
    this->township = s.township;
    this->line = s.line;
}

string Station::getName() {
    return this->name;
}

string Station::getDistrict() {
    return this->district;
}

string Station::getMunicipality() {
    return this->municipality;
}

string Station::getTownship() {
    return this->township;
}

string Station::getLine() {
    return this->line;
}