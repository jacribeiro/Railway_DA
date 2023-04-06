#ifndef BSM_FUNCS_H
#define BSM_FUNCS_H

#include "Station.h"
#include "Segment.h"
#include "Graph.h"
#include <queue>
#include <utility>
#include <vector>

using namespace std;

//2.1 (também funciona para 4.1, mas g tem menos edges)
int maxNumberTrains(Station *s, Station *t, vector<Station *> g);
//bfs auxiliar para 2.1
bool mnt_bfs(Station *s, Station *t, vector<Station *> g);
//2.2
vector<pair<Station *, Station *>> maxCostStations(vector<Station *> g);
//2.3
vector<Station *> budget_assignment(vector<Station *> g);
//3.1
int minCost_maxFlow(Station *s, Station *t, vector<Station *> g);
//bfs auxiliar para 3.1
bool findMinCostWay(Station *s, Station *t, vector<Station *> g);
//2.4
int maxTrains_forGivenStation(Station *t, vector<Station *> g);
//4.2
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

void bfs_less(Station *s, vector<Station *> g, vector<mock_station> &vec);

vector<mock_station> report_losses(vector<Segment *> v, vector<Station *> g);

#endif
