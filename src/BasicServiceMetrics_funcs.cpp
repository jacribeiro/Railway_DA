#include "BasicServiceMetrics_funcs.h"
#include <algorithm>
using namespace std;

/**
 * @param s The source station, from where trains will start their path
 * @param t The target station, where trains will try to reach
 * @param g The Stations that compose the Graph
 * @return The maximum number of trains that can go simultaneously from Station s to Station t
 * 
 * This function calculates the maximum number of trains (flow) that can travel from one station to another.
*/
int maxNumberTrains(Station *s, Station *t, vector<Station *> g) {
    //set the flow of the graph to zero (0) in order to avoid calculation errors
    for(auto v : g){
        for(auto e : v->getAdj()){
            e->setFlow(0);
        }
    }
    int max_flow = 0;
    /*calls mnt_bfs, which (as explained below) finds the shortest 
    path from the source node to the sink node*/
    while(mnt_bfs(s, t, g)){
        int min = INT32_MAX;
        auto sta_atual = t;
        auto seg_atual = t->getPrevious();
        //finds the maximum number of trains that can pass through the path established by mnt_bfs
        while(true){
            if(seg_atual->getCap() - seg_atual->getFlow() < min) min = seg_atual->getCap() - seg_atual->getFlow();
            if(seg_atual->getA()->getID() == sta_atual->getID()) sta_atual = seg_atual->getB();
            else sta_atual = seg_atual->getA();
            if(sta_atual->getID() == s->getID()) break;
            seg_atual = sta_atual->getPrevious();
        }
        seg_atual = t->getPrevious();
        sta_atual = t;
        //iterates through the path and changes the flow value of the segments
        while(true){
            seg_atual->setFlow(seg_atual->getFlow() + min);
            if(seg_atual->getA()->getID() == sta_atual->getID()) sta_atual = seg_atual->getB();
            else sta_atual = seg_atual->getA();
            max_flow += min;
            if(sta_atual->getID() == s->getID()) break;
            seg_atual = sta_atual->getPrevious();
        }
    }
    return max_flow;
}

/**
 * @param s The source station, from where trains will start their path
 * @param t The target station, where trains will try to reach
 * @param g The Stations that compose the Graph
 * @return True if the algorithm finds a path from s to t, False otherwise
 * 
 * This function uses a modified BFS algorithm to find the
 * shortest path between the source node and the sink node.
*/
bool mnt_bfs(Station *s, Station *t, vector<Station *> g) {
    queue<Station *> q;
    for(Station* st : g){
        st->setPrevious(nullptr);
        st->setVisited(false);
    }
    q.push(s);
    s->setVisited(true);
    while(!q.empty()){
        auto v = q.front();
        q.pop();
        for(auto e : v->getAdj()){
            Station *w;
            v->getID() == e->getA()->getID() ? w = e->getB() : w = e->getA();

            if(!w->getVisited() && e->getCap() != 0 && e->getCap() - e->getFlow() > 0){
                w->setVisited(true);
                w->setPrevious(e);
                q.push(w);
                if(w->getID() == t->getID()) return true;
            }
        }
    }
    return false;
}

/**
 * @param g The Stations that compose the Graph
 * @return A vector of pair_costs items, ordered by the non-ascending cost of travelling from stA to stB
 * 
 * This function finds the pairs of stations that require the most trains to reach from one to the other.
*/
vector<pair_costs> maxCostStations(vector<Station *> g) {
    vector<pair_costs> ret;
    auto n = g.size();
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            ret.emplace(ret.end(), g[i]->getName(), g[j]->getName(), maxNumberTrains(g[i], g[j], g));
        }
    }
    sort(ret.begin(), ret.end(), [](pair_costs p1, pair_costs p2){return p1.flow >= p2.flow;});
    return ret;
}

/**
 * @param g The Stations that compose the Graph
 * @return The vector of Stations ordered in non-ascending order of maintenance costs
 * 
 * This function orders the Station list by cost,
 * by calling the overwritten operator() of order_budget.
*/
vector<Station *> budget_assignment(vector<Station *> g) {
    sort(g.begin(), g.end(), order_budget());
    return g;
}


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
int minCost_maxFlow(Station *s, Station *t, vector<Station *> g) {
    for(auto v : g){
        for(auto e : v->getAdj()){
            e->setFlow(0);
        }
    }
    int max_flow = 0;
    /*calls findMinCostWay, which (as explained below) finds 
    the cheapest available path from the 
    source node to the sink node*/
    while(findMinCostWay(s, t, g)){
        int min = INT32_MAX;
        auto sta_atual = t;
        auto seg_atual = t->getPrevious();
        //finds the maximum number of trains that can pass through the path established by findMinCostWay
        while(true){
            if(seg_atual->getCap() - seg_atual->getFlow() < min) min = seg_atual->getCap() - seg_atual->getFlow();
            if(seg_atual->getA()->getID() == sta_atual->getID()) sta_atual = seg_atual->getB();
            else sta_atual = seg_atual->getA();
            if(sta_atual->getID() == s->getID()) break;
            seg_atual = sta_atual->getPrevious();
        }
        seg_atual = t->getPrevious();
        sta_atual = t;
        //iterates through the path and changes the flow value of the segments
        while(true){
            seg_atual->setFlow(seg_atual->getFlow() + min);
            if(seg_atual->getA()->getID() == sta_atual->getID()) sta_atual = seg_atual->getB();
            else sta_atual = seg_atual->getA();
            max_flow += min;
            if(sta_atual->getID() == s->getID()) break;
            seg_atual = sta_atual->getPrevious();
        }
    }
    return max_flow;
}

