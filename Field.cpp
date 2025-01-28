#include <iostream>
#include <iomanip>
#include "Exceptions.h"
#include "Field.h"
#include "AbilityManager.h"

Field::Field(): width(0), height(0), needsToReduceShips(false) {}

Field::Field(int width, int height) {
    if (width <= 0 || height <= 0) {
        throw PositiveIntError("Error: The user entered an invalid value for the size of the field.\n");;
    }
    this->width = width;
    this->height = height;
    data.resize(height, std::vector<int>(width, 0));
    allPtr.resize(height, std::vector<Cell>(width));
}

int Field::getWidth() const {
    return width;
}

int Field::getHeight() const {
    return height;
}

void Field::showField() {
    std::cout << std::setw(7) << " ";
    for (size_t j = 0; j < width; j++) {
        std::cout << std::setw(4) << j << '.';
    }
    std::cout << std::endl;
    for (size_t i = 0; i < height; i++) {
        std::cout << std::setw(5) << i << '.';
        for (size_t j = 0; j < width; j++) {
            if (data[i][j] != 0) {
                std::cout << std::setw(5) << "2";
            }
            else {
                std::cout << std::setw(5) << "~";
            }
        }
        std::cout << std::endl;
    }
}

void Field::checkArea(std::vector<int> coordinates, int length, char orientation) {
    int xmin, xmax, ymin, ymax;
    xmin = std::max(0, coordinates[0]-1);
    ymin = std::max(0, coordinates[1]-1);
    if (orientation == 'h') {
        if (coordinates[0]+length > width) {
            throw ShipError("Error: The ship doesn't fit on the field.\n");
        }
        xmax = std::min(width-1, coordinates[0]+length);
        ymax = std::min(height-1, coordinates[1]+1);
    }
    else if (orientation == 'v') {
        if (coordinates[1]+length > height) {
            throw ShipError("Error: The ship doesn't fit on the field.\n");
        }
        xmax = std::min(width - 1, coordinates[0] + 1);
        ymax = std::min(height - 1, coordinates[1] + length);
    }
    else {
        throw OrientationError("Error: The user entered an invalid orientation for the ship.\n");
    }
    for (size_t i = ymin; i <= ymax; i++) {
        for (size_t j = xmin; j <= xmax; j++) {
            if (data[i][j] == 1) {
                throw ShipError("Error: The ship is in contact with another one.\n");;
            }
        }
    }
}

void Field::setShip(Ship &ship, std::vector<int> coordinates, char orientation) {
    if (coordinates[0] < 0 || coordinates[1] < 0 || coordinates[0] >= width || coordinates[1] >= height) {
        throw CoordinatesError("Error: Incorrect coordinates.\n");
    }
    checkArea(coordinates, ship.getLength(), orientation);
    int indexShipSegment = 0;
    if (orientation == 'h') {
        ship.setOrient(Orientation::HORIZONTAL);
        while (indexShipSegment < ship.getLength()) {
            data[coordinates[1]][coordinates[0] + indexShipSegment] = 1;
            allPtr[coordinates[1]][coordinates[0] + indexShipSegment] = {indexShipSegment, &ship};
            indexShipSegment++;
        }
    } else {
        ship.setOrient(Orientation::VERTICAL);
        while (indexShipSegment < ship.getLength()) {
            data[coordinates[1] + indexShipSegment][coordinates[0]] = 1;
            allPtr[coordinates[1] + indexShipSegment][coordinates[0]] = {indexShipSegment, &ship};
            indexShipSegment++;
        }
    }

}

int Field::attack(std::vector<int> coordinates) {
    if (coordinates[0] < 0 || coordinates[1] < 0  || coordinates[0] >= width || coordinates[1] >= height) {
        throw CoordinatesError("Error: Incorrect coordinates.\n");
    }
    if (DoubleDamage::isDoubleDamageActive()) {
        std::cout << "Applying Double Damage attack" << std::endl;
    }
    allPtr[coordinates[1]][coordinates[0]].gotHit = true;
    if (allPtr[coordinates[1]][coordinates[0]].shipPtr) {
            if (DoubleDamage::isDoubleDamageActive()) {
                DoubleDamage::deactivateDoubleDamage();
                if (allPtr[coordinates[1]][coordinates[0]].shipPtr->getAttack(allPtr[coordinates[1]][coordinates[0]].indSeg)) {
                    needsToReduceShips = true;
                    return 2;
                }

            }
            if (allPtr[coordinates[1]][coordinates[0]].shipPtr->getAttack(allPtr[coordinates[1]][coordinates[0]].indSeg)) {
                data[coordinates[1]][coordinates[0]] = 0;
                if (allPtr[coordinates[1]][coordinates[0]].shipPtr->getCondition() == ShipState::DESTROYED){
                    needsToReduceShips = true;
                    return 2;
                }
            }
            return 1;
    }
    else {
        std::cout << "Oops.. Didn't hit the ship." << std::endl;
        DoubleDamage::deactivateDoubleDamage();
        return 0;
    }
}

Field::Field(const Field& other):width(other.width),height(other.height) {
    data = other.data;
    allPtr = other.allPtr;
}

Field &Field::operator=(const Field& other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        data = other.data;
        allPtr = other.allPtr;
    }
    return *this;
}

Field::Field(Field&& other) noexcept:width(0),height(0) {
    std::swap(width, other.width);
    std::swap(height, other.height);
    data = std::move(other.data);
    allPtr = std::move(other.allPtr);
}

Field &Field::operator=(Field &&other) noexcept {
    if (this != &other) {
        std::swap(width, other.width);
        std::swap(height, other.height);
        data = std::move(other.data);
        allPtr = std::move(other.allPtr);
    }
    return *this;
}
