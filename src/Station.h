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

    Segment* previous = NULL; //segmento que precede a estação (usado em bfs e assim, pode ser nullptr)
    int ID; //id da estação, mais fácil do que usar o nome
    vector<Segment *> adj; //segmentos adjacentes
    bool visited = false;
    bool is_in_g; //indica se esta estação está no grafo fornecido às funções, deve ser inicializado a true quando g é criado
    int arrive;

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

    void setName(string n);
    void setDistrict(string d);
    void setMunicipality(string m);
    void setTownship(string t);
    void setLine(string l);

    Segment* getPrevious();
    int getID();
    void setPrevious(Segment* s);
    vector<Segment *> getAdj();
    bool getVisited();
    void setVisited(bool b);
    bool getIs();
    void setIs(bool b);
    void addSegment(Segment* destination);
    bool operator==(const Station& s1) const;
    int getArrive();
    void setArrive(int a);
};




#endif //RAILWAY_DA_STATION_H
