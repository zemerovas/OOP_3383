#ifndef SEAFIGHT_FIELD_H
#define SEAFIGHT_FIELD_H

#include <vector>
#include "Ship.h"

class AbilityManager;

struct Cell {
    int indSeg = -1;
    Ship *shipPtr = nullptr;
    bool gotHit = false;
};

class Field {
private:
    int width;
    int height;
public:
    bool needsToReduceShips;
    std::vector<std::vector<Cell>> allPtr;
    std::vector<std::vector<int>> data;
    Field();
    Field(int width, int height);
    Field(const Field& other);
    Field& operator = (const Field& obj);
    Field(Field&& other) noexcept ;
    Field& operator = (Field&& other) noexcept ;
    ~Field() = default;
    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;
    void showField();
    void setShip(Ship &ship, std::vector<int> coordinates, char orientation);
    int attack(std::vector<int> coordinates);
    void checkArea(std::vector<int> coordinates, int length, char orientation);
};


#endif //SEAFIGHT_FIELD_H
