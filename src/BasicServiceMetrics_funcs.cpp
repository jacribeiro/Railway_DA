#include "BasicServiceMetrics_funcs.h"

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