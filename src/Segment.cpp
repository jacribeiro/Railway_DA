#include "Segment.h"

#include <utility>

Segment::Segment(Station *a, Station *b, int c, string t):
    stationA(a), stationB(b), capacity(c), type(std::move(t)), price(0), prev_capacity(c) {};

Station* Segment::getA(){
    return this->stationA;
};

Station* Segment::getB(){
    return this->stationB;
};

int Segment::getCap() const{
    return this->capacity;
};

int Segment::getFlow() const{
    return this->flow;
};

string Segment::getType(){
    return this->type;
};

int Segment::getPrice() const{
    return this->price;
}

void Segment::setA(Station *a) {
    this->stationA = a;
}

void Segment::setB(Station *b) {
    this->stationB = b;
}

void Segment::setCap(int c) {
    this->capacity = c;
}

void Segment::setFlow(int f) {
    this->flow = f;
}

void Segment::setType(string t) {
    this->type  = t;
}

void Segment::setPrice(int p) {
    this->price = p;
}

int Segment::getPrevCap() const {
    return this->prev_capacity;
}

void Segment::setPrevCap(int c) {
    this->prev_capacity = c;
}