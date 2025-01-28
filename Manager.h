#ifndef SEAFIGHT_MANAGER_H
#define SEAFIGHT_MANAGER_H
#include <cstdlib>
#include <vector>
#include "Ship.h"

class Manager {
private:
    std::vector<Ship> ships;
    int numShips;
    std::vector<int> sizeShips;

public:
    Manager();

    Manager(int numShips, std::vector<int> sizeShips);
    [[nodiscard]] const Ship& getShip(int shipIndex) const;
    Ship& getShip(int shipIndex);
    [[nodiscard]] std::vector<int> getSizeShips() const;
    [[nodiscard]] int getNumShips() const;
    void popSizeShip();
    [[nodiscard]] int getRemainingNumShips() const;
    void reduceShips();
    void eraseShip(int index);
    void pushShip(Ship& ship);
    ~Manager() = default;;
};

#endif //SEAFIGHT_MANAGER_H
