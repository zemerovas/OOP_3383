#ifndef SEAFIGHT_IABILITY_H
#define SEAFIGHT_IABILITY_H

#include "Field.h"
#include "Manager.h"
#include "AbilityType.h"

class IAbility {
    public:
        virtual void useAbility(Field& field) = 0;
        virtual AbilityType getType() const = 0;
        virtual ~IAbility() = default;
};

#endif //SEAFIGHT_IABILITY_H
