#ifndef UTIL_H
#define UTIL_H
#include "../Error.h"
using namespace std;

class util {
public:
    static string readAPIKey(const string& filePath);
};

#endif UTIL_H