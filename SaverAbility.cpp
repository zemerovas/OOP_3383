#include "SaverAbility.h"
#include <sstream>

const std::unordered_map<AbilityType, std::string> AbilityTypeToString = {
    {AbilityType::DAMAGE, "DAMAGE"},
    {AbilityType::DOUBLE_DAMAGE, "DOUBLE_DAMAGE"},
    {AbilityType::SCANNER, "SCANNER"}
};

const std::unordered_map<std::string, AbilityType> StringToAbilityType = {
    {"DAMAGE", AbilityType::DAMAGE},
    {"DOUBLE_DAMAGE", AbilityType::DOUBLE_DAMAGE},
    {"SCANNER", AbilityType::SCANNER}
};

void SaverAbility::save(std::ostream &out, std::queue<std::shared_ptr<IAbility>>& abilityQueue) {
    size_t queueSize = abilityQueue.size();
    for (size_t i = 0; i < queueSize; ++i) {
        std::shared_ptr<IAbility> ability = std::move(abilityQueue.front());
        abilityQueue.pop();
        AbilityType abilityType = ability->getType();
        auto it = AbilityTypeToString.find(abilityType);
        if (it != AbilityTypeToString.end()) {
            out << it->second << "\n";
        }
        abilityQueue.push(std::move(ability));
    }
}

void SaverAbility::load(std::istream &in, std::queue<std::shared_ptr<IAbility>>& abilityQueue) {
    std::string abilityTypeStr;
    while (std::getline(in, abilityTypeStr)) {
        auto it = StringToAbilityType.find(abilityTypeStr);
        if (it != StringToAbilityType.end()) {
            abilityQueue.push(AbilityFactory::createAbility(it->second));
        }
    }
}

SaverAbility::SaverAbility(const AbilityManager &abilityManager) : abilityManager(abilityManager) {}
