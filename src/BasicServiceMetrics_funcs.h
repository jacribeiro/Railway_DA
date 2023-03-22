#ifndef BSM_FUNCS_H
#define BSM_FUNCS_H

#include "Station.h"
#include "Segment.h"
#include "Graph.h"
#include <queue>

using namespace std;

int maxNumberTrains(Station *s, Station *t, vector<Station *> g);

bool mnt_bfs(Station *s, Station *t, vector<Station *> g);

#endif
