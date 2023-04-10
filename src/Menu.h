#ifndef RAILWAY_MENU_H
#define RAILWAY_MENU_H

#include "FileReader.h"
#include "Graph.h"

using namespace std;

class Menu {
    FileReader& reader;
    Graph& network;

protected:
    /**
     * Prints to the console a message displaying the maximum number of trains between two given stations
     * @param st1 Name of the origin station
     * @param st2 Name of the destination station
     */
    void showMaxNumTrains(const string &st1, const string &st2);

    /**
     * Prints to the screen the 10 pairs of stations with the most trains travelling between them
     */
    void showMostTrainsPairs();

    /**
     * Prints to the console a message showing the k stations that require the most budget for maintenance
     * @param k Number of stations to display
     */
    void showBudgetAssign(int k);

    /**
     * Prints to the console a message showing the maximum number of trains that can arrive at a station simultaneously
     * @param station Name of the station
     */
    void showMaxTrainsStation(const string &station);

    /**
     * Prints to the console a message showing the maximum number of trains that can travel between two stations with
     * minimum costs for the company
     * @param st1 Name of the origin station
     * @param st2 Name of the destination station
     */
    void showMaxTMinB(const string &st1, const string &st2);

    /**
     * Prints to the console the maximum number of trains that can travel between two stations given previously
     * established reduced connectivity conditions
     * @param st1 Name of the origin station
     * @param st2 Name of the destination station
     */
    void showRCMaxTrains(const string &st1, const string &st2);

    /**
     * Prints to the console a message showing the most affected k stations by the established reduced connectivity
     * conditions
     * @param k
     */
    void showRCMostAffStations(vector<Segment *>& v, int k);

    /**
     * Interacts with the user in order to create a reduced connectivity segment
     * @param v Vector where the reduced connectivity segments are stored
     */
    void showReduceConnectivity(vector<Segment *>& v);

public:
    
    /**
     * Creates a new Menu object
     * 
     * @param r A FileReader object responsible for reading the network files
     * @param n A Graph object, representing the Railway Network
    */
    Menu(FileReader& r, Graph& n);

    /**
     * Prints the interface and interacts with the user
    */
    void show();
};

#endif