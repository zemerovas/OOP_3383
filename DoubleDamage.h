#ifndef SEAFIGHT_DOUBLEDAMAGE_H
#define SEAFIGHT_DOUBLEDAMAGE_H

#include "IAbility.h"
#include "Field.h"
#include "Manager.h"
#include <iostream>


class DoubleDamage: public IAbility{
   public:
    void useAbility(Field &field) override;
    static bool isDoubleDamageActive();
    static void activateDoubleDamage();
    static void deactivateDoubleDamage();
    [[nodiscard]] AbilityType getType() const override;

   private:
    static bool doubleDamageActive;
};


#endif //SEAFIGHT_DOUBLEDAMAGE_H

