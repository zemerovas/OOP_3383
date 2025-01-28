#ifndef SEAFIGHT_SHIP_H
#define SEAFIGHT_SHIP_H
#include <cstdlib>
#include <vector>

enum class SegState: int {DESTROYED = 0, DAMAGED = 1, INTACT = 2};
enum class ShipState: int {DESTROYED = 0, INTACT = 1};
enum class Orientation: char {HORIZONTAL = 'h', VERTICAL = 'v'};

class Ship {
private:
    Orientation orientation;
    ShipState condition;
    int length;

public:
    std::vector <SegState> shipBody;
    explicit Ship(int length, Orientation orientation);
    ~Ship() = default;
    void setOrient(Orientation orient);
    Orientation getOrient();
    bool getAttack(int indSeg);
    ShipState getCondition();
    int getLength() const;
    int getIntOrient() const;
};

#endif //SEAFIGHT_SHIP_H
