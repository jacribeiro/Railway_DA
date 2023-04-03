//
// Created by Joao Ribeiro on 21/03/2023.
//

#include "Station.h"

Station::Station(string n, string d, string m, string t, string l):
    name(n), district(d), municipality(m), township(t), line(l) {
    ID = ++nextID;
};

Station::Station(Station& s) {
    this->name = s.name;
    this->district = s.district;
    this->municipality = s.municipality;
    this->township = s.township;
    this->line = s.line;
    this->ID = s.ID;
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

Segment* Station::getPrevious() {
    return this->previous;
}

int Station::getID() {
    return this->ID;
}

void Station::setName(string s) {
    this->name = s;
}

void Station::setDistrict(string d) {
    this->district = d;
}

void Station::setMunicipality(string m) {
    this->municipality = m;
}

void Station::setTownship(string t) {
    this->township = t;
}

void Station::setLine(string l) {
    this->line = l;
}

void Station::setPrevious(Segment *s) {
    this->previous = s;
}

vector<Segment *> Station::getAdj() {
    return this->adj;
}

bool Station::getVisited() {
    return this->visited;
}
    
void Station::setVisited(bool b) {
    this->visited = b;
}

bool Station::getIs() {
    return this->is_in_g;
}

void Station::setIs(bool b) {
    this->is_in_g = b;
}

bool Station::operator==(const Station& s1) const {
    return this->ID == s1.ID;
}