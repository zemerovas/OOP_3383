#ifndef SEAFIGHT_DAMAGE_H
#define SEAFIGHT_DAMAGE_H

#include "IAbility.h"
#include "Field.h"
#include <iostream>


class Damage: public IAbility {
    void useAbility(Field &field) override;
    [[nodiscard]] AbilityType getType() const override;
};

#endif //SEAFIGHT_DAMAGE_H
