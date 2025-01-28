#include <iostream>
#include "Manager.h"
#include "Exceptions.h"

Manager::Manager() {
    numShips = 0;
    sizeShips = {};
}

Manager::Manager(int numShips, std::vector<int> sizeShips) {
    this->numShips = numShips;
    this->sizeShips = sizeShips;
    for (int i = 0; i < numShips; i++) {
        ships.emplace_back(sizeShips[i], Orientation::HORIZONTAL);
    }
}

const Ship& Manager::getShip(int shipIndex) const {
    return ships[shipIndex];
}

Ship& Manager::getShip(int shipIndex) {
    return ships[shipIndex];
}

int Manager::getRemainingNumShips() const {
    return numShips;
}

int Manager::getNumShips() const {
    return sizeShips.size();
}

void Manager::reduceShips(){
    numShips--;
}

std::vector<int> Manager::getSizeShips() const {
    return sizeShips;
}

void Manager::popSizeShip() {
    sizeShips.pop_back();
}

void Manager::eraseShip(int index) {
    ships.erase(ships.begin() + index);
}
void Manager::pushShip(Ship& ship) {
    ships.push_back(ship);
}
