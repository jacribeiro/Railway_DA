#include <iostream>
#include "Menu.h"
#include "BasicServiceMetrics_funcs.h"

Menu::Menu(FileReader& r, Graph& n): reader(r), network(n) {};

void Menu::show() {
    bool working = true;
    cout << "================================================\n";
    cout << "Welcome to the Railway Network management system\n";
    cout << "================================================\n\n";
    string stfile, nfile;
    cout << "Please insert the path to the CSV file containing the stations in the network: \n";
    cin >> stfile;
    while (reader.readStationsFile(stfile, network)) {
        cout << "Something went wrong. Please correct the path of the stations file:\n";
        cin >> stfile;
    }
    cout << "Now, please insert the path to the CSV file containing the connections between stations: \n";
    cin >> nfile;
    while (reader.readNetworkFile(nfile, network)) {
        cout << "Something went wrong. Please correct the path of the network file:\n";
        cin >> nfile;
    }
    cout << "Please respect the required format of your input, otherwise, it may cause the system to shut down.\n";
    string st1, st2, st3, st4, st5, st6, st7;
    vector<Segment *> v;
    while (working) {
        cout << "Hello, what task are you interested in today?\n";
        // 1. Max number of trains between two stations - ask for input of stations, call function
        cout << "1. Calculate maximum number of trains between two stations\n";
        // 2. Determine which pair(s) of stations require(s) the most amount of trains between them
        cout << "2. Find the pair(s) of stations that require the most trains between them\n";
        // 3. Advice on budget assignment, ask for number of stations to advice report
        cout << "3. Find top-k municipalities, given budget requirements for their stations\n";
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
                cout << "1. Calculate maximum number of trains between two stations\n";
                cout << "Please provide the name of the stations: \nOrigin: ";
                cin.ignore(); getline(cin, st1);
                cout << "Destination: ";
                getline(cin, st2);
                showMaxNumTrains(st1, st2); break;
            case 2:
                cout << "2. Find the pair(s) of stations that require the most trains between them\n";
                showMostTrainsPairs(); break;
            case 3:
                int k;
                cout << "3. Find top-k municipalities, given budget requirements for their stations\n";
                cout << "For an ordered list regarding budget assignment advice, please insert k: \n";
                cin >> k;
                showBudgetAssign(k); break;
            case 4:
                cout << "4. Report maximum number of trains that can arrive at a station\n";
                cout << "Please provide the name of the station: \n";
                cin >> st3;
                showMaxTrainsStation(st3); break;
            case 5:
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
                        showRCMostAffStations(v, k); break;
                    case 3:
                        cout << "3. Reduce connectivity\n";
                        showReduceConnectivity(v); break;
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
    int max = maxNumberTrains(network.getStation(st1), network.getStation(st2), network.getStationSet());
    cout << "The maximum numbers of trains that can travel between " << st1 << " and " << st2 << "is " << max << endl;
}

// Option 2
void Menu::showMostTrainsPairs() {
    vector<pair<Station *, Station *>> v = maxCostStations(network.getStationSet());
    cout << "The stations with the most trains travelling between them are:\n";
    for (auto s: v) {
        cout << s.first->getName() << " - " << s.second->getName() << endl;
    }
}

// Option 3
void Menu::showBudgetAssign(int k) {
    vector<Station *> v = budget_assignment(network.getStationSet());
    cout << "The " << k << " stations that require the most budget are:\n";
    for (int i = 0; i < k; i++) {
        cout << i+1 << ". " << v[i]->getName() << " in " << v[i]->getMunicipality() << ", " << v[i]->getDistrict() << endl;
    }
}

// Option 4
void Menu::showMaxTrainsStation(const string &station) {
    int max = maxTrains_forGivenStation(network.getStation(station), network.getStationSet());
    cout << "The maximum number of trains that can arrive at " << station << " simultaneously is " << max << endl;
}

// Option 5
void Menu::showMaxTMinB(const string &st1, const string &st2) {
    int max = minCost_maxFlow(network.getStation(st1), network.getStation(st2), network.getStationSet());
    cout << "The maximum number of trains that can travel between " << st1 << " and " << st2 << " with the lowest budget is " << max << endl;
}

// Option 6.1
void Menu::showRCMaxTrains(const string &st1, const string &st2) {
    int max = maxNumberTrains(network.getStation(st1), network.getStation(st2), network.getStationSet());
    cout << "The maximum number of trains that can travel between " << st1 << " and " << st2 << " given your reduced connectivity conditions is " <<
     max << endl;
}

// Option 6.2
void Menu::showRCMostAffStations(vector<Segment *>& v, int k) {
    vector<mock_station> stations = report_losses(v, network.getStationSet());
    cout << "The most affected stations, ordered by loss of capacity, given your reduced connectivity condition are: \n";
    for (int i = 0; i < k; i++) {
        cout << i + 1 << ". " << stations[i].name << " losing " << stations[i].loss * 100 << "% of its original capacity\n";
    }
}

// Option 6.3
void Menu::showReduceConnectivity(vector<Segment *>& v) {
    string st1, st2;
    cout << "You will now select a segment of the network where connectivity should be reduced\n";
    cout << "Please insert the name of your origin station: \n";
    cin >> st1;
    vector<Segment *> options = network.getStation(st1)->getAdj();
    cout << "Now select one of the following possible destinations: \n";
    for (int i = 0; i < options.size(); i++) {
        if (options[i]->getA()->getName() == st1) {
            cout << i + 1 << options[i]->getB()->getName() << endl;
        } else {
            cout << i + 1 << options[i]->getA()->getName() << endl;
        }
    }
    int chosen = 0;
    cin >> chosen;
    options[chosen-1]->getA()->getName() == st1 ? st2 = options[chosen-1]->getB()->getName() : st2 = options[chosen-1]->getA()->getName();
    cout << "Chosen segment: " << st1 << " to " << st2 << endl;
    v.push_back(options[chosen-1]);
}
