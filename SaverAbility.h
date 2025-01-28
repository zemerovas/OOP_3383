#ifndef SEAFIGHT_GAME_CPP_SAVERABILITY_H_
#define SEAFIGHT_GAME_CPP_SAVERABILITY_H_
#include "AbilityManager.h"
#include <unordered_map>

class SaverAbility {
   public:
    static void save(std::ostream& out, std::queue<std::shared_ptr<IAbility>>& abilityQueue);
    static void load(std::istream& in, std::queue<std::shared_ptr<IAbility>>& abilityQueue);
    explicit SaverAbility(const AbilityManager& abilityManager);
   private:
    const AbilityManager& abilityManager;
};

#endif//SEAFIGHT_GAME_CPP_SAVERABILITY_H_
