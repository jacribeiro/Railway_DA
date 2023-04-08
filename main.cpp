#include <iostream>

#include "src/Menu.h"

using namespace std;

int main() {
    FileReader reader = FileReader();
    Graph g = Graph();
    Menu menu = Menu(reader, g);
    menu.show();
    g.clearSegments();
    g.clearStations();
    return 0;
}
