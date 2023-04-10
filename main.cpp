#include <iostream>

#include "src/Menu.h"

using namespace std;

int main() {
    FileReader reader = FileReader();
    Graph g = Graph();
    BasicServiceMetrics m = BasicServiceMetrics();
    Menu menu = Menu(reader, m, g);
    menu.show();
    g.clearSegments();
    g.clearStations();
    return 0;
}
