#include "reptile.h"

reptile::reptile() {}

bool reptile::getHTML(const string& stockID) {
    string URL = "https://tw.stock.yahoo.com/quote/" + stockID;
    int result = system(("curl " + URL + " -o output.html").c_str());
    if (result != 0) {
        throw FetchException("Failed to fetch HTML content from URL: " + URL);
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

    regex pricePattern(R"(<span[^>]*class="[^"]*Fz\(32px\)[^"]*Fw\(b\)[^"]*C\(\$c-trend-(up|down)\)[^>]*>(\d{1,3}(?:,\d{3})*(?:\.\d+)?)<\/span>)");
    regex percentagePattern(R"(<span[^>]*class="[^"]*C\(\$c-trend-(up|down)\)[^>]*>\(([\d.]+%)\)<\/span>)");

    smatch priceMatch, percentageMatch;

    string result;

    if (regex_search(content, priceMatch, pricePattern)) {
        string trend = priceMatch[1];
        string price = priceMatch[2];

        if (regex_search(content, percentageMatch, percentagePattern)) {
            string percent = percentageMatch[2];
            result = "    Price: " + price + "\n"
                     "    Change: " + (trend =="up"?"+":"-") + percent;
        } else {
            throw FetchException("Percentage not found in HTML content.");
        }
    } else {
        throw FetchException("Price not found in HTML content.");
    }

    return result;
}

void reptile::execReptile(const string& id){
    try{
        if (getHTML(id)) {
            string stockPrice = extractStockPrice("output.html");
            cout << "\n" + id + "\n====================\n" << stockPrice << endl;
        }
    }catch(const FetchException& e){
        cout << "Error: " << e.what() << endl;
    }
}
