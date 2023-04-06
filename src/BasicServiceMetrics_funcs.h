#ifndef BSM_FUNCS_H
#define BSM_FUNCS_H

#include "Station.h"
#include "Segment.h"
#include "Graph.h"
#include <queue>
#include <utility>
#include <vector>

using namespace std;

struct mock_station {
    string name;
    int prev_cap;
    int new_cap;
    double loss;
};

struct aux {
    int cap;
    Station *stA;
    Station *stB;
};

struct pair_costs {
    string stA;
    string stB;
    int flow;
};

/**
 * This struct contains an overwrite of the operator().
 * It is needed to order the vector of Stations by their cost.
*/
struct order_budget
{
    bool operator() (Station *s1, Station *s2){
        int s1_p = 0, s2_p = 0;
        for(auto e : s1->getAdj()) s1_p += e->getCap() * e->getPrice();
        for(auto e : s2->getAdj()) s2_p += e->getCap() * e->getPrice();
        return s1_p >= s2_p;
    }
};

int maxNumberTrains(Station *s, Station *t, vector<Station *> g);

bool mnt_bfs(Station *s, Station *t, vector<Station *> g);

vector<pair_costs> maxCostStations(vector<Station *> g);

vector<Station *> budget_assignment(vector<Station *> g);

int minCost_maxFlow(Station *s, Station *t, vector<Station *> g);

bool findMinCostWay(Station *s, Station *t, vector<Station *> g);

int maxTrains_forGivenStation(Station *t, vector<Station *> g);

void bfs_less(Station *s, vector<Station *> g, vector<mock_station> &vec);

vector<mock_station> report_losses(vector<Segment *> v, vector<Station *> g);

#endif
