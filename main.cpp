#include <iostream>
#include <string>
#include "CommandLineParser.h"

int main(int argc, char* argv[]) {
try {
        CommandLineParser cmd(argc, argv);

        for (CommandType command : cmd.commands) {
            switch (command) {
                case CMD_REPTILE: {
                    if (cmd.hasMainOption(MAIN_STOCK)) {
                        if (cmd.hasOption(OPT_STOCK_ID)) {
                            string id = cmd.getOption(OPT_STOCK_ID);
                            shared_ptr<reptile> rep = make_shared<reptile>();
                            rep->execReptile(id);
                        } else {
                            throw invalid_argument("Error: Missing stock ID.");
                        }
                    } else {
                        throw invalid_argument("Error: Missing required main option.");
                    }
                    break;
                }
                default:
                    throw invalid_argument("Error: Unsupported command.");
            }
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    } catch (...) {
        cerr << "Unknown error occurred." << endl;
    }

    return 0;
}