/**
 * @param s The source station, from where trains will start their path
 * @param t The target station, where trains will try to reach
 * @param g The Stations that compose the Graph
 * @return True if the algorithm finds a path from s to t, False otherwise
 * 
 * This function uses a greedy algorithm to find the
 * cheapest path between the source node and the sink node.
*/
bool findMinCostWay(Station *s, Station *t, vector<Station *> g) {
    for(Station* st : g){
        st->setPrevious(nullptr);
        st->setVisited(false);
    }
    queue<Station *> q;
    q.push(s);
    s->setVisited(true);
    while(!q.empty()) {
        auto v = q.front();
        int min_cost = INT32_MAX;
        Station *next_v = nullptr;
        for(auto e : v->getAdj()){
            if((e->getCap() - e->getFlow()) * e->getPrice() < min_cost){
                q.pop();
                min_cost = (e->getCap() - e->getFlow()) * e->getPrice();
                e->getA()->getID() == v->getID() ? next_v = e->getB() : next_v = e->getA();

                if(!next_v->getVisited() && e->getCap() - e->getFlow() > 0){
                    next_v->setVisited(true);
                    next_v->setPrevious(e);
                    q.push(next_v);
                    if(next_v->getID() == t->getID()) return true;
                }
            }
            if((e->getCap() - e->getFlow()) * e->getPrice() == min_cost){
                e->getA()->getID() == v->getID() ? next_v = e->getB() : next_v = e->getA();

                if(!next_v->getVisited() && e->getCap() - e->getFlow() > 0){
                    next_v->setVisited(true);
                    next_v->setPrevious(e);
                    q.push(next_v);
                    if(next_v->getID() == t->getID()) return true;
                }
            }
        }
    }
    return false;
}

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
int maxTrains_forGivenStation(Station *t, vector<Station *> g) {
    for(Station* st : g){
        st->setPrevious(nullptr);
        st->setVisited(false);
    }
    
    int min = 0;
    int ret = 0;
    for(auto e : t->getAdj()) {
        ret += e->getCap();
        min++;
    }

    queue<Station *> q;
    q.push(t);
    t->setVisited(true);

    while(!q.empty()){
        auto v = q.front();
        q.pop();
        for(auto e : v->getAdj()){
            Station *w;
            if(v->getID() == e->getA()->getID()){
                w = e->getB();
            }
            else{
                w = e->getA();
            }
            w->setPrevious(e);
            q.push(w);
            w->setVisited(true);
            if(v->getPrevious() != nullptr && v->getPrevious()->getCap() > e->getCap()) ret -= e->getCap();
            if(ret <= min) return min;
        }
    }
    return ret;
}

/**
 * @param s The Station from where the algorithm will start its iterations over g
 * @param g The Stations that compose the Graph
 * @param vec A vector of mock_station, that will keep track of the Stations affected by the removal of segments
 * 
 * This function uses a modified BFS algorithm to find which Stations are affected by the removal of edges,
 * and calculates their percentual loss of capacity.
*/
void bfs_less(Station *s, vector<Station *> g, vector<mock_station> &vec) {
    queue<Station *> q;
    
    q.push(s);
    s->setVisited(true);
    s->setIs(true);
    mock_station ss = {s->getName(), 0, 0, 0};
    for(auto e : s->getAdj()){
        ss.new_cap += e->getCap();
        ss.prev_cap += e->getPrevCap();
    }
    ss.loss = 1 - (ss.new_cap / ss.prev_cap);
    vec.push_back(ss);
    while(!q.empty()){
        auto v = q.front();
        q.pop();
        for(auto e : v->getAdj()){
            Station *w;
            if(v->getID() == e->getA()->getID()){
                w = e->getB();
            }
            else{
                w = e->getA();
            }
            if((!w->getIs() && !w->getVisited()) && e->getCap() != 0){
                w->setVisited(true);
                q.push(w);
                if(!w->getIs()){
                    mock_station ww;
                    int ncap = 0, pcap = 0;
                    for(auto e : w->getAdj()){
                        ncap += e->getCap();
                        pcap += e->getPrevCap();
                    }
                    ww.name = w->getName();
                    ww.new_cap = ncap;
                    ww.prev_cap = pcap;
                    ww.loss = 1 - (ncap / pcap);
                    vec.push_back(ww);
                    w->setIs(true);
                }
            }
        }
    }
}

/**
 * @param v A vector containing the removed Segments
 * @param g The Stations that compose the Graph
 * @return A vector of mock_station items, representing Stations and their capacity losses
 * 
 * This function builds a vector of mock_station items,
 * ordered by the non-ascending percentual loss of capacity
 * of the Stations they represent.
*/
vector<mock_station> report_losses(vector<Segment *> v, vector<Station *> g) {
    vector<Station*> visited_nodes;
    vector<aux> edges_to_remove;
    vector<mock_station> ret;
    for(auto s : g){
        s->setIs(false);
    }
    for(auto s : v){
        edges_to_remove.emplace_back(s->getCap(), s->getA(), s->getB());
        s->setCap(0);
        
    }
    for(auto s : edges_to_remove){
        for(Station* st : g){
            st->setVisited(false);
        }
        bfs_less(s.stA, g, ret);
        bfs_less(s.stB, g, ret);
    }
    sort(ret.begin(), ret.end(), [](mock_station m1, mock_station m2) {return m1.loss >= m2.loss;});
    for(auto v : g){
        if(!v->getIs()){
            int c = 0;
            for(auto s : v->getAdj()){
                c += s->getCap();
            }
            ret.push_back({v->getName(), c, c, 0});
        }
    }
    return ret;
}
