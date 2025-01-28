#include "SaverManager.h"
#include <sstream>

void SaverManager::save(std::ostream& out, const Manager& manager) {
    out << "__MANAGER_START__" << std::endl;
    out << manager.getRemainingNumShips() << std::endl;
    std::vector<int> sizeShips = manager.getSizeShips();
    for (int size : sizeShips) {
        out << size << " ";
    }
    out << std::endl;
}


void SaverManager::load(std::istream& in, Manager& manager) {
    std::string line;
    std::getline(in, line);
    while (line != "__MANAGER_START__") {
        std::getline(in, line);
    }
    std::getline(in, line);
    std::istringstream iss(line);
    int numShips;
    iss >> numShips;
    std::vector<int> sizeShips(numShips);
    std::getline(in, line);
    std::istringstream iss2(line);
    for (int i = 0; i < numShips; ++i) {
        iss2 >> sizeShips[i];
    }
    manager = Manager(numShips, sizeShips);
}

SaverManager::SaverManager(const Manager &manager) : manager(manager) {}
