#ifndef RAILWAY_MENU_H
#define RAILWAY_MENU_H

#include "FileReader.h"
#include "Graph.h"

using namespace std;

class Menu {
    FileReader reader;
    Graph network;

protected:
    /**
     *
     * @param st1
     * @param st2
     */
    void showMaxNumTrains(const string &st1, const string &st2);

    /**
     *
     */
    void showMostTrainsPairs();

    /**
     *
     * @param k
     */
    void showBudgetAssign(int k);

    /**
     *
     * @param station
     */
    void showMaxTrainsStation(const string &station);

    /**
     *
     * @param st1
     * @param st2
     */
    void showMaxTMinB(const string &st1, const string &st2);

    /**
     *
     * @param st1
     * @param st2
     */
    void showRCMaxTrains(const string &st1, const string &st2);

    /**
     *
     * @param k
     */
    void showRCMostAffStations(int k);

    /**
     *
     */
    void showReduceConnectivity();

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
}

#endif