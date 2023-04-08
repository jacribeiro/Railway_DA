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

    aux(int i, Station *st1, Station *st2): cap(i), stA(st1), stB(st2) {};
};

struct pair_costs {
    string stA;
    string stB;
    int flow;

    pair_costs(string a, string b, int f): stA(a), stB(b), flow(f) {};
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

/**
 * @param s The source station, from where trains will start their path
 * @param t The target station, where trains will try to reach
 * @param g The Stations that compose the Graph
 * @return The maximum number of trains that can go simultaneously from Station s to Station t
 *
 * This function calculates the maximum number of trains (flow) that can travel from one station to another.
*/
int maxNumberTrains(Station *s, Station *t, vector<Station *>& g);

/**
 * @param s The source station, from where trains will start their path
 * @param t The target station, where trains will try to reach
 * @param g The Stations that compose the Graph
 * @return True if the algorithm finds a path from s to t, False otherwise
 *
 * This function uses a modified BFS algorithm to find the
 * shortest path between the source node and the sink node.
*/
bool mnt_bfs(Station *s, Station *t, vector<Station *>& g);

/**
 * @param g The Stations that compose the Graph
 * @return A vector of pair_costs items, ordered by the non-ascending cost of travelling from stA to stB
 *
 * This function finds the pairs of stations that require the most trains to reach from one to the other.
*/
vector<pair_costs> maxCostStations(vector<Station *>& g);

/**
 * @param g The Stations that compose the Graph
 * @return The vector of Stations ordered in non-ascending order of maintenance costs
 *
 * This function orders the Station list by cost,
 * by calling the overwritten operator() of order_budget.
*/
vector<Station *>& budget_assignment(vector<Station *>& g);

/**
 * @param s The source station, from where trains will start their path
 * @param t The target station, where trains will try to reach
 * @param g The Stations that compose the Graph
 * @return The maximum number of trains that can go from s to t with minimum costs for the company
 *
 * This function calculates the maximum number of trains (flow)
 * that can travel from one station to another with minimum
 * costs for the company.
*/
int minCost_maxFlow(Station *s, Station *t, vector<Station *>& g);

/**
 * @param s The source station, from where trains will start their path
 * @param t The target station, where trains will try to reach
 * @param g The Stations that compose the Graph
 * @return True if the algorithm finds a path from s to t, False otherwise
 *
 * This function uses a greedy algorithm to find the
 * cheapest path between the source node and the sink node.
*/
bool findMinCostWay(Station *s, Station *t, vector<Station *>& g);

/**
 * @param t The Station for which the function calculates the maximum number of trains
 * @param g The Stations that compose the Graph
 * @return The maximum number of trains that can arrive simultaneously at Station t
 *
 * This function finds the maximum number of trains that can arrive simultaneously
 * at station t.
 * It works by iterating through the edges that connect to t and subtracting
 * from the maximum capacity when there is a bottleneck.
*/
int maxTrains_forGivenStation(Station *t, vector<Station *>& g);

/**
 * @param s The Station from where the algorithm will start its iterations over g
 * @param g The Stations that compose the Graph
 * @param vec A vector of mock_station, that will keep track of the Stations affected by the removal of segments
 *
 * This function uses a modified BFS algorithm to find which Stations are affected by the removal of edges,
 * and calculates their percentual loss of capacity.
*/
void bfs_less(Station *s, vector<Station *>& g, vector<mock_station>& vec);

/**
 * @param v A vector containing the removed Segments
 * @param g The Stations that compose the Graph
 * @return A vector of mock_station items, representing Stations and their capacity losses
 *
 * This function builds a vector of mock_station items,
 * ordered by the non-ascending percentual loss of capacity
 * of the Stations they represent.
*/
vector<mock_station> report_losses(vector<Segment *>& v, vector<Station *>& g);

#endif
