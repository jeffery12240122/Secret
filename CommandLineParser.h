#ifndef COMMAND_LINE_PARSER_H
#define COMMAND_LINE_PARSER_H
#include "Tool/reptile.h"

using namespace std;

enum CommandType {
    CMD_HELP,
    CMD_REPTILE,
    CMD_UNKNOWN
};

enum MainOptionType {
    MAIN_STOCK,
    MAIN_UNKNOWN
};

enum OptionType {
    OPT_STOCK_ID,
    OPT_HISTORY,
    OPT_UNKNOWN
};

extern map<string, CommandType> commandMap;
extern map<string, MainOptionType> mainOptionMap;
extern map<string, OptionType> optionMap;

class CommandLineParser {
public:
    CommandLineParser(int argc, char* argv[]);
    bool hasCommand(CommandType cmd) const;
    bool hasMainOption(MainOptionType mainOpt) const;
    bool hasOption(OptionType opt) const;
    string getOption(OptionType opt) const;
    bool hasHelp() const { return helpFlag; }

    set<CommandType> commands;
    MainOptionType mainOption = MAIN_UNKNOWN;
    map<OptionType, string> options;
    bool helpFlag = false;
};

#endif COMMAND_LINE_PARSER_H