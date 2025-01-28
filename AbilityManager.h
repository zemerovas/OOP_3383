#ifndef SEAFIGHT_ABILITYMANAGER_H
#define SEAFIGHT_ABILITYMANAGER_H

#include <iostream>
#include <queue>
#include <memory>
#include "IAbility.h"
#include "Damage.h"
#include "DoubleDamage.h"
#include "Scanner.h"
#include "AbilityFactory.h"
#include "AbilityType.h"

class AbilityManager {
    public:
        AbilityManager();
        explicit AbilityManager(bool initializedAbilities);
        void addAbility();
        int getRandNum(int start, int end);
        void getAbilityFromQueue(Field &field);
        bool checkAbility();
        [[nodiscard]] std::queue<std::shared_ptr<IAbility>>& getAbilityQueue();
        void setAbilityQueue(const std::queue<std::shared_ptr<IAbility>>& abilities);
        AbilityManager(AbilityManager&& other) noexcept ;
        AbilityManager& operator=(AbilityManager&& other) noexcept ;
        AbilityManager(const AbilityManager&) = delete;
        AbilityManager& operator=(const AbilityManager&) = delete;

    private:
     std::queue<std::shared_ptr<IAbility>> abilityQueue;
     AbilityType getAbilityType();

};

#endif // SEAFIGHT_ABILITYMANAGER_H



