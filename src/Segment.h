#ifndef RAILWAY_SEGMENT_DA_H
#define RAILWAY_SEGMENT_DA_H

#include <string>

using namespace std;

class Station;

class Segment {

    Station* stationA;
    Station* stationB;
    int capacity;
    int prev_capacity; //original capacity of the Segment, needed to restore the Segment if its capacity is altered
    int flow = 0;

    string type;
    int price;

public:

    Segment(Station *a, Station *b, int c, string t);

    Station* getA();
    Station* getB();
    int getCap() const;
    int getFlow() const;

    string getType();
    int getPrice() const;
    int getPrevCap() const;

    void setA(Station *a);
    void setB(Station *b);
    void setCap(int c);
    void setFlow(int f);
    void setType(string t);
    void setPrice(int p);
    void setPrevCap(int c);
};

#endif
