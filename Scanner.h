#ifndef SEAFIGHT_SCANNER_H
#define SEAFIGHT_SCANNER_H

#include <iostream>
#include "IAbility.h"
#include "Field.h"



class Scanner: public IAbility {
    void useAbility(Field &field) override;
    [[nodiscard]] AbilityType getType() const override;
};

#endif //SEAFIGHT_SCANNER_H
