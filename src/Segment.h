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
    bool visited = false; //importa para o maxCostStations e bfs etc etc

public:
    Segment(Station* a, Station* b, double c, string t);
    ~Segment();

    Station* getA();
    Station* getB();
    double getCap();
    double getFlow();
    string getType();
    int getPrice();
    bool getVisited();

    void setA(Station *a);
    void setB(Station *b);
    void setCap(double c);
    void setFlow(double f);
    void setType(string t);
    void setPrice(int p);
    void setVisited(bool v);
};

#endif
