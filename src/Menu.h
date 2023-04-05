#ifndef RAILWAY_MENU_H
#define RAILWAY_MENU_H

#include "FileReader.h"
#include "Graph.h"

using namespace std;

class Menu {
    FileReader reader;
    Graph network;

public:
    
    /**
     * Creates a new Menu object
     * 
     * @param r A FileReader object responsible for reading the network files
     * @param n A Graph object, representing the Railway network
    */
    Menu(FileReader r, Graph n);

    /**
     * Prints the interface and interacts with the user
    */
    void show();

    // other useful functions, called during show()

}

#endif