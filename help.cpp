#include "help.h"

using namespace std;

void showHelp() {
    std::cout << "Usage: ./LCC.exe [COMMAND] [MAIN_OPTION] [OPTION]\n\n";

    // Display commands
    std::cout << "Commands:\n";
    for (const auto& cmd : commandMap) {
        std::cout << "  --" << cmd.first << " : ";
        switch (cmd.second) {
            case CMD_HELP:
                std::cout << "Show help information.\n";
                break;
            case CMD_REPTILE:
                std::cout << "Fetch stock data and display.\n";
                break;
            default:
                std::cout << "Unknown command.\n";
        }
    }

    std::cout << "\nMain Options:\n";
    for (const auto& opt : mainOptionMap) {
        std::cout << "  --" << opt.first << " : ";
        switch (opt.second) {
            case MAIN_STOCK:
                std::cout << "Specify stock-related operations.\n";
                break;
            default:
                std::cout << "Unknown main option.\n";
        }
    }

    std::cout << "\nOptions:\n";
    for (const auto& opt : optionMap) {
        std::cout << "  --" << opt.first << " : ";
        switch (opt.second) {
            case OPT_STOCK_ID:
                std::cout << "Specify the stock ID for operations.\n";
                break;
            case OPT_HISTORY:
                std::cout << "Specify historical data duration.\n";
                break;
            default:
                std::cout << "Unknown option.\n";
        }
    }

    std::cout << "\nExample Usage:\n";
    std::cout << "  ./LCC.exe --reptile --stock --stock_id <stock_id> --history <1m|1y>\n";
    std::cout << "  ./LCC.exe --help\n";
}

