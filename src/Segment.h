#ifndef RAILWAY_SEGMENT_DA_H
#define RAILWAY_SEGMENT_DA_H

#include "Station.h"
#include <string>

using namespace std;

class Segment {
    Station* stationA;
    Station* stationB;
    int capacity;
    int prev_capacity;
    int flow = 0;
    string type;
    int price;
    bool visited = false; //importa para o maxCostStations e bfs etc etc

public:
    Segment(Station *a, Station *b, int c, string t);

    Station* getA();
    Station* getB();
    int getCap() const;
    int getFlow() const;
    string getType();
    int getPrice() const;
    bool getVisited() const;
    int getPrevCap() const;

    void setA(Station *a);
    void setB(Station *b);
    void setCap(int c);
    void setFlow(int f);
    void setType(string t);
    void setPrice(int p);
    void setVisited(bool v);
    void setPrevCap(int c);
};

#endif
