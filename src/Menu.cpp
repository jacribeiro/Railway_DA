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
        
    }
}