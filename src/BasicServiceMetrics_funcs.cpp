#include "BasicServiceMetrics_funcs.h"
#include <algorithm>
using namespace std;


int maxNumberTrains(Station *s, Station *t, vector<Station *>& g) {
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

bool mnt_bfs(Station *s, Station *t, vector<Station *>& g) {
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


vector<pair_costs> maxCostStations(vector<Station *>& g) {
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

vector<Station*>& budget_assignment(int k, vector<Station *>& g) {
    int m = k;
    for(auto s : g){
        s->setVisited(false);
    }
    vector<Station*> v;
    while(k != 0){
        int c = INT32_MIN;
        int pos = 0;
        int rem = 0;
        while(pos != g.size()){
            if(!g[pos]->getVisited()){
                int posc = 0;
                for(auto e : g[pos]->getAdj()){
                    posc += e->getCap() * e->getPrice();
                }
                if(posc > c){
                    rem = pos;
                    c = posc;
                }
            }
            pos++;
        }
        v.push_back(g[rem]);
        g[rem]->setVisited(true);
        k--;
    }
    int i = 1;
    cout << "The " << m << " stations that require the most budget are:\n";
    for (auto s : v) {
        cout << i << ". " << s->getName() << " in " << s->getMunicipality() << ", " << s->getDistrict() << endl;
        i++;
    }
    return v;
}

int minCost_maxFlow(Station *s, Station *t, vector<Station *>& g, vector<Segment*>& e) {
    for(Station* st : g){
        st->setPrevious(nullptr);
        st->setVisited(false);
        st->setIs(false);
    }
    cout << "done this\n";
    vector<Segment> l;
    for(auto seg : e){
        l.push_back(*seg);
    }
    cout << "pushed back everything\n";
    while(!l.empty()){
        sort(l.begin(), l.end(), [](Segment s1, Segment s2){return s1.getCap()*s1.getPrice() >= s2.getCap()*s2.getPrice();});
        auto x = l.back();
        l.pop_back();
        auto x_a = x.getA();
        auto x_b = x.getB();
        if(!x_a->getIs() || !x_b->getIs()){
            x_a->setIs(true);
            x_b->setIs(true);
        }
    }
    cout << "aglhdj\n";
    for(auto seg : e){
        if(!seg->getA()->getIs() || !seg->getB()->getIs()){
            seg->setCap(0);
        }
    }
    cout << "altered caps\n";
    return maxNumberTrains(s, t, g);
}

bool findMinCostWay(Station *s, Station *t, vector<Station *>& g) {


}

int maxTrains_forGivenStation(Station *t, vector<Station *>& g) {
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

void bfs_less(Station *s, vector<Station *>& g, vector<mock_station>& vec) {
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

vector<mock_station> report_losses(vector<Segment *>& v, vector<Station *>& g) {
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
