#ifndef REPTILE_H
#define REPTILE_H
#include "util.h"

using namespace std;

class reptile{
public:
    void getHistoricalDataWithAPI(const string& stockID, const string& duration);
    string calculateStartDate(const string& duration);
    bool getStockData(const string& stockID);
    string extractStockPrice(const string& filePath);
    void execReptile(const string& id);
    reptile();
};
#endif REPTILE_H