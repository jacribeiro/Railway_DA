#ifndef RAILWAY_DA_FILEREADER_H
#define RAILWAY_DA_FILEREADER_H

#include "Station.h"

class FileReader {
public:
    int readStationsFile(const string& fname, vector<Station*>& stations);

};


#endif //RAILWAY_DA_FILEREADER_H
