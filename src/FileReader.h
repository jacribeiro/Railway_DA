#ifndef RAILWAY_FILEREADER_H
#define RAILWAY_FILEREADER_H

#include "Station.h"
#include "Graph.h"

class FileReader {

public:
    /**
     * Default constructor. Returns a new FileReader object.
     */
    FileReader();

    /**
     * Reads/parses a CSV format file containing the network stations
     * @param fname Name/location of the file to be read
     * @param g Reference to graph to store the stations of the network
     * @return 0 in case of no errors, 1 otherwise
     */
    static int readStationsFile(const std::string& fname, Graph& g);

    /**
     * Reads/parses a CSV format file containing the connections between stations in the network
     * @param fname Name/location of the file to be read
     * @param g Reference to graph containing the stations of the network
     * @return 0 in case of no errors, 1 otherwise
     */
    static int readNetworkFile(const std::string& fname, Graph& g);
};


#endif