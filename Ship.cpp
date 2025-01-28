#include <iostream>
#include "Ship.h"

Ship::Ship(int length, Orientation orientation) {
    if (length == 0) {
        this->length = 0;
        this->orientation = orientation;
        this->condition = ShipState::DESTROYED;
        shipBody.resize(1, SegState::INTACT);
    } else {
        this->length = length;
        this->orientation = orientation;
        this->condition = ShipState::INTACT;
        shipBody.resize(length, SegState::INTACT);
    }
}

bool Ship::getAttack(int indSeg) {
    if (shipBody[indSeg] == SegState::DESTROYED) {
        std::cout << "The ship is already destroyed." << std::endl;
        return false;
    }
    else if (shipBody[indSeg]== SegState::INTACT) {
        shipBody[indSeg] = SegState::DAMAGED;
        std::cout << "Ship's segment is damaged!" << std::endl;
        return false;
    }
    else {
        shipBody[indSeg] = SegState::DESTROYED;
        length--;
        if (length == 0) {
            std::cout << "Last ship's segment is destroyed! The whole ship was sunk!" << std::endl;
            condition = ShipState::DESTROYED;

        }
        else {
            std::cout << "Ship's segment is destroyed!" << std::endl;
        }
    }
    return true;
}


Orientation Ship::getOrient() {
    return orientation;
}

void Ship::setOrient(Orientation orient) {
    orientation = orient;
}

ShipState Ship::getCondition() {
    return condition;
}

int Ship::getLength() const {
    return length;
}

int Ship::getIntOrient() const {
    if (orientation == Orientation::HORIZONTAL) {
        return 0;
    }
    return 1;
}







