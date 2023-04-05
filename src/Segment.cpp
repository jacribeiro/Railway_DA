#include "Segment.h"

Segment::Segment(Station *a, Station *b, double c, string t):
    stationA(a), stationB(b), capacity(c), type(t) {};

Station* Segment::getA(){
    return this->stationA;
};

Station* Segment::getB(){
    return this->stationB;
};

double Segment::getCap(){
    return this->capacity;
};

double Segment::getFlow(){
    return this->flow;
};

string Segment::getType(){
    return this->type;
};

int Segment::getPrice(){
    return this->price;
}

void Segment::setA(Station *a) {
    this->stationA = a;
}

void Segment::setB(Station *b) {
    this->stationB = b;
}

void Segment::setCap(double c) {
    this->capacity = c;
}

void Segment::setFlow(double f) {
    this->flow = f;
}

void Segment::setType(string t) {
    this->type  = t;
}

void Segment::setPrice(int p) {
    this->price = p;
}

bool Segment::getVisited() {
    return this->visited;
}

void Segment::setVisited(bool v) {
    this->visited = v;
}