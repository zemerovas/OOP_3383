#ifndef SEAFIGHT__ABILITYFACTORY_H_
#define SEAFIGHT__ABILITYFACTORY_H_

#include "AbilityManager.h"
#include "AbilityType.h"

class AbilityFactory {
   public:
    static std::shared_ptr<IAbility> createAbility(AbilityType type);
    virtual ~AbilityFactory() = default;
};

#endif//SEAFIGHT__ABILITYFACTORY_H_
