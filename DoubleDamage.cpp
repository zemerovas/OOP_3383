#include "DoubleDamage.h"
#include "Exceptions.h"

bool DoubleDamage::doubleDamageActive = false;

void DoubleDamage::useAbility(Field &field) {
    std::cout << "Current type of attack is DOUBLE DAMAGE!" << std::endl;
    activateDoubleDamage();
}

bool DoubleDamage::isDoubleDamageActive() {
    if (doubleDamageActive) {
        return true;
    }
    return false;
}

void DoubleDamage::activateDoubleDamage() {
    doubleDamageActive = true;
}

void DoubleDamage::deactivateDoubleDamage() {
    doubleDamageActive = false;
}

AbilityType DoubleDamage::getType() const {
    return AbilityType::DOUBLE_DAMAGE;
}
