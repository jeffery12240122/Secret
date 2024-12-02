#include "CommandLineParser.h"

map<string, CommandType> commandMap = {
    {"--reptile", CMD_REPTILE}
};

map<string, MainOptionType> mainOptionMap = {
    {"--stock", MAIN_STOCK}
};

map<string, OptionType> optionMap = {
    {"--stock_id", OPT_STOCK_ID}
};
CommandLineParser::CommandLineParser(int argc, char* argv[]) {
    bool hasCmd = false, hasMainOpt = false;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        auto cmdIt = commandMap.find(arg);
        if (cmdIt != commandMap.end()) {
            commands.insert(cmdIt->second);
            hasCmd = true;
            continue;
        }

        auto mainOptIt = mainOptionMap.find(arg);
        if (mainOptIt != mainOptionMap.end()) {
            if (hasMainOpt) {
                throw invalid_argument("Multiple main options are not allowed: " + arg);
            }
            mainOption = mainOptIt->second;
            hasMainOpt = true;
            continue;
        }

        auto optIt = optionMap.find(arg);
        if (optIt != optionMap.end()) {
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                options[optIt->second] = argv[++i];
            } else {
                throw invalid_argument("Error: Missing value for option " + arg);
            }
            continue;
        }

        throw invalid_argument("Unknown argument: " + arg);
    }

    if (!hasCmd) {
        throw invalid_argument("Error: Missing required command.");
    }

    if (!hasMainOpt) {
        throw invalid_argument("Error: Missing required main option.");
    }
}

bool CommandLineParser::hasCommand(CommandType cmd) const {
    return commands.find(cmd) != commands.end();
}

bool CommandLineParser::hasMainOption(MainOptionType mainOpt) const {
    return mainOption == mainOpt;
}

bool CommandLineParser::hasOption(OptionType opt) const {
    return options.find(opt) != options.end();
}

string CommandLineParser::getOption(OptionType opt) const {
    auto it = options.find(opt);
    return (it != options.end()) ? it->second : "";
}