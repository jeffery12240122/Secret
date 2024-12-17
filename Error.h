#include <fstream>
#include <regex>
#include <memory>
#include <string>
#include <cstdlib>
#include <iostream>
#include <set>
#include <map>
#include <sstream>

using namespace std;

class FetchException : public exception {
private:
    string message;
public:
    explicit FetchException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};