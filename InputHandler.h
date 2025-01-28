#ifndef SEAFIGHT_CONTROLLERS_CPP_INPUTHANDLER_H_
#define SEAFIGHT_CONTROLLERS_CPP_INPUTHANDLER_H_
#include <unordered_map>
#include <iostream>

enum class CommandType {
    SAVE,
    LOAD,
    QUIT,
    USER_FIELD,
    ENEMY_FIELD,
    CONTINUE,
    UNKNOWN,
    HELP
};

class InputHandler {
   public:
    std::unordered_map<char, CommandType> commandsMapping;
    CommandType getCommand();
    explicit InputHandler();
    void loadKeyMap(const std::string& fileName);
    void help();
    void defaultKeyMap();
    static CommandType stringToCommand(const std::string& command);
    static std::string commandToString(CommandType type);

};

#endif//SEAFIGHT_CONTROLLERS_CPP_INPUTHANDLER_H_
