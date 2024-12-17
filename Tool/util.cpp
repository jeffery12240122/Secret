#include "util.h"

string util::readAPIKey(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        throw runtime_error("Error: Could not open API key file: " + filePath);
    }
    string apiKey;
    getline(file, apiKey);
    file.close();
    if (apiKey.empty()) {
        throw runtime_error("Error: API key file is empty.");
    }
    return apiKey;
}
