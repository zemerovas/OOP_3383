#include <random>
#include "Damage.h"

void Damage::useAbility(Field &field) {
    std::cout << "Current type of attack is DAMAGE!" << std::endl;
    std::vector<std::vector<int>> coordinatesWithShip;
    for (int i = 0; i < field.getHeight(); i++) {
        for (int j = 0; j < field.getWidth(); j++) {
            if (field.allPtr[i][j].shipPtr && field.allPtr[i][j].shipPtr->shipBody[field.allPtr[i][j].indSeg] != SegState::DESTROYED) {
                coordinatesWithShip.push_back({j, i});
            }
        }
    }
    std::minstd_rand generator;
    generator.seed(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, coordinatesWithShip.size()-1);
    int randNum = dist(generator);
    field.attack(coordinatesWithShip[randNum]);
}

AbilityType Damage::getType() const {
    return AbilityType::DAMAGE;
}
