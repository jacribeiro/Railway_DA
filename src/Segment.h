#ifndef RAILWAY_SEGMENT_DA_H
#define RAILWAY_SEGMENT_DA_H

#include "Station.h"
#include <string>
using namespace std;

class Segment {
    Station* stationA;
    Station* stationB;
    double capacity;
    double flow;
    string type;
    int price;

public:
    Segment(Station* a, Station* b, double c, string t);
    ~Segment();

    Station* getA();
    Station* getB();
    double getCap();
    double getFlow();
    string getType();
    int getPrice();

    void setA(Station *a);
    void setB(Station *b);
    void setCap(double c);
    void setFlow(double f);
    void setType(string t);
    void setPrice(int p);
};

#endif
