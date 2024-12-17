#include "reptile.h"

reptile::reptile() {}

bool reptile::getStockData(const string& stockID) {
    string apiKey = util::readAPIKey("APIKEY.txt");
    string URL = "curl \"https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=" + stockID +
                 "&interval=5min&apikey=" + apiKey + "\" -o output.json";

    int result = system(URL.c_str());

    if (result != 0) {
        throw FetchException("Failed to fetch stock data from Alpha Vantage.");
    }

    return true;
}


string reptile::extractStockPrice(const string& filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        throw FetchException("Error: Could not open file: " + filePath);
    }

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    size_t timeSeriesPos = content.find("\"Time Series (5min)\"");
    if (timeSeriesPos == string::npos) {
        throw FetchException("Time series data not found in the response.");
    }

    size_t timestampPos = content.find("{", timeSeriesPos);
    if (timestampPos == string::npos) {
        throw FetchException("No stock data available.");
    }

    size_t closePos = content.find("\"4. close\":", timestampPos);
    if (closePos == string::npos) {
        throw FetchException("Stock price not found in the response.");
    }

    size_t closeStart = content.find("\"", closePos + 11);
    size_t closeEnd = content.find("\"", closeStart + 1);
    string price = content.substr(closeStart + 1, closeEnd - closeStart - 1);

    size_t openPos = content.find("\"1. open\":", timestampPos);
    if (openPos == string::npos) {
        throw FetchException("Open price not found in the response.");
    }

    size_t openStart = content.find("\"", openPos + 11);
    size_t openEnd = content.find("\"", openStart + 1);
    string open = content.substr(openStart + 1, openEnd - openStart - 1);

    double priceVal = stod(price);
    double openVal = stod(open);
    double change = priceVal - openVal;

    return "    Price: " + price + "\n" +
           "    Change: " + (change > 0 ? "+" : "") + to_string(change);
}

void reptile::execReptile(const string& id) {
    try {
        if (getStockData(id)) {
            string stockPrice = extractStockPrice("output.json");
            cout << "\n" + id + "\n====================\n" << stockPrice << endl;
        }
    } catch (const FetchException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void reptile::getHistoricalDataWithAPI(const string& stockID, const string& duration) {
    string apiKey = util::readAPIKey("APIKEY.txt");
    string URL = "curl \"https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=" + stockID +
             "&interval=5min&apikey=" + apiKey + "\" -o output.json";
    int result = system(("curl \"" + URL + "\" -o historical_data.csv").c_str());
    if (result != 0) {
        throw FetchException("Failed to fetch data from Alpha Vantage.");
    }
    cout << "Historical data saved to historical_data.csv" << endl;
}

string reptile::calculateStartDate(const string& duration) {
    time_t now = time(nullptr);
    if (duration == "1m") return to_string(now - 30 * 24 * 60 * 60);
    if (duration == "1y") return to_string(now - 365 * 24 * 60 * 60);
    throw invalid_argument("Unsupported duration: " + duration);
}
