#include <iostream>
#include "Menu.h"
#include "BasicServiceMetrics_funcs.h"

Menu::Menu(FileReader r, Graph n): reader(r), network(n) {};

void Menu::show() {
    bool working = true;
    cout << "================================================\n";
    cout << "Welcome to the Railway Network management system\n";
    cout << "================================================\n\n";
    string stfile, nfile;
    cout << "Please insert the path to the CSV file containing the stations in the network: \n";
    cin >> stfile;
    cout << "Now, please insert the path to the CSV file containing the connections between stations: \n";
    cin >> nfile;
    while (!reader.readStationsFile(stfile, network)) {
        cout << "Something went wrong. Please correct the path of the stations file:\n";
        cin >> stfile;
    }
    while (!reader.readNetworkFile(nfile, network)) {
        cout << "Something went wrong. Please correct the path of the network file:\n";
        cin >> nfile;
    }
    cout << "Please respect the required format of your input, otherwise, it may cause the system to shut down.\n";
    while (working) {
        cout << "Hello, what task are you interested in today?\n";
        // 1. Max number of trains between two stations - ask for input of stations, call function
        cout << "1. Calculate maximum number of trains between two stations\n";
        // 2. Determine which pair(s) of stations require(s) the most amount of trains between them
        cout << "2. Find the pair(s) of stations that require the most trains between them\n";
        // 3. Advice on budget assignment, ask for number of stations to advice report
        cout << "3. Find top-k municipalitites, given budget requirements for their stations\n";
        // 4. Report max number of trains that can arrive to a given station, simultaneously - ask for station
        cout << "4. Report maximum number of trains that can arrive at a station\n";
        // 5. Report max number of trains that can travel between two stations, given min budget - ask for stations
        cout << "5. Report maximum number of trains between stations with lowest possible budget\n";
        // 6. Reduced connectivity options
        cout << "6. Reduced connectivity options\n";
        // 7. Leave the system
        cout << "7. Exit the system\n";
        int o1; cin >> o1;
        switch (o1) {
            case 1:
                string st1, st2;
                cout << "1. Calculate maximum number of trains between two stations\n";
                cout << "Please provide the name of the stations: \nOrigin: ";
                cin >> st1;
                cout << "Destination: ";
                cin >> st2;
                showMaxNumTrains(st1, st2); break;
            case 2:
                cout << "2. Find the pair(s) of stations that require the most trains between them\n";
                showMostTrainsPairs(); break;
            case 3:
                int k;
                cout << "3. Find top-k municipalitites, given budget requirements for their stations\n";
                cout << "For an ordered list regarding budget assignment advice, please insert k: \n";
                cin >> k;
                showBudgetAssign(k); break;
            case 4:
                string st3;
                cout << "4. Report maximum number of trains that can arrive at a station\n";
                cout << "Please provide the name of the station: \n";
                cin >> st3;
                showMaxTrainsStation(st3); break;
            case 5:
                string st4, st5;
                cout << "5. Report maximum number of trains between stations with lowest possible budget\n";
                cout << "Please provide the name of the stations: \nOrigin: ";
                cin >> st4;
                cout << "Destination: ";
                cin >> st5;
                showMaxTMinB(st4, st5); break;
            case 6:
                cout << "6. Reduced connectivity options\n";
                cout << "Please choose one of the options: \n";
                cout << "1. Report the maximum number of trains that can travel between two stations\n";
                cout << "2. Find top-k stations most affected by the reduced connectivity (ordered by percentage of capacity lost)\n";
                cout << "3. Reduce connectivity\n";
                cout << "4. Return to the previous menu\n";
                int o2;
                cin >> o2;
                switch (o2) {
                    case 1:
                        string st6, st7;
                        cout << "1. Report the maximum number of trains that can travel between two stations\n";
                        cout << "Please provide the name of the stations: \nOrigin: ";
                        cin >> st6;
                        cout << "Destination: ";
                        cin >> st7;
                        showRCMaxTrains(st6, st7); break;
                    case 2:
                        cout << "2. Find top-k stations most affected by the reduced connectivity (ordered by percentage of capacity lost)\n";
                        cout << "For an ordered list regarding loss of capacity, please insert k: \n";
                        cin >> k;
                        showRCMostAffStations(k); break;
                    case 3:
                        cout << "3. Reduce connectivity\n";
                        showReduceConnectivity(); break;
                    case 4:
                        break;
                }
            case 7:
                cout << "Exiting system\n";
                working = false; break;
        }
    }
}

// Option 1
void Menu::showMaxNumTrains(const string &st1, const string &st2) {

}

// Option 2
void Menu::showMostTrainsPairs() {

}

// Option 3
void Menu::showBudgetAssign(int k) {

}

// Option 4
void Menu::showMaxTrainsStation(const string &station) {

}

// Option 5
void Menu::showMaxTMinB(const string &st1, const string &st2) {

}

// Option 6.1
void Menu::showRCMaxTrains(const string &st1, const string &st2) {

}

// Option 6.2
void Menu::showRCMostAffStations(int k) {

}

// Option 6.3
void Menu::showReduceConnectivity() {
    string st1, st2;
    cout << "You will now select a segment of the network where connectivity should be reduced\n";
    cout << "Please insert the name of your origin station: \n";
    cin >> st1;
    cout << "Now select one of the ";
}