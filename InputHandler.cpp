#include "InputHandler.h"
#include <fstream>

InputHandler::InputHandler() {
    loadKeyMap("../cmake-build-debug/key_mapping.txt");
}

CommandType InputHandler::getCommand() {
    std::cout << "Press any available key to run the command:" << std::endl;
    char input;
    std::cin >> input;
    auto it = commandsMapping.find(input);
    if (it != commandsMapping.end()) {
        return it->second;
    }
    return CommandType::UNKNOWN;
}

void InputHandler::defaultKeyMap() {
    commandsMapping = {
        {'s', CommandType::SAVE},
        {'l', CommandType::LOAD},
        {'e', CommandType::ENEMY_FIELD},
        {'u', CommandType::USER_FIELD},
        {'c', CommandType::CONTINUE},
        {'q', CommandType::QUIT},
        {'h', CommandType::HELP}
    };
    std::cout << "The key mapping is set to default." << std::endl;
    help();
}

void InputHandler::loadKeyMap(const std::string& filename) {
    std::unordered_map<char, CommandType> uncheckedMapping;
    std::unordered_map<CommandType, char> reversedMapping;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "The mapping file couldn't be open." << std::endl;
        defaultKeyMap();
        return;
    }
    std::cout << "The mapping file was opened successfully. Mapping keys according to the file content." << std::endl;
    char key;
    std::string command;
    while (file >> key >> command) {
        CommandType cmd = stringToCommand(command);
        if (cmd == CommandType::UNKNOWN) {
            std::cout << "Warning: command " << commandToString(cmd) << " is unknown." << std::endl;
            defaultKeyMap();
            return;
        }
        if (uncheckedMapping.find(key) != uncheckedMapping.end()) {
            std::cout << "Error: key " << key << " is already used for another command." << std::endl;
            defaultKeyMap();
            return;
        }
        if (reversedMapping.find(cmd) != reversedMapping.end()) {
            std::cout << "Error: command " << commandToString(cmd) << " is already has a key." << std::endl;
            defaultKeyMap();
            return;
        }
        uncheckedMapping[key] = cmd;
        reversedMapping[cmd] = key;
    }
    for (CommandType cmd : {CommandType::SAVE, CommandType::LOAD, CommandType::QUIT,
                            CommandType::USER_FIELD, CommandType::ENEMY_FIELD, CommandType::CONTINUE, CommandType::HELP}) {
        if (reversedMapping.find(cmd) == reversedMapping.end()) {
            std::cout << "Warning: Command '" << commandToString(cmd) << "' has no key assigned." << std::endl;
            defaultKeyMap();
            return;
        }
    }
    commandsMapping = std::move(uncheckedMapping);
}

CommandType InputHandler::stringToCommand(const std::string& command) {
    if (command == "LOAD") return CommandType::LOAD;
    if (command == "SAVE") return CommandType::SAVE;
    if (command == "QUIT") return CommandType::QUIT;
    if (command == "USER_FIELD") return CommandType::USER_FIELD;
    if (command == "ENEMY_FIELD") return CommandType::ENEMY_FIELD;
    if (command == "CONTINUE") return CommandType::CONTINUE;
    if (command == "HELP") return CommandType::HELP;
    return CommandType::UNKNOWN;
}

std::string InputHandler::commandToString(CommandType type) {
    if (type == CommandType::LOAD) return "LOAD";
    if (type == CommandType::SAVE) return "SAVE";
    if (type == CommandType::USER_FIELD) return "USER_FIELD";
    if (type == CommandType::ENEMY_FIELD) return "ENEMY_FIELD";
    if (type == CommandType::CONTINUE) return "CONTINUE";
    if (type == CommandType::HELP) return "HELP";
    return "UNKNOWN";
}

void InputHandler::help() {
    for (const auto& pair : commandsMapping) {
        std::cout << "Key: " << pair.first << ", Command: ";
        std::cout << commandToString(pair.second) << std::endl;
    }
}
