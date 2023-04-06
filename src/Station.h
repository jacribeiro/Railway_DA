#ifndef RAILWAY_DA_STATION_H
#define RAILWAY_DA_STATION_H

#include <string>
#include <vector>
#include "Segment.h"

using namespace std;

class Station {
    string name; 
    string district; 
    string municipality;
    string township;
    string line;

    Segment* previous = NULL; //preceding Segment, for use in pathfinding algorithms
    int ID;
    vector<Segment *> adj; //adjacent Segments
    bool visited = false;
    bool is_in_g; //indicates if this Station is reached on report_losses

//protected:
//    static int nextID = 0;

public:

    Station(string n, string d, string m, string t, string l);
    Station(Station& s);

    string getName();
    string getDistrict();
    string getMunicipality();
    string getTownship();
    string getLine();
    Segment* getPrevious();
    int getID();
    vector<Segment *> getAdj();
    bool getVisited();
    bool getIs();

    void setName(string n);
    void setDistrict(string d);
    void setMunicipality(string m);
    void setTownship(string t);
    void setLine(string l);
    void setPrevious(Segment* s);
    void setVisited(bool b);
    void setIs(bool b);

    void addSegment(Segment* destination);
    bool operator==(const Station& s1) const;
};




#endif //RAILWAY_DA_STATION_H
