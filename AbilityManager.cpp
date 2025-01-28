#include <random>
#include <utility>
#include "AbilityManager.h"
#include "Exceptions.h"

AbilityManager::AbilityManager() : AbilityManager(true) {}

AbilityManager::AbilityManager(bool initializedAbilities) {
    if (initializedAbilities) {
        std::vector<AbilityType> types = {AbilityType::SCANNER, AbilityType::DAMAGE, AbilityType::DOUBLE_DAMAGE};
        int randIndex, end = 2;
        for (int i = 0; i < 3; i++) {
            randIndex = getRandNum(0, end - i);
            abilityQueue.push(std::move(AbilityFactory::createAbility(types[randIndex])));
            types.erase(types.begin() + randIndex);
        }
    }
}

int AbilityManager::getRandNum(int start, int end) {
    std::minstd_rand generator;
    generator.seed(std::random_device{}());
    std::uniform_int_distribution<int> dist(start, end);
    int randNum = dist(generator);
    return randNum;
}

AbilityType AbilityManager::getAbilityType() {
    int randNum = getRandNum(0, 2);
    return AbilityType(randNum);
}

void AbilityManager::addAbility() {
    AbilityType abilityTypeToAdd = getAbilityType();
    abilityQueue.push(std::move(AbilityFactory::createAbility(abilityTypeToAdd)));
}

void AbilityManager::getAbilityFromQueue(Field &field) {
    if (abilityQueue.empty()) {
        throw NoAbilityError("Error: You have no ability left.");
    }
    auto ability = std::move(abilityQueue.front());
    ability->useAbility(field);
    abilityQueue.pop();
}

bool AbilityManager::checkAbility() {
    if (abilityQueue.empty()) {
        return false;
    }
    return true;
}

std::queue<std::shared_ptr<IAbility>>& AbilityManager::getAbilityQueue() {
    return abilityQueue;
}

void AbilityManager::setAbilityQueue(const std::queue<std::shared_ptr<IAbility>>& abilities) {
    abilityQueue = abilities;
}

AbilityManager::AbilityManager(AbilityManager&& other) noexcept
    : abilityQueue(std::move(other.abilityQueue)) {

}

AbilityManager& AbilityManager::operator=(AbilityManager&& other) noexcept {
    if (this != &other) {
        abilityQueue = std::move(other.abilityQueue);
    }
    return *this;
}
