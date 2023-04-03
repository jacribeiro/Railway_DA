#include "BasicServiceMetrics_funcs.h"
#include <algorithm>
using namespace std;

int maxNumberTrains(Station *s, Station *t, vector<Station *> g) {
    for(auto v : g){
        for(auto e : v->getAdj()){
            e->setFlow(0);
        }
    }
    int max_flow = 0;
    while(mnt_bfs(s, t, g)){
        int min = INT32_MAX;
        auto sta_atual = t;
        auto seg_atual = t->getPrevious();
        while(true){
            if(seg_atual->getCap() - seg_atual->getFlow() < min) min = seg_atual->getCap() - seg_atual->getFlow();
            if(seg_atual->getA()->getID() == sta_atual->getID()) sta_atual = seg_atual->getB();
            else sta_atual = seg_atual->getA();
            if(sta_atual->getID() == s->getID()) break;
            seg_atual = sta_atual->getPrevious();
        }
        seg_atual = t->getPrevious();
        sta_atual = t;
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

bool mnt_bfs(Station *s, Station *t, vector<Station *> g) {
    queue<Station *> q;
    for(Station* st : g){
        st->setPrevious(nullptr);
        st->setVisited(false);
        st->setIs(true);
    }
    q.push(s);
    s->setVisited(true);
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
            if((w->getIs() && !w->getVisited()) && e->getCap() - e->getFlow() > 0){
                w->setVisited(true);
                w->setPrevious(e);
                q.push(w);
                if(w->getID() == t->getID()) return true;
            }
        }
    }
    return false;
}

vector<pair<Station *, Station *>> maxCostStations(vector<Station *> g) {
    int highest_cost = 0;
    vector<pair<Station *, Station *>> ret;
    for(auto v : g){
        v->setVisited(false);
        for(auto e : v->getAdj()){
            Station *w;
            if(v->getID() == e->getA()->getID()){
                w = e->getB();
            }
            else{
                w = e->getA();
            }
            if(!e->getVisited() && w->getIs()){
                if(e->getCap() > highest_cost){
                    highest_cost = e->getCap();
                    ret.clear();
                    ret.emplace(ret.end(), e->getA(), e->getB());
                }
                else if(e->getCap() == highest_cost) ret.emplace(ret.end(), e->getA(), e->getB());
                e->setVisited(true);
            }
        }
    }
    return ret;
}

struct order_budget //ordena o grafo por ordem decrescente do preço necessário para cada estação
//tem em conta os distritos
{
    bool operator() (Station *s1, Station *s2){
        int s1_p = 0, s2_p = 0;
        for(auto e : s1->getAdj()) s1_p += e->getCap() * e->getPrice();
        for(auto e : s2->getAdj()) s2_p += e->getCap() * e->getPrice();
        return s1->getDistrict() == s2->getDistrict() && s1_p >= s2_p;
    }
};

struct order_district //ordena os vértices do grafo por distrito
{
    bool operator() (Station *s1, Station *s2){
        return s1->getDistrict() <= s2->getDistrict();
    }
};


vector<Station *> budget_assignment(vector<Station *> g) {
    sort(g.begin(), g.end(), order_district());
    sort(g.begin(), g.end(), order_budget());
    return g;
}

int minCost_maxFlow(Station *s, Station *t, vector<Station *> g) {
    for(auto v : g){
        for(auto e : v->getAdj()){
            e->setFlow(0);
        }
    }
    int max_flow = 0;
    while(findMinCostWay(s, t, g)){
        int min = INT32_MAX;
        auto sta_atual = t;
        auto seg_atual = t->getPrevious();
        while(true){
            if(seg_atual->getCap() - seg_atual->getFlow() < min) min = seg_atual->getCap() - seg_atual->getFlow();
            if(seg_atual->getA()->getID() == sta_atual->getID()) sta_atual = seg_atual->getB();
            else sta_atual = seg_atual->getA();
            if(sta_atual->getID() == s->getID()) break;
            seg_atual = sta_atual->getPrevious();
        }
        seg_atual = t->getPrevious();
        sta_atual = t;
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

bool findMinCostWay(Station *s, Station *t, vector<Station *> g) {
    for(Station* st : g){
        st->setPrevious(nullptr);
        st->setVisited(false);
        st->setIs(true);
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
                if(e->getA()->getID() == v->getID()){
                    next_v = e->getB();
                }
                else{
                    next_v = e->getA();
                }

                if((next_v->getIs() && !next_v->getVisited()) && e->getCap() - e->getFlow() > 0){
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

int maxTrains_forGivenStation(Station *t, vector<Station *> g) {
    for(Station* st : g){
        st->setPrevious(nullptr);
        st->setVisited(false);
        st->setIs(true);
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
