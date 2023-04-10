#include <iostream>
#include "Menu.h"
#include "BasicServiceMetrics_funcs.h"

Menu::Menu(FileReader& r, BasicServiceMetrics m, Graph& n): reader(r), metrics (m), network(n) {};

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
        cout << "1. Calculate maximum number of trains between two stations\n";
        cout << "2. Find the pair(s) of stations that require the most trains between them\n";
        cout << "3. Find top-k municipalities, given budget requirements for their stations\n";
        cout << "4. Report maximum number of trains that can arrive at a station\n";
        cout << "5. Report maximum number of trains between stations with lowest possible budget\n";
        cout << "6. Reduced connectivity options\n";
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
                cin.ignore();
                getline(cin, st3);
                showMaxTrainsStation(st3); break;
            case 5:
                cout << "5. Report maximum number of trains between stations with lowest possible budget\n";
                cout << "Please provide the name of the stations: \nOrigin: ";
                cin.ignore();
                getline(cin, st4);
                cout << "Destination: ";
                getline(cin, st5);
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
    int max = metrics.maxNumberTrains(network.getStation(st1), network.getStation(st2), network.getStationSet());
    cout << "The maximum numbers of trains that can travel between " << st1 << " and " << st2 << " is " << max << endl;
}

// Option 2
void Menu::showMostTrainsPairs() {
    vector<pair_costs> v = metrics.maxCostStations(network.getStationSet());
    cout << "The pairs of stations with the most trains travelling between them are:\n";
    for (int i = 0; i < 10; i++) {
        cout << v[i].stA << " - " << v[i].stB << endl;
    }
}

// Option 3
void Menu::showBudgetAssign(int k) {
    metrics.budget_assignment(k, network.getStationSet());

}

// Option 4
void Menu::showMaxTrainsStation(const string &station) {
    int max = metrics.maxTrains_forGivenStation(network.getStation(station), network.getStationSet());
    cout << "The maximum number of trains that can arrive at " << station << " simultaneously is " << max << endl;
}

// Option 5
void Menu::showMaxTMinB(const string &st1, const string &st2) {
    int max = metrics.minCost_maxFlow(network.getStation(st1), network.getStation(st2), network.getStationSet(), network.getSegmentSet());
    cout << "The maximum number of trains that can travel between " << st1 << " and " << st2 << " with the lowest budget is " << max << endl;
}

// Option 6.1
void Menu::showRCMaxTrains(const string &st1, const string &st2) {
    int max = metrics.maxNumberTrains(network.getStation(st1), network.getStation(st2), network.getStationSet());
    cout << "The maximum number of trains that can travel between " << st1 << " and " << st2 << " given your reduced connectivity conditions is " <<
     max << endl;
}

// Option 6.2
void Menu::showRCMostAffStations(vector<Segment *>& v, int k) {
    vector<mock_station> stations = metrics.report_losses(v, network.getStationSet());
    cout << "The most affected stations, ordered by loss of capacity, given your reduced connectivity condition are: \n";
    for (int i = 0; i < k; i++) {
        cout << i + 1 << ". " << stations[i].name << " losing " << stations[i].loss * 100 << "% of its original capacity\n";
    }
}

// Option 6.3
void Menu::showReduceConnectivity(vector<Segment *>& v) {
    string ori, dest;
    cout << "You will now select a segment of the network where connectivity should be reduced\n";
    cout << "Please insert the name of your origin station: \n";
    getline(cin, ori);
    vector<Segment *> options = network.getStation(ori)->getAdj();
    cout << "Now select one of the following possible destinations: \n";
    for (int i = 0; i < options.size(); i++) {
        if (options[i]->getA()->getName() == ori) {
            cout << i + 1 << options[i]->getB()->getName() << endl;
        } else {
            cout << i + 1 << options[i]->getA()->getName() << endl;
        }
    }
    int chosen = 0;
    cin >> chosen;
    options[chosen-1]->getA()->getName() == ori ? dest = options[chosen-1]->getB()->getName() : dest = options[chosen-1]->getA()->getName();
    cout << "Chosen segment: " << ori << " to " << dest << endl;
    cout << "The current capacity of this segment is " << options[chosen-1]->getCap() << endl;
    int opt = 0;
    cout << "Do you wish to:\n";
    cout << "1. Reduce the capacity\n";
    cout << "2. Remove the segment completely\n";
    cin >> opt;
    int newCap = 0;
    switch (opt) {
        case 1:
            cout << "Enter the new (reduced) capacity: \n";
            cin >> newCap;
            options[chosen-1]->setCap(newCap);
            break;
        case 2:
            cout << "The segment will be removed from the network\n";
            options[chosen-1]->setCap(0);
            break;
    }
    v.push_back(options[chosen-1]);
}
