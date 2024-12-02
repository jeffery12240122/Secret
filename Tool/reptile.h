#ifndef REPTILE_H
#define REPTILE_H
#include "../Error.h"

using namespace std;

class reptile{
public:
    bool getHTML(const string& stockID);
    string extractStockPrice(const string& filePath);
    void execReptile(const string& id);
    reptile();
};
#endif REPTILE_